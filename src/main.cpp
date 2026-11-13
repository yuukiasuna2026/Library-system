#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <limits>
#ifdef _WIN32
#include <windows.h>
#endif
#include "book.h"
#include "library.h"
#include "Student.h"
#include "Teacher.h"
#include "Admin.h"
using namespace std;

static void eatLine() // 吃掉一行残留输入（cin >> 之后用）
{
    cin.ignore(1024, '\n');
}

constexpr int MAX_ATTEMPTS = 3; // 管理员连续输错次数上限

// 读取菜单选择：非数字输入清错误状态后返回 -1
static int readChoice()
{
    int choice = -1;
    if(!(cin >> choice)) // 输入非数字：清错误状态后重新选择
    {
        cin.clear(); // 用clear重置错误状态
        eatLine(); // 吃掉残留的错误输入和换行符
        cout << "输入无效，请输入数字选项！" << '\n';
        return -1;
    }
    eatLine();
    return choice;
}

// admins.txt：账号|密码，一行一个；格式非法的行跳过并计数
static bool loadAdmins(vector<Admin>& admins)
{
    ifstream in("data/admins.txt"); // 数据文件统一放在 data/ 目录
    if(!in)
    {
        return false; // 文件缺失
    }
    string line;
    int bad = 0;
    while(getline(in, line))
    {
        if(line.empty())
        {
            continue;
        }
        size_t pos = line.find('|');
        if(pos == string::npos || pos == 0 || pos + 1 >= line.size())
        {
            bad++; // 没有分隔符、账号为空或密码为空
            continue;
        }
        admins.emplace_back(line.substr(0, pos), line.substr(pos + 1));
    }
    if(bad > 0)
    {
        cout << "警告：admins.txt 有 " << bad << " 行格式非法，已跳过！" << '\n';
    }
    return !admins.empty(); // 文件为空或全部非法时视为缺失
}

static void saveAdmins(const vector<Admin>& admins)
{
    ofstream out("data/admins.txt");
    if(!out)
    {
        cout << "警告：admins.txt 打开失败，管理员数据未保存！" << '\n';
        return;
    }
    for(const Admin& admin : admins)
    {
        admin.saveTo(out); // 序列化由 Admin 自己负责
    }
}

// 退出并保存全部数据
static void saveAndExit(Library& lib, const vector<Admin>& admins)
{
    lib.saveData("data"); // 覆盖写回 data/books.txt、data/users.txt
    saveAdmins(admins); // 覆盖写回 admins.txt
    cout << "感谢使用，再见！" << '\n';
    exit(0);
}

// 管理员界面：只有管理功能，没有借还功能
static void adminMenu(Library& lib, const vector<Admin>& admins)
{
    while(true)
    {
        cout << "\n========== 管理员界面 ==========" << '\n';
        cout << " 1.添加图书    2.删除图书    3.修改图书" << '\n';
        cout << " 4.添加用户    5.删除用户    6.修改用户" << '\n';
        cout << " 7.列出全部图书    8.返回用户界面    0.退出并保存" << '\n';
        cout << "请选择：";

        int choice = readChoice();
        if(choice == -1)
        {
            continue;
        }

        switch(choice)
        {
        case 0: // 退出并保存
            saveAndExit(lib, admins);
            break;
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
        case 3: // 修改图书
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
        case 4: // 添加用户
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
        case 5: // 删除用户
        {
            long long id = 0;
            cout << "请输入要删除的用户 ID：";
            cin >> id;
            eatLine();
            lib.removeUser(id);
            break;
        }
        case 6: // 修改用户
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
        case 7: // 列出全部图书
            lib.printAll();
            break;
        case 8: // 返回用户界面
            cout << "已返回用户界面！" << '\n';
            return;
        default:
            cout << "无效选项，请重新选择！" << '\n';
            break;
        }
    }
}

// 普通用户界面：借还、查询；管理员从这里登录后切换到管理员界面
static void userMenu(Library& lib, vector<Admin>& admins)
{
    while(true)
    {
        cout << "\n========== 图书馆借阅管理系统（用户界面）==========" << '\n';
        cout << " 1.借书    2.还书    3.查询图书（ISBN/书名/作者）    4.列出全部图书" << '\n';
        cout << " 5.查询用户借阅    6.查询借阅与还书日期    7.续借" << '\n';
        cout << " 9.管理员登录    0.退出并保存" << '\n';
        cout << "请选择：";

        int choice = readChoice();
        if(choice == -1)
        {
            continue;
        }

        switch(choice)
        {
        case 0: // 退出并保存
            saveAndExit(lib, admins);
            break;
        case 1: // 借书（刷卡通型：操作时输入用户 ID；只输借阅天数，日期自动生成）
        {
            long long id = 0;
            cout << "请刷入用户 ID：";
            cin >> id;
            eatLine();
            User* user = lib.findUser(id); // 即时验证身份，不保留登录状态
            if(user == nullptr)
            {
                break;
            }
            string bookname;
            cout << "请输入书名：";
            getline(cin, bookname);
            int days = 0;
            cout << "请输入借阅天数：";
            if(!(cin >> days))
            {
                cin.clear();
                eatLine();
                cout << "输入无效，请输入借阅天数！" << '\n';
                break;
            }
            eatLine();
            if(days < 1 || days > 365)
            {
                cout << "借阅天数必须在 1~365 之间！" << '\n';
                break;
            }
            string borrowDate, dueDate;
            if(!User::today(borrowDate) || !User::addDays(borrowDate, days, dueDate))
            {
                cout << "获取系统日期失败，操作取消！" << '\n';
                break;
            }
            cout << "借阅日期：" << borrowDate << "，应还日期：" << dueDate << '\n';
            lib.borrowBook(bookname, *user, borrowDate, dueDate);
            break;
        }
        case 2: // 还书（自动取系统当天日期，逾期与罚款自动计算）
        {
            long long id = 0;
            cout << "请刷入用户 ID：";
            cin >> id;
            eatLine();
            User* user = lib.findUser(id);
            if(user == nullptr)
            {
                break;
            }
            string bookname;
            cout << "请输入书名：";
            getline(cin, bookname);
            string returnDate;
            if(!User::today(returnDate))
            {
                cout << "获取系统日期失败，操作取消！" << '\n';
                break;
            }
            cout << "还书日期：" << returnDate << '\n';
            lib.returnbook(bookname, *user, returnDate);
            break;
        }
        case 3: // 查询图书：13 位纯数字按 ISBN 精确查，否则按书名/作者关键词模糊查
        {
            string key;
            cout << "请输入 ISBN、书名或作者关键词：";
            getline(cin, key);
            bool isIsbn = key.size() == 13;
            if(isIsbn)
            {
                for(char c : key)
                {
                    if(c < '0' || c > '9')
                    {
                        isIsbn = false;
                        break;
                    }
                }
            }
            if(isIsbn)
            {
                Book* book = lib.findBook(key);
                if(book != nullptr)
                {
                    book->PrintBookInformation();
                }
            }
            else
            {
                lib.searchBooks(key);
            }
            break;
        }
        case 4: // 列出全部图书
            lib.printAll();
            break;
        case 5: // 查询用户借阅情况
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
        case 6: // 查询借阅书籍及还书日期（含是否逾期）
        {
            long long id = 0;
            cout << "请输入要查询的用户 ID：";
            cin >> id;
            eatLine();
            User* user = lib.findUser(id);
            if(user != nullptr)
            {
                lib.printBorrowList(*user);
            }
            break;
        }
        case 7: // 续借（刷卡通型；学生将被拒绝，教师输入 1～7 天在原应还日期上延长）
        {
            long long id = 0;
            cout << "请刷入用户 ID：";
            cin >> id;
            eatLine();
            User* user = lib.findUser(id); // 即时验证身份
            if(user == nullptr)
            {
                break;
            }
            string bookname;
            cout << "请输入书名：";
            getline(cin, bookname);
            lib.renewBook(bookname, *user);
            break;
        }
        case 9: // 管理员登录：校验成功后切换到管理员界面
        {
            string account, password;
            int attempts = 0;
            bool success = false;
            while(attempts < MAX_ATTEMPTS)
            {
                cout << "请输入管理员账号："; getline(cin, account);
                cout << "请输入管理员密码："; getline(cin, password);
                for(const Admin& admin : admins)
                {
                    if(admin.check(account, password))
                    {
                        success = true;
                        break;
                    }
                }
                if(success)
                {
                    break;
                }
                attempts++;
                cout << "账号或密码错误，已尝试 " << attempts << "/" << MAX_ATTEMPTS << " 次！" << '\n';
            }
            if(success)
            {
                cout << "管理员登录成功，已进入管理员界面！" << '\n';
                adminMenu(lib, admins); // 进入管理员界面，返回用户界面后回到本循环
            }
            else
            {
                cout << "尝试次数过多，本次登录失败，请重新选择登录！" << '\n';
            }
            break;
        }
        default:
            cout << "无效选项，请重新选择！" << '\n';
            break;
        }
    }
}

int main()
{
// 解决Windows控制台中文乱码的问题
#ifdef _WIN32 // Windows 控制台默认使用 GBK，中文输出乱码，需切换为 UTF-8
    SetConsoleOutputCP(CP_UTF8);  // 输出 UTF-8
    SetConsoleCP(CP_UTF8);        // 输入也 UTF-8（需要 cin 中文时）
#endif

    // 实验六：启动加载——从 books.txt / users.txt 恢复数据（文件缺失则从空数据开始）
    Library lib;
    lib.loadData("data"); // 从 data/ 目录恢复数据

    // 加载管理员账号：admins.txt 缺失、为空或全部非法时，创建默认管理员
    vector<Admin> admins;
    if(!loadAdmins(admins))
    {
        admins.emplace_back("admin", "123456");
        cout << "未找到有效的 admins.txt，已启用默认管理员账号 admin（密码 123456）！" << '\n';
    }

    userMenu(lib, admins); // 从普通用户界面开始
    return 0;
}
