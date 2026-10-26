#include<iostream>
#include<string>
#include<iomanip>
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

// 老师续借
void Teacher::borrow(Book& book , string initialdate,string returndate)
{
    cout << "【教师通道】" << '\n';
    cout << "欢迎您！您是本校教师可以享受续借服务！" << '\n';
    cout << "如果您未能在还书日期内完成还书！您可以自动续借至多一周！" << endl;
    
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
void Teacher::returnbook(Book& book,string returndate)
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
        if(day <= 7)
        {
            cout << "由于您是教师,您可以享受逾期自动续借服务!" << '\n' << "且本次逾期时长:" << day << "天,未超出一周!" << '\n';
            cout << "您无需支付任何费用!" << endl;
            book.GetIn(getName(),getID());  
        }
        else
        {
        double pay = (day - 7) * book.getPrice() * getDivisor();
        cout << "非常抱歉，您未能按规定日期完成还书！且您逾期时间过长: "<< day << "根据相关规定：" << '\n' << "       因为您是：" << getUserType() << "所以您将按照每本书每天" << getDivisor() << "的比例支付超时费用！" << endl;
        if(pay >= book.getPrice())
        {
            cout << "由于您逾期时间为(已自动减去续借时间)：" << day << "所付金额超出了本书价格！" << '\n' << "因此，您只需支付本书的价格！" << endl;
            cout << "本书价格为：" << fixed << setprecision(2) << book.getPrice() << endl;
        }
        else
        {
            cout << "您需要支付的金额为(已自动减去续借时间)：" << fixed << setprecision(2) << pay << endl;
        }
        }
        
    }
}