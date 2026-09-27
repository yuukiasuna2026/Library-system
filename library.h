#pragma once
#include <string>
#include "book.h"

class Library
{
private:
    std::string libname;
    std::string address;
    std::string phone;
    Book books[100];
    int bookcount;

public:
    Library();
    Library(std::string libraryname, std::string libraryaddress, std::string libraryphone);
    void addBook(const Book& book);
    void outBook(const Book& book);
    Book* findBook(const std::string& ISBN);
    void printAll() const;

    void borrowBook(std::string bookname, std::string stuname, long long stunumber,
                    std::string initialdate, std::string returndate);
    void returnBook(std::string bookname, std::string stuname, long long stunumber,
                    std::string returndate);
    std::string findISBN(const std::string& name);
};
