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

    // 公共接口
    virtual void borrow(Book& book , string initialdate , string returndate);
    // 教师能够续借，学生不能，用作多态的区分
    virtual void returnbook(Book& book , string returndate);
    virtual void getUserInformation() const;
    int daysFromCivil(int y , int m , int d);

    // 获取相关的数据
    virtual double getDivisor() const;
    virtual string getUserType() const;
    virtual string getName() const;
    virtual string getDepartment() const;
    virtual long long getID() const;
    virtual int getMax() const;
    virtual int getCurrent() const;
    
};

    
