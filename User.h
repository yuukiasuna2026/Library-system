#pragma once
#include<string>
#include"book.h"
using namespace std;
class User
{
protected:
    string name;
    string department;
    long long ID;
    int max; //  最大的借阅数量
    int current; // 当前已借阅数量
    
public:
    User();
    User(string name , string department , long long ID , int max , int current);
    virtual ~User() = default;

    // 获取相关的数据
    virtual string getName() const;
    virtual string getDepartment() const;
    virtual long long getID() const;
    virtual int getMax() const;
    virtual int getCurrent() const;
    virtual double getDivisor() const = 0;
    virtual string getUserType() const = 0;

    // 公共接口
    void borrow(Book& book , string initialdate , string returndate);
    void returnbook(Book& book , string returndate);
    
};
