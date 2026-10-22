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
};