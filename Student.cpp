#include<iostream>
#include<string>
#include "Student.h"
using namespace std;

// 构造函数
Student::Student()
{
    this -> name = "";
    this -> department = "";
    this -> ID = 0;
    this -> max = 5;
    this -> current = 0;
}
Student::Student(string name , string department , long long ID)
: User(name , department , ID , 5 , 0 ) // 初始化列表
{}

// 获取数据
double Student::getDivisor() const 
{
    return 0.05;
}
string Student::getUserType() const
{
    return "学生";
}

// 学生的借还
void Student::borrow(Book& book , string initialdate , string returndate)
{
    cout << "【学生通道】" << '\n';
    cout << "欢迎您！您是本校的学生！请在规定时间内还书否则将会面临罚款！" << endl;

    User::borrow(book, initialdate, returndate);// 后续调用基类
}
// 还书调用基类版本，和教师区分