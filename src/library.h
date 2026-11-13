#pragma once
#include <string>
#include <vector>
#include "book.h" 
#include "User.h"
using namespace std;

class Library
{
private:

    vector<User*> users; // Library 接管所有权，析构时统一释放
    // vector<User> currentUsers;
    vector<Book> books;

    std::string libname;
    std::string address;
    std::string phone;

public:
    // 构造函数、析构函数、禁止拷贝
    Library();
    Library(std::string libraryname, std::string libraryaddress, std::string libraryphone);
    ~Library(); // 释放 users 中全部用户对象
    Library(const Library&) = delete; // 禁止拷贝构造，避免双重释放
    Library& operator=(const Library&) = delete; // 禁止拷贝赋值，避免双重释放

    void addBook(const Book& book);
    void outBook(const Book& book);
    bool removeBook(const std::string& isbn);

    // 返回的指针仅在 books 不发生扩容/删除期间有效
    Book* findBook(const std::string& ISBN);
    void printAll() const;

    // 借还
    void borrowBook(string bookname , User& user , string initialdate , string returndate);
    void returnbook(string bookname , User& user , string returndate);
    // 续借
    bool renewBook(const std::string& bookname, User& user); // 续借：经多态区分学生/教师
    // 查询
    void searchBooks(const std::string& keyword) const;      // 按书名/作者关键词查询
    std::string findISBN(const std::string& name);

    // 用户相关接口，Library 接管传入对象的所有权
    void addUser(User* user);
    User* findUser(long long id);
    bool removeUser(long long id); // 还有未还图书时拒绝删除
    bool updateUser(long long id, const std::string& name, const std::string& department);
    bool updateBook(const std::string& isbn, const std::string& name, const std::string& author,
                    const std::string& publisher, double price, int page); // 不影响借出状态
    void printUserinformation(User& user) const;
    void printBorrowList(const User& user) const; // 查询用户借阅书籍及每本的还书日期、是否逾期
    // 显式清空：释放全部用户、清空图书，调用后 findUser/findBook 返回的旧指针全部失效
    void clear();
    
    // 启动加载：从 path 目录下的 users.txt、books.txt 恢复数据；文件缺失或为空时从空数据开始
    bool loadData(const std::string& path = ".");
    // 退出保存：覆盖写回 path 目录下的 books.txt、users.txt
    bool saveData(const std::string& path = ".");
};
