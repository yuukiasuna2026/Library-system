#include <iostream>
#include "library.h"

Library::Library()
{
    this -> libname = "";
    this -> address = "";
    this -> phone = "";
    this -> bookcount = 0;
}
Library::Library(std::string libraryname , std::string libraryaddress , std::string libraryphone)
{
    this -> libname = std::move(libraryname);
    this -> address = std::move(libraryaddress);
    this -> phone = std::move(libraryphone);
    this -> bookcount = 0;
}
void Library::addBook(const Book& book)
{
    if(bookcount < 100)
    {
        books[bookcount] = book;
        bookcount ++;
    }
}
void Library::outBook(const Book& book)
{
    for(int i = 0 ; i < bookcount ; i ++)
    {
        if(books[i].getISBN() == book.getISBN())
        {
            books[i] = books[bookcount - 1];
            bookcount --;
            break;
        }
    }
}
std::string Library::findISBN(const std::string& name)
{
    for( int i = 0 ; i < bookcount ; i ++)
    {
        if(books[i].getName() == name)
        {
            return books[i].getISBN();
        }
    }
    return "";
}
Book* Library::findBook(const std::string& ISBN)
{
    if(Book::checkISBN(ISBN))
    {
        for(int i = 0 ; i < bookcount ; i ++)
        {
            if(books[i].getISBN() == ISBN)
            {
                return &books[i]; 
            }
        }
    }
    else
    {
        std::cout << "The isbn maybe wrong!" << std::endl;
        return nullptr;
    }
    return nullptr;
}
void Library::printAll() const
{
    int count = 1;
    std::cout << "All the books is followed as :" << std::endl;
    for( int i = 0 ; i < bookcount ; i ++)
    {
        std::cout << "Number " << count << "is : " << books[i].getName() << std::endl;
        count ++;
    }
}
void Library::borrowBook(std::string bookname ,std::string stuname,long long stunumber,std::string initialdate,std::string returndate)
{
    std::string s = findISBN(bookname);
    Book* b = findBook(s);
    b -> GetOut(stuname,stunumber,initialdate,returndate);
}
void Library::returnBook(std::string bookname , std::string stuname , long long stunumber , std::string returndate)
{
    std::string isbn = findISBN (bookname);
    Book* b = findBook(isbn);
    if (b == nullptr)
    {
        return;
    }

    std::string dueDate = b -> getReturndate();
    // 不考虑年份不同的情况了
    if(dueDate[5] == returndate[5] && dueDate[6] == returndate[6])
    {
        int date1 = (returndate[8] - '0') * 10 + (returndate[9] - '0');
        int date2 = (dueDate[8] - '0') * 10 + (dueDate[9] - '0');
        int t = date2 - date1;
        if(b == nullptr)
        {
            std::cout << "The book is not found!" << std::endl;
            return;
        }
        b -> GetIn(stuname,stunumber);
        if(t >= 0 )
        {
            std::cout << "You've returned book in time !" << std::endl;
        }
        else
        {
            long long price = b -> getPrice();
            long long pay = (price * 1LL / 10) * (date1 - date2);
            std::cout << "Sorry, you're mot return this book in time ! We have the rule followed as :" << std::endl;
            std::cout << "For each day you are not return , you must pay 1/10 money of the book !" << std::endl;
            std::cout << "So , you have to pay :" << pay << std::endl;
        }
    }
    else
    {
        int month1 = (returndate[5] - '0') * 10 + (returndate[6] - '0');
        int month2 = (dueDate[5] - '0') * 10 + (dueDate[6] - '0');
        int day1 = (returndate[8] - '0') * 10 + (returndate[9] - '0');
        int day2 = (dueDate[8] - '0') * 10 + (dueDate[9] - '0');
        int t = 0;
        b -> GetIn(stuname,stunumber);
        // 统一一个月30天 
        if(day2 - day1 < 0)
        {
            month1--;
            day2 += 30;
            t = (day2 - day1) + (month2 - month1) * 30;
        }
        else
        {
            t = (day2 - day1) + (month2 -month1) * 30;
        }
        if(t >= 0 )
        {
            std::cout << "You've returned book in time !" << std::endl;
        }
        else
        {
            long long price = b -> getPrice();
            long long pay = (price * 1LL / 10) * (0 - t);
            std::cout << "Sorry, you're mot return this book in time ! We have the rule followed as :" << std::endl;
            std::cout << "For each day you are not return , you must pay 1/10 money of the book !" << std::endl;
            std::cout << "So , you have to pay :" << pay << std::endl;
        }
    }
}