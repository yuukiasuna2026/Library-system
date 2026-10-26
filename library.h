#pragma once
#include <string>
#include <vector>
#include "Book.h"
#include "User.h"
using namespace std;

class Library
{
private:
    
    vector<User> users;
    vector<User> currentUsers;

    vector<Book> books;
    std::string libname;
    std::string address;
    std::string phone;

public:
    Library();
    Library(std::string libraryname, std::string libraryaddress, std::string libraryphone);
    void addBook(const Book& book);
    void outBook(const Book& book);
    Book* findBook(const std::string& ISBN);
    void printAll() const;
    // // 借还
    // void borrowBook(std::string bookname, std::string stuname, long long stunumber,
    //                 std::string initialdate, std::string returndate);
    // void returnBook(std::string bookname, std::string stuname, long long stunumber,
    //                 std::string returndate);
    std::string findISBN(const std::string& name);

    // 用户相关接口
    void addUser(User& user);
    User* findUser(long long id);
    void printUserinformation(User& user) const;
    bool login(long long userID);
    bool logout(long long userID);
};
