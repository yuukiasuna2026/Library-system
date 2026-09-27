#pragma once
#include<string>
#include "book.h"
using namespace std;
class Student
{
private:
    string name;
    string department;
    long long number;
    int max;
    int borrowcount;
public:
    Student();
    Student(string mane,string department , long long number);
    void borrow(Book& book,string initialdate,string returndate);
    void returnbook(Book& book , string returndate);
};
