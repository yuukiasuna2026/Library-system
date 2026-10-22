#include<iostream>
#include<string>
#include "Teacher.h"

// 构造函数
Teacher::Teacher()
{
    this -> name = "";
    this -> department = "";
    this -> ID = 0;
    this -> max = 10;
    this -> current = 0;
}
Teacher::Teacher(string name , string department , long long ID)
: User(name , department , ID , 10 ,0)
{}

// 获取数据
double Teacher::getDivisor() const
{
    return 0.01;
}
string Teacher::getUserType() const
{
    return "教师";
}