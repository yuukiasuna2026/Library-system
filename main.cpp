#include <iostream>
#include <string>
#include <limits>
#ifdef _WIN32
#include <windows.h>
#endif
#include "book.h"
#include "library.h"
#include "Student.h"
#include "Teacher.h"
using namespace std;

static void eatLine() // 吃掉一行残留输入（cin >> 之后用）
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // 输出 UTF-8
    SetConsoleCP(CP_UTF8);        // 输入也 UTF-8（需要 cin 中文时）
#endif
    // 实验六：启动加载——从 books.txt / users.txt 恢复数据（文件缺失则从空数据开始）
    Library lib;
    lib.loadData();

    int choice = -1;
    while(true)
    {
        cout << "\n========== 图书馆借阅管理系统 ==========" << '\n';
        cout << " 1.添加图书    2.删除图书    3.查询图书    4.列出全部图书" << '\n';
        cout << " 5.添加用户    6.删除用户    7.修改图书    8.修改用户" << '\n';
        cout << " 9.登录       10.登出       11.借书       12.还书" << '\n';
        cout << "13.查看用户   0.退出并保存" << '\n';
        cout << "请选择：";

        if(!(cin >> choice)) // 输入非数字：清错误状态后重新选择
        {
            cin.clear();
            eatLine();
            cout << "输入无效，请输入数字选项！" << '\n';
            continue;
        }
        eatLine();

        if(choice == 0)
        {
            lib.saveData(); // 退出保存：覆盖写回 books.txt / users.txt
            cout << "感谢使用，再见！" << '\n';
            return 0;
        }

        switch(choice)
        {
        case 1: // 添加图书
        {
            string name, publisher, author, isbn;
            double price = 0.0;
            int page = 0;
            cout << "请输入书名：";          getline(cin, name);
            cout << "请输入出版社：";        getline(cin, publisher);
            cout << "请输入作者：";          getline(cin, author);
            cout << "请输入ISBN（13位）：";  getline(cin, isbn);
            cout << "请输入价格：";          cin >> price;
            cout << "请输入页数：";          cin >> page;
            eatLine();
            lib.addBook(Book(name, publisher, author, isbn, price, page, true));
            break;
        }
        case 2: // 删除图书
        {
            string isbn;
            cout << "请输入要删除的图书 ISBN：";
            getline(cin, isbn);
            lib.removeBook(isbn);
            break;
        }
        case 3: // 查询图书
        {
            string isbn;
            cout << "请输入要查询的图书 ISBN：";
            getline(cin, isbn);
            Book* book = lib.findBook(isbn);
            if(book != nullptr)
            {
                book->PrintBookInformation();
            }
            break;
        }
        case 4: // 列出全部图书
            lib.printAll();
            break;
        case 5: // 添加用户
        {
            string type, name, department;
            long long id = 0;
            cout << "用户类型（S=学生 / T=教师）："; getline(cin, type);
            cout << "请输入姓名：";  getline(cin, name);
            cout << "请输入院系：";  getline(cin, department);
            cout << "请输入ID：";    cin >> id;
            eatLine();
            if(type == "S" || type == "s")
            {
                lib.addUser(new Student(name, department, id));
            }
            else if(type == "T" || type == "t")
            {
                lib.addUser(new Teacher(name, department, id));
            }
            else
            {
                cout << "类型无效，添加失败！" << '\n';
            }
            break;
        }
        case 6: // 删除用户
        {
            long long id = 0;
            cout << "请输入要删除的用户 ID：";
            cin >> id;
            eatLine();
            lib.removeUser(id);
            break;
        }
        case 7: // 修改图书
        {
            string isbn, name, author, publisher;
            double price = 0.0;
            int page = 0;
            cout << "请输入要修改的图书 ISBN："; getline(cin, isbn);
            cout << "新的书名：";    getline(cin, name);
            cout << "新的作者：";    getline(cin, author);
            cout << "新的出版社：";  getline(cin, publisher);
            cout << "新的价格：";    cin >> price;
            cout << "新的页数：";    cin >> page;
            eatLine();
            lib.updateBook(isbn, name, author, publisher, price, page);
            break;
        }
        case 8: // 修改用户
        {
            long long id = 0;
            string name, department;
            cout << "请输入要修改的用户 ID：";
            cin >> id;
            eatLine();
            cout << "新的姓名：";  getline(cin, name);
            cout << "新的院系：";  getline(cin, department);
            lib.updateUser(id, name, department);
            break;
        }
        case 9: // 登录
        {
            long long id = 0;
            cout << "请输入登录 ID：";
            cin >> id;
            eatLine();
            lib.login(id);
            break;
        }
        case 10: // 登出
        {
            long long id = 0;
            cout << "请输入登出 ID：";
            cin >> id;
            eatLine();
            lib.logout(id);
            break;
        }
        case 11: // 借书（当前登录用户）
        case 12: // 还书（当前登录用户）
        {
            User* user = lib.getCurrentUser();
            if(user == nullptr)
            {
                cout << "请先登录（选项9），借还操作针对当前登录用户！" << '\n';
                break;
            }
            string bookname, date1, date2;
            cout << "请输入书名：";
            getline(cin, bookname);
            if(choice == 11)
            {
                cout << "请输入借阅日期（YYYY-MM-DD）："; getline(cin, date1);
                cout << "请输入应还日期（YYYY-MM-DD）："; getline(cin, date2);
                lib.borrowBook(bookname, *user, date1, date2);
            }
            else
            {
                cout << "请输入还书日期（YYYY-MM-DD）："; getline(cin, date1);
                lib.returnbook(bookname, *user, date1);
            }
            break;
        }
        case 13: // 查看用户信息
        {
            long long id = 0;
            cout << "请输入要查看的用户 ID：";
            cin >> id;
            eatLine();
            User* user = lib.findUser(id);
            if(user != nullptr)
            {
                lib.printUserinformation(*user);
            }
            break;
        }
        default:
            cout << "无效选项，请重新选择！" << '\n';
            break;
        }
    }
}
