#include<iostream>
#include<string>
#include "Student.h"
using namespace std;
Student::Student()
{
    this -> name = "";
    this -> department = "";
    this -> number = 0;
    this -> max = 5;
    this -> borrowcount = 0;
}
Student::Student(string name , string department , long long number)
{
    this -> name = move(name);
    this -> department = move(department);
    this -> number = number;
    this -> max = 5;
    this -> borrowcount = 0;
}
void Student::borrow(Book& book,string initialdate,string returndate)
{
    if(borrowcount < 5)
    {
        book.GetOut(name , number , initialdate, returndate);
        borrowcount ++;
    }
    else 
    {
        cout << "Sorry , you can not borrow any more book now !" << endl;
    }
}
void Student::returnbook(Book& book , string returndate)
{
    std::string s = book.getReturndate();
    // 不考虑年份不同的情况了
    if(s[5] == returndate[5] && s[6] == returndate[6])
    {
        int date1 = (returndate[8] - '0') * 10 + (returndate[9] - '0');
        int date2 = (s[8] - '0') * 10 + (s[9] - '0');
        int t = date2 - date1;
        book.GetIn(name,number);
        borrowcount --;
        if(t >= 0 )
        {
            std::cout << "You've returned book in time !" << std::endl;
        }
        else
        {
            long long price = book.getPrice();
            long long pay = (price / 10.0) * (date1- date2);
            std::cout << "Sorry, you're mot return this book in time ! We have the rule followed as :" << std::endl;
            std::cout << "For each day you are not return , you must pay 1/10 money of the book !" << std::endl;
            std::cout << "So , you have to pay :" << pay << std::endl;
        }
    }
    else
    {
        int month1 = (returndate[5] - '0') * 10 + (returndate[6] - '0');
        int month2 = (s[5] - '0') * 10 + (s[6] - '0');
        int day1 = (returndate[8] - '0') * 10 + (returndate[9] - '0');
        int day2 = (s[8] - '0') * 10 + (s[9] - '0');
        int t = 0;
        book.GetIn(name,number);
        borrowcount --;
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
            long long price = book.getPrice();
            long long pay = (price / 10.0) * (0 - t);
            std::cout << "Sorry, you're mot return this book in time ! We have the rule followed as :" << std::endl;
            std::cout << "For each day you are not return , you must pay 1/10 money of the book !" << std::endl;
            std::cout << "So , you have to pay :" << pay << std::endl;
        }
    }
}
