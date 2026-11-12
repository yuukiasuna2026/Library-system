#pragma once
#include "User.h"
using namespace std;

class Student : public User
{
public:
    // 构造函数
    Student();
    Student(string name,string department , long long ID);
    
    // 获取相关的数据
    double getDivisor() const override;
    string getUserType() const override;
    int getRenewDays() const override; // 学生不支持续借：返回 0

    // 学生无特殊服务
    void borrow(Book& book , string initialdate , string returndate) override;
    
};
