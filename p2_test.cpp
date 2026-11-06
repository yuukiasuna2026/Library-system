// P2（实验六）持久化边界测试：单独用 g++ 编译，不加入 libarary.vcxproj
// 运行前需先创建 p2_test_dir 目录（测试数据与其隔离）
#include <iostream>
#include <fstream>
#include "library.h"
#include "Student.h"
#include "Teacher.h"
using namespace std;

static const char* DIR = "p2_test_dir";

int main()
{
    bool ok = true;

    // 1. 文件缺失：不崩溃，从空数据开始
    {
        Library lib;
        ok &= lib.loadData(DIR);
        ok &= (lib.findUser(1) == nullptr);
        cout << "--- 场景1结束 ---" << '\n';
    }

    // 2. 正常存取往返：类型恢复为多态对象、在馆状态与借阅人对应
    {
        Library libA;
        libA.addUser(new Student("张三", "计算机", 1001));
        libA.addUser(new Teacher("李四", "软件工程", 1002));
        libA.addBook(Book("Cpp", "PubC", "AuthC", "9787121155352", 100.0, 800, true));
        libA.addBook(Book("Algo", "PubA", "AuthA", "9780306406157", 50.0, 300, true));
        User* u = libA.findUser(1001);
        libA.borrowBook("Cpp", *u, "2026-10-01", "2026-10-10"); // 1001 借走 Cpp
        ok &= (u->getBorrowedBooks().size() == 1 && u->getBorrowedBooks()[0] == "Cpp"); // 借书同步书名列表
        ok &= libA.saveData(DIR);

        Library libB;
        ok &= libB.loadData(DIR);
        User* us = libB.findUser(1001);
        User* ut = libB.findUser(1002);
        ok &= (us != nullptr && us->getUserType() == "学生"); // 派生类恢复，多态不丢
        ok &= (ut != nullptr && ut->getUserType() == "教师");
        ok &= (us != nullptr && us->getCurrent() == 1);       // 已借数量恢复
        ok &= (us != nullptr && us->getBorrowedBooks().size() == 1
               && us->getBorrowedBooks()[0] == "Cpp");        // 借阅书名列表恢复
        Book* bb = libB.findBook("9787121155352");
        ok &= (bb != nullptr && !bb->isAvailable() && bb->getUserID() == 1001
               && bb->getReturndate() == "2026-10-10");       // 借出状态与借阅人对应
        ok &= (libB.findBook("9780306406157") != nullptr
               && libB.findBook("9780306406157")->isAvailable());
        cout << "--- 场景2结束 ---" << '\n';
    }

    // 3. 坏行容错：格式非法、类型非法、重复 ID、借阅人不存在的书
    {
        ofstream uf(string(DIR) + "/users.txt");
        uf << "S|1001|张三|计算机|1" << '\n';   // 正常（旧 5 字段格式兼容）
        uf << "S|1001|重复ID|x|0" << '\n';    // 重复 ID，跳过
        uf << "X|1003|坏类型|x|0" << '\n';    // 类型非法，跳过
        uf << "这不是合法行" << '\n';          // 字段数不对，跳过
        uf << "T|1002|王五|数学|2|不存在的书,另一本" << '\n'; // 书名与图书对不上，加载后修正
        uf.close();

        ofstream bf(string(DIR) + "/books.txt");
        bf << "9780306406157|Good|A|P|50|300|1|0||" << '\n';            // 在馆，正常
        bf << "9787121155352|Ghost|A|P|100|800|0|9999|2026-10-01|2026-10-10" << '\n'; // 借阅人不存在，跳过
        bf << "9780306406157|Dup|A|P|50|300|1|0||" << '\n';             // 重复 ISBN，跳过
        bf.close();

        Library libC;
        ok &= libC.loadData(DIR); // 应看到多条警告/跳过，不崩溃
        ok &= (libC.findUser(1001) != nullptr);
        User* wu = libC.findUser(1002);
        ok &= (wu != nullptr && wu->getCurrent() == 0 && wu->getBorrowedBooks().empty()); // 书名列表被修正
        ok &= (libC.findUser(1003) == nullptr);
        ok &= (libC.findBook("9787121155352") == nullptr); // 坏书被跳过
        ok &= (libC.findBook("9780306406157") != nullptr);
        cout << "--- 场景3结束 ---" << '\n';
    }

    // 4. 空文件：正常运行
    {
        ofstream uf(string(DIR) + "/users.txt"); uf.close(); // 清空
        ofstream bf(string(DIR) + "/books.txt"); bf.close();
        Library libD;
        ok &= libD.loadData(DIR);
        ok &= (libD.findUser(1001) == nullptr);
        cout << "--- 场景4结束 ---" << '\n';
    }

    cout << (ok ? "P2_TESTS_PASSED" : "P2_TESTS_FAILED") << endl;
    return ok ? 0 : 1;
}
