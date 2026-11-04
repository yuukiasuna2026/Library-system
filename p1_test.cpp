// P1 边界测试：单独用 g++ 编译，不加入 libarary.vcxproj，不影响 VS 工程
#include <iostream>
#include <sstream>
#include <iomanip>
#include "library.h"
#include "Student.h"
#include "Teacher.h"
using namespace std;

static string makeISBN(int n) // 生成合法 ISBN-13
{
    string base = "978";
    ostringstream oss;
    oss << setfill('0') << setw(9) << n;
    base += oss.str();
    int sum = 0;
    for (int k = 0; k < 12; ++k) sum += ((k + 1) % 2 == 0 ? 3 : 1) * (base[k] - '0');
    base += char('0' + (10 - sum % 10) % 10);
    return base;
}

int main()
{
    bool ok = true;

    // 1. 空 vector 查找（经 findUser，P1.3 模板本轮未实施）
    Library lib;
    ok &= (lib.findUser(1) == nullptr);

    // 2. 查找存在与不存在的用户
    lib.addUser(new Student("张三", "计算机", 1001));
    lib.addUser(new Teacher("李四", "软件工程", 1002));
    ok &= (lib.findUser(1001) != nullptr);
    ok &= (lib.findUser(9999) == nullptr);

    // 3. 删除首本、中间一本、最后一本图书
    Book b0("Book0", "P", "A", makeISBN(0), 10.0, 100, true);
    Book b1("Book1", "P", "A", makeISBN(1), 10.0, 100, true);
    Book b2("Book2", "P", "A", makeISBN(2), 10.0, 100, true);
    lib.addBook(b0); lib.addBook(b1); lib.addBook(b2);

    lib.outBook(b0); // 删除第一本
    ok &= (lib.findBook(makeISBN(0)) == nullptr);
    ok &= (lib.findBook(makeISBN(1)) != nullptr && lib.findBook(makeISBN(2)) != nullptr);

    lib.addBook(b0); // 补回
    lib.outBook(b1); // 删除中间一本
    ok &= (lib.findBook(makeISBN(1)) == nullptr);
    ok &= (lib.findBook(makeISBN(0)) != nullptr && lib.findBook(makeISBN(2)) != nullptr);

    lib.addBook(b1);
    lib.outBook(b2); // 删除最后一本
    ok &= (lib.findBook(makeISBN(2)) == nullptr);
    ok &= (lib.findBook(makeISBN(0)) != nullptr && lib.findBook(makeISBN(1)) != nullptr);

    // 4. 删除不存在的 ISBN：其余图书不受影响
    Book bx("Ghost", "P", "A", makeISBN(3), 10.0, 100, true);
    lib.outBook(bx); // 库中无此书，静默无操作
    ok &= (lib.findBook(makeISBN(0)) != nullptr);

    // 5. cout << book 输出（字段齐全）
    {
        ostringstream oss;
        oss << b0;
        string s = oss.str();
        ok &= (s.find("Book0") != string::npos && s.find(makeISBN(0)) != string::npos
               && s.find("是否可借") != string::npos);
        cout << "--- cout << book 输出样例 ---" << '\n' << b0;
    }

    // 6. 多态用户统一输出（经基类引用体现差异）
    {
        User* us = new Student("王五", "数学", 1003);
        User* ut = new Teacher("赵六", "物理", 1004);
        ostringstream os1, os2;
        os1 << *us;
        os2 << *ut;
        ok &= (os1.str().find("学生") != string::npos);
        ok &= (os2.str().find("教师") != string::npos);
        cout << "--- cout << 学生 ---" << '\n' << *us;
        cout << "--- cout << 教师 ---" << '\n' << *ut;
        delete us; delete ut; // 测试自建对象，不经 Library 管理
    }

    // 7. clear() 后再次添加并查找
    lib.clear();
    ok &= (lib.findUser(1001) == nullptr);
    lib.addUser(new Student("新人", "化学", 2001));
    lib.addBook(Book("NewBook", "P", "A", makeISBN(9), 10.0, 100, true));
    ok &= (lib.findUser(2001) != nullptr && lib.findBook(makeISBN(9)) != nullptr);

    cout << (ok ? "P1_TESTS_PASSED" : "P1_TESTS_FAILED") << endl;
    return ok ? 0 : 1;
}
