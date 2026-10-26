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
    if(getCurrent() < getMax()) // 按照各自的权限
    {
        book.GetOut(getName() , getID() , initialdate , returndate);
        current++;
    }
    else 
    {
        cout << "很抱歉，您已经到达最大的借阅数量！请先将已借阅的图书归还！" << endl;
    }
}

// 利用daysfromcivil算法改进日期问题
int User::daysFromCivil(int y,int m,int d)
{
    y -= m <= 2; // bool类型 true和false隐形转化为 0和 1
    int era = (y >= 0 ? y : y - 399) / 400; // 400为一纪元 处理公元前负数年份情况
    unsigned yoe = y - era * 400; // 当前的year处于纪元的第几年 year of era
    unsigned doy = (153 * (m + (m >= 2 ? -3 : 9)) + 2) / 5 + d - 1; // 当前处于该年的第几天 day of year
    unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy; // 该纪元第几天 day of era
    return era * 146097 + (int)doe - 719468;
}
void User::returnbook(Book& book , string returndate)
{
    // 规定的还书日期
    string returndate_old = book.getReturndate(); // 日期 xxxx-xx-xx
    int y_old = (returndate_old[0] - '0') * 10 * 10 * 10 + (returndate_old[1] - '0') * 10 * 10 + (returndate_old[2] - '0') * 10 + (returndate_old[3] - '0');
    int m_old = (returndate_old[5] - '0') * 10 + (returndate_old[6] - '0');
    int d_old = (returndate_old[8] - '0') * 10 + (returndate_old[9] - '0');
    int old = daysFromCivil(y_old,m_old,d_old);

    // 现在的日期
    string year_sub = returndate.substr(0,4);
    string mmonth_sub = returndate.substr(5,2);
    string day_sub = returndate.substr(8,2);
    int y_now = stoi(year_sub);
    int m_now = stoi(mmonth_sub);
    int d_now = stoi(day_sub);
    int now = daysFromCivil(y_now,m_now,d_now);

    int day = now - old;
    if(day <= 0)
    {
        book.GetIn(getName(),getID());
        cout << "恭喜您！您成功在规定时间内完成还书！" << endl;
    }
    else
    {
        double pay = day * book.getPrice() * getDivisor();
        cout << "非常抱歉，您未能按规定日期完成还书！根据相关规定：" << '\n' << "       因为您是：" << getUserType() << "所以您将按照每本书每天" << getDivisor() << "的比例支付超时费用！" << endl;
        if(pay >= book.getPrice())
        {
            cout << "由于您逾期时间为：" << day << "所付金额超出了本书价格！" << '\n' << "因此，您只需支付本书的价格！" << endl;
            cout << "本书价格为：" << fixed << setprecision(2) << book.getPrice() << endl;
        }
        else
        {
            cout << "您需要支付的金额为：" << fixed << setprecision(2) << pay << endl;
        }
    }
}
void User::getUserInformation() const
{
    cout << "该用户的名字：" << name << endl;
    cout << "该用户的院系：" << department << endl;
    cout << "该用户的ID：" << ID << endl;
    cout << "该用户的借阅数：" << current << "/" << max << endl;
}
