#include<iostream>
#include<string>
#include<iomanip> // 用于设置输出的精度
#include<sstream>
#include<vector>
#include "User.h"
#include "Student.h"
#include "Teacher.h"
using namespace std;

namespace
{
    vector<string> splitLine(const string& line) // 按 '|' 切分字段
    {
        vector<string> fields;
        string field;
        istringstream ss(line);
        while(std::getline(ss, field, '|'))
        {
            fields.push_back(field);
        }
        if(!line.empty() && line.back() == '|') // getline 会丢弃末尾的空字段
        {
            fields.push_back("");
        }
        return fields;
    }
}

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
// 纯虚函数 ：
// vitual int getDivisor() const = 0;
// vitual string getUserType() const = 0;
// 在基类中不需要实现，在派生类中具体实现 

bool User::dateToDays(const string& date, int& days)
{
    if(date.size() != 10 || date[4] != '-' || date[7] != '-')
    {
        return false;
    }

    for(int i = 0; i < 10; i++)
    {
        if(i == 4 || i == 7)
        {
            continue;
        }
        if(date[i] < '0' || date[i] > '9')
        {
            return false;
        }
    }

    int year = stoi(date.substr(0,4));
    int month = stoi(date.substr(5,2));
    int day = stoi(date.substr(8,2));
    if(month < 1 || month > 12)
    {
        return false;
    }

    static const int daysInMonth[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    int maxDay = daysInMonth[month];
    bool leap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    if(month == 2 && leap)
    {
        maxDay = 29;
    }
    if(day < 1 || day > maxDay)
    {
        return false;
    }

    days = daysFromCivil(year,month,day);
    return true;
}

// 公共接口
void User::borrow(Book& book , string initialdate , string returndate)
{
    if(getCurrent() >= getMax()) // 按照各自的权限
    {
        cout << "很抱歉，您已经到达最大的借阅数量！请先将已借阅的图书归还！" << endl;
        return;
    }

    int initial = 0;
    int expectedReturn = 0;
    if(!dateToDays(initialdate,initial) || !dateToDays(returndate,expectedReturn))
    {
        cout << "日期格式或日期值不正确，请使用 YYYY-MM-DD！" << endl;
        return;
    }
    if(expectedReturn < initial)
    {
        cout << "应还日期不能早于借阅日期！" << endl;
        return;
    }

    if(!book.isAvailable())
    {
        // 保留 GetOut 原有的失败提示，但不增加借阅数
        book.GetOut(getName() , getID() , initialdate , returndate);
        return;
    }

    book.GetOut(getName() , getID() , initialdate , returndate);
    current++;
}

// 利用daysfromcivil算法改进日期问题
int User::daysFromCivil(int y,int m,int d)
{
    y -= m <= 2; // bool类型 true和false隐形转化为 0和 1
    int era = (y >= 0 ? y : y - 399) / 400; // 400为一纪元 处理公元前负数年份情况
    unsigned yoe = y - era * 400; // 当前的year处于纪元的第几年 year of era
    unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; // 当前处于该年的第几天 day of year
    unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy; // 该纪元第几天 day of era
    return era * 146097 + (int)doe - 719468;
}
void User::returnbook(Book& book , string returndate)
{
    // 未借出或不属于当前用户时，不解析日期、不修改计数
    if(book.isAvailable()
        || book.getUsername() != getName()
        || book.getUserID() != getID())
    {
        book.GetIn(getName(),getID()); // 输出原有失败原因
        return;
    }

    int old = 0;
    int now = 0;
    if(!dateToDays(book.getReturndate(),old) || !dateToDays(returndate,now))
    {
        cout << "日期格式或日期值不正确，请使用 YYYY-MM-DD！" << endl;
        return;
    }

    int day = now - old;
    if(day <= 0)
    {
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

    // 所有成功的还书分支统一更新一次
    book.GetIn(getName(),getID());
    current--;
}
void User::getUserInformation() const
{
    cout << "该用户的名字：" << name << endl;
    cout << "该用户的院系：" << department << endl;
    cout << "该用户的ID：" << ID << endl;
    cout << "该用户的借阅数：" << current << "/" << max << endl;
}
std::ostream& operator<<(std::ostream& os, const User& user)
{
    os << "该用户的名字：" << user.getName() << std::endl;
    os << "该用户的院系：" << user.getDepartment() << std::endl;
    os << "该用户的ID：" << user.getID() << std::endl;
    os << "该用户的借阅数：" << user.getCurrent() << "/" << user.getMax() << std::endl;
    os << "该用户的类型：" << user.getUserType() << std::endl; // 多态差异
    return os;
}

// 实验六：User 自己负责自己的存取格式；类型标记经虚函数 getUserType() 区分，派生类无需重写
void User::saveTo(std::ostream& os) const
{
    os << (getUserType() == "学生" ? "S" : "T") << '|' << ID << '|'
       << name << '|' << department << '|' << current << '\n';
}
User* User::loadFrom(const string& line) // 工厂：按类型标记 new 对应派生类，以 User* 返回保证多态
{
    vector<string> f = splitLine(line);
    // 类型|ID|姓名|院系|当前已借数量
    if(f.size() != 5 || (f[0] != "S" && f[0] != "T"))
    {
        return nullptr;
    }
    long long id = 0;
    int current = 0;
    try
    {
        id = std::stoll(f[1]);
        current = std::stoi(f[4]);
    }
    catch(...)
    {
        return nullptr;
    }
    User* user = (f[0] == "S") ? static_cast<User*>(new Student(f[2], f[3], id))
                               : static_cast<User*>(new Teacher(f[2], f[3], id));
    if(current < 0)
    {
        current = 0;
    }
    if(current > user->getMax())
    {
        cout << "警告：用户 " << id << " 已借数量 " << current << " 超过上限，已按上限 " << user->getMax() << " 修正！" << '\n';
        current = user->getMax();
    }
    user->current = current; // 成员函数可访问 protected 成员
    return user;
}
