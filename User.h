#pragma once
#include<string>
#include<ostream>
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
    bool dateToDays(const string& date, int& days); // 校验日期并转换为天数

private:
    int daysFromCivil(int y , int m , int d); // 仅供 dateToDays 内部调用

public:
    User();
    User(string name , string department , long long ID , int max , int current);
    virtual ~User() = default;

    // 公共接口
    virtual void borrow(Book& book , string initialdate , string returndate);
    // 教师能够续借，学生不能，用作多态的区分
    virtual void returnbook(Book& book , string returndate);
    void getUserInformation() const;

    // 获取相关的数据
    virtual double getDivisor() const = 0;
    virtual string getUserType() const = 0;
    string getName() const;
    string getDepartment() const;
    long long getID() const;
    int getMax() const;
    int getCurrent() const;
    friend class Library; // 持久化恢复时修正 current 计数
    // 实验六：序列化下沉到类成员；经虚函数 getUserType() 写类型标记，一份实现覆盖全部派生类
    void saveTo(std::ostream& os) const;
    static User* loadFrom(const std::string& line); // 工厂：按类型标记 new 派生类对象

};

// 非成员运算符重载：经基类引用输出，虚函数 getUserType() 体现学生/教师差异
std::ostream& operator<<(std::ostream& os, const User& user);

    
