#include<iostream>
#include<string>
#include<iomanip> // 用于设置输出的精度
#include "User.h"
using namespace std;

// 构造函数
User::User()
{
    this -> name = "";
    this -> department = "";
    this -> ID = 0;
    this -> max = 0;
    this -> current = 0;
}
User::User(string name , string department , long long ID , int max , int current)
{
    this -> name = move(name);
    this -> department = move(department);
    this -> ID = ID;
    this -> max = max;
    this -> current = current;
}

// 获取相关的数据
string User::getName() const
{
    return name;
}
string User::getDepartment() const
{
    return department;
}
long long User::getID() const
{
    return ID;
}
int User::getMax() const
{
    return max;
}
int User::getCurrent() const
{
    return current;
}
double User::getDivisor() const
{
    return 0;
}
string User::getUserType() const
{
    return "User";
}

// 纯虚函数 ：
// vitual int getDivisor() const = 0;
// vitual string getUserType() const = 0;
// 在基类中不需要实现，在派生类中具体实现 

// 公共接口
void User::borrow(Book& book , string initialdate , string returndate)
{
    if(getCurrent() < getMax())
    {
        book.GetOut(getName() , getID() , initialdate , returndate);
        current++;
    }
    else 
    {
        cout << "很抱歉，您已经到达最大的借阅数量！请先将已借阅的图书归还！" << endl;
    }
}
void User::returnbook(Book& book , string returndate)
{
    string s = book.getReturndate();
    // 不考虑年份不同的情况了
    if(s[5] == returndate[5] && s[6] == returndate[6])
    {
        int date1 = (returndate[8] - '0') * 10 + (returndate[9] - '0');
        int date2 = (s[8] - '0') * 10 + (s[9] - '0');
        int t = date2 - date1;
        book.GetIn(getName(), getID());
        current--;
        if(t >= 0 )
        {
            cout << "您成功归还了该图书！" << endl;
        }
        else
        {
            double price = book.getPrice();
            double pay = price * getDivisor() * (date1- date2);
            cout << "很抱歉，您未能按时归还该图书！根据图书馆的相关规定：" << endl;
            cout << "      对于每一天未按时归还的图书,您必须支付图书价格的" << getDivisor() << "费用！" << endl;
            cout << "因此，您需要支付：" << fixed << setprecision(2) << pay << endl;
        }
    }
    else
    {
        int month1 = (returndate[5] - '0') * 10 + (returndate[6] - '0');
        int month2 = (s[5] - '0') * 10 + (s[6] - '0');
        int day1 = (returndate[8] - '0') * 10 + (returndate[9] - '0');
        int day2 = (s[8] - '0') * 10 + (s[9] - '0');
        int t = 0;
        book.GetIn(getName(), getID());
        current--;
        // 统一一个月30天 
        if(day2 - day1 < 0)
        {
            month1--;
            day2 += 30;
            t = (day2 - day1) + (month2 - month1) * 30;
        }
        else
        {
            t = (day2 - day1) + (month2 -month1) * 30;
        }
        if(t >= 0 )
        {
            cout << "您成功归还了该图书！" << endl;
        }
        else
        {
            double price = book.getPrice();
            double pay = price * getDivisor() * (0 - t);
            cout << "很抱歉，您未能按时归还该图书！根据图书馆的相关规定：" << endl;
            cout << "      对于每一天未按时归还的图书,您必须支付图书价格的" << getDivisor() << "费用！" << endl;
            cout << "因此，您需要支付：" << fixed << setprecision(2) << pay << endl;
        }
    }
}
