#pragma once
#include "User.h"
using namespace std;

class Teacher : public User
{
public:
    // 构造函数
    Teacher();
    Teacher(string name , string department , long long ID);

    // 获取数据
    double getDivisor() const override;
    string getUserType() const override;
    int getRenewDays() const override; // 续借上限为 7 天：教师在此范围内输入续借天数
    // 借还重写
    void borrow(Book& book , string initialdate , string returndate) override;
    void returnbook(Book& book , string returndate) override;
};