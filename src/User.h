#pragma once
#include<string>
#include<ostream>
#include<vector>
#include"book.h"
using namespace std;
class User
{
protected:
    // 用户基本信息
    string name;
    string department;
    long long ID;
    int max; //  最大的借阅数量
    int current; // 当前已借阅数量
    vector<string> borrowedBooks; // 当前借阅的书名列表
    static bool dateToDays(const string& date, int& days); // 校验日期并转换为天数（不依赖对象状态）

private:
    static int daysFromCivil(int y , int m , int d); // 仅供 dateToDays 内部调用(辅助函数，对外不暴露)

public:
    // 自动日期：借书只输天数、还书自动取当天，日期由系统生成
    static bool today(std::string& out); // 获取当前日期 YYYY-MM-DD（本地时区）
    static bool addDays(const std::string& base, int n, std::string& out); // 日期加 n 天，返回 YYYY-MM-DD
    // 构造函数
    User();
    User(string name , string department , long long ID , int max , int current);
    // 虚析构函数：基类指针 delete 派生类对象时调用派生类析构函数
    virtual ~User() = default;

    // 公共接口
    virtual void borrow(Book& book , string initialdate , string returndate);
    virtual void returnbook(Book& book , string returndate);

    // 续借
    bool renew(Book& book); // 续借：非虚，天数经纯虚函数 getRenewDays() 多态区分
    virtual int getRenewDays() const = 0; // 续借上限：学生 0（不支持），教师 7

    void getUserInformation() const;

    // 获取相关的数据
    virtual double getDivisor() const = 0;
    virtual string getUserType() const = 0;

    string getName() const;
    string getDepartment() const;
    long long getID() const;
    int getMax() const;
    int getCurrent() const;
    const vector<string>& getBorrowedBooks() const; // 当前借阅的书名列表
    friend class Library; // 持久化恢复时修正 current 计数
    // 实验六：经虚函数 getUserType() 写类型标记，一份实现覆盖全部派生类
    void saveTo(std::ostream& os) const;
    static User* loadFrom(const std::string& line); // 按类型标记 new 派生类对象

};
// 类外
// 非成员运算符重载：经基类引用输出，虚函数 getUserType() 体现学生/教师差异
std::ostream& operator<<(std::ostream& os, const User& user);

    
