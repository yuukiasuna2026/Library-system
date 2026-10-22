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