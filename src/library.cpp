#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> // sort：一致性校验时无序比较书名列表
#include "library.h"
#include "Student.h"
#include "Teacher.h"

Library::Library()
{
    books.reserve(10000); // 预留容量，避免 findBook 返回的指针因扩容失效
    this -> libname = "";
    this -> address = "";
    this -> phone = "";
}
Library::Library(std::string libraryname , std::string libraryaddress , std::string libraryphone)
{

    books.reserve(10000);
    this -> libname = std::move(libraryname);
    this -> address = std::move(libraryaddress);
    this -> phone = std::move(libraryphone);
}
Library::~Library()
{
    for(auto* user : users)
    {
        delete user;
    }
}
void Library::addBook(const Book& book)
{
    if(!Book::checkISBN(book.getISBN()))
    {
        cout << "添加失败：图书 ISBN 不合法！" << '\n';
        return;
    }
    if(book.getPrice() < 0 || book.getPage() < 0)
    {
        cout << "添加失败：价格与页数不能为负数！" << '\n';
        return;
    }

    for(const auto& existingBook : books)
    {
        if(existingBook.getISBN() == book.getISBN())
        {
            cout << "添加失败：该 ISBN 已存在！" << '\n';
            return;
        }
    }
    books.push_back(book);
}
void Library::outBook(const Book& book)
{
    removeBook(book.getISBN()); // 委托按 ISBN 删除的实现
}
bool Library::removeBook(const std::string& isbn)
{
    for(auto it = books.begin(); it != books.end(); ++it)
    {
        if(it->getISBN() == isbn)
        {
            if(!it->isAvailable())
            {
                cout << "删除失败：该图书正在借出中！" << '\n';
                return false;
            }
            books.erase(it); 
            cout << "图书已删除！" << '\n';
            return true;
        }
    }
    cout << "未找到该图书，删除失败！" << '\n';
    return false;
}
std::string Library::findISBN(const std::string& name)
{
    const Book* found = nullptr;
    for(const auto& book : books)
    {
        if(book.getName() == name)
        {
            if(found != nullptr)
            {
                cout << "存在多本同名图书，无法仅凭书名确定图书！" << '\n';
                return "";
            }
            found = &book;
        }
    }

    if(found != nullptr)
    {
        return found->getISBN();
    }
    return "";
}
Book* Library::findBook(const std::string& ISBN)
{
    if(Book::checkISBN(ISBN))
    {
        for(auto& existingBook : books)
        {
            if(existingBook.getISBN() == ISBN)
            {
                return &existingBook;
            }
        }
    }
    else
    {
        std::cout << "The isbn maybe wrong!" << std::endl;
        return nullptr;
    }
    cout << "未找到该图书！" << '\n'; // ISBN 合法但库中不存在
    return nullptr;
}
void Library::printAll() const
{
    std::cout << "All the books are as follows :" << std::endl;
    int count = 1;
    for(const auto& book : books)
    {
        std::cout << "Number " << count << " is : " << book.getName() << std::endl;
        count ++;
    }
}

// 借还

void Library::borrowBook(string bookname , User& user , string initialdate , string returndate)
{
    string ISBN = findISBN(bookname);
    if(ISBN.empty())
    {
        cout << "图书不存在，借书操作已取消！" << '\n';
        return;
    }

    Book* book = findBook(ISBN);
    if(book == nullptr)
    {
        cout << "图书不存在！" << '\n';
        return;
    }
    user.borrow(*book , initialdate , returndate);
}
void Library::returnbook(string bookname , User& user , string returndate)
{
    string ISBN = findISBN(bookname);
    if(ISBN.empty())
    {
        cout << "图书不存在，还书操作已取消！" << '\n';
        return;
    }

    Book* book = findBook(ISBN);
    if(book == nullptr)
    {
        cout << "图书不存在！" << '\n';
        return;
    }
    user.returnbook(*book , returndate);
}
// 续借：书名精确匹配（同名不借歧义），转多态的 User::renew
bool Library::renewBook(const std::string& bookname, User& user)
{
    string ISBN = findISBN(bookname);
    if(ISBN.empty())
    {
        cout << "图书不存在，续借操作已取消！" << '\n';
        return false;
    }
    Book* book = findBook(ISBN);
    if(book == nullptr)
    {
        cout << "图书不存在！" << '\n';
        return false;
    }
    return user.renew(*book);
}
// 按书名/作者关键词查询：子串命中即列出，输出书名、作者、ISBN、在馆状态
void Library::searchBooks(const std::string& keyword) const
{
    if(keyword.empty())
    {
        cout << "查询关键词不能为空！" << '\n';
        return;
    }
    int count = 0;
    for(const auto& book : books)
    {
        if(book.getName().find(keyword) != string::npos
            || book.getAuthor().find(keyword) != string::npos)
        {
            count++;
            cout << count << ". " << book.getName()
                 << " | 作者：" << book.getAuthor()
                 << " | ISBN：" << book.getISBN()
                 << " | " << (book.isAvailable() ? "在馆可借" : "已借出") << '\n';
        }
    }
    if(count == 0)
    {
        cout << "未找到与 \"" << keyword << "\" 相关的图书！" << '\n';
    }
}

// 用户接口
void Library::addUser(User* user)
{
    if(user == nullptr)
    {
        cout << "添加失败：用户指针为空！" << '\n';
        return;
    }
    for(const auto* existingUser : users)
    {
        if(existingUser->getID() == user->getID())
        {
            cout << "添加失败：该用户 ID 已存在！" << '\n';
            return;
        }
    }
    users.push_back(user); // Library 接管所有权，析构时统一释放
}
User* Library::findUser(long long id)
{
    for(const auto x : users) // 按值拷贝指针，遍历只读
    {
        if(x->getID() == id)
            return x;
    }
    cout << "未找到该用户！" << '\n';
    cout << "请检查您输入的ID是否正确！" << '\n';
    return nullptr;
}
bool Library::removeUser(long long id)
{
    for(auto it = users.begin(); it != users.end(); ++it)
    {
        if((*it)->getID() == id)
        {
            if((*it)->getCurrent() > 0)
            {
                cout << "删除失败：该用户还有 " << (*it)->getCurrent() << " 本书未归还！" << '\n';
                return false;
            }
            delete *it; // Library 统一释放
            users.erase(it); // erase 后 it 失效，立即返回不再使用
            cout << "用户已删除！" << '\n';
            return true;
        }
    }
    cout << "未找到该用户，删除失败！" << '\n';
    return false;
}
bool Library::updateUser(long long id, const std::string& name, const std::string& department)
{
    for(auto* user : users)
    {
        if(user->getID() == id)
        {
            user->name = name; // friend 访问
            user->department = department;
            cout << "用户信息已修改！" << '\n';
            return true;
        }
    }
    cout << "未找到该用户，修改失败！" << '\n';
    return false;
}
bool Library::updateBook(const std::string& isbn, const std::string& name, const std::string& author,
                         const std::string& publisher, double price, int page)
{
    for(auto& book : books)
    {
        if(book.getISBN() == isbn)
        {
            if(book.updateInfo(name, author, publisher, price, page)) // 借出状态不受影响
            {
                cout << "图书信息已修改！" << '\n';
                return true;
            }
            return false; // updateInfo 已打印失败原因
        }
    }
    cout << "未找到该图书，修改失败！" << '\n';
    return false;
}
void Library::printUserinformation(User& user) const
{
    user.getUserInformation();

    cout << "已借阅的书籍：" << '\n';
    const vector<string>& titles = user.getBorrowedBooks(); // User 自己维护的借阅列表
    if(titles.empty())
    {
        cout << "暂无借阅记录" << '\n';
        return;
    }
    for(const auto& title : titles)
    {
        cout << "《" << title << "》" << '\n';
    }
}
// 查询用户借阅书籍及还书日期：以图书记录为准（Book 是日期与状态的唯一权威来源）
void Library::printBorrowList(const User& user) const
{
    bool found = false;
    string todayStr;
    bool hasToday = User::today(todayStr);
    int todayDays = 0;
    if(hasToday)
    {
        User::dateToDays(todayStr, todayDays); // static，可取
    }

    for(const auto& book : books)
    {
        if(book.isAvailable() || book.getUserID() != user.getID())
        {
            continue;
        }
        found = true;
        cout << "《" << book.getName() << "》" << '\n';
        cout << "    应还日期：" << book.getReturndate();
        if(hasToday)
        {
            int dueDays = 0;
            if(User::dateToDays(book.getReturndate(), dueDays))
            {
                cout << (dueDays < todayDays ? "（已逾期！）" : "（未到期）");
            }
        }
        cout << '\n';
    }
    if(!found)
    {
        cout << "该用户当前没有借阅中的图书！" << '\n';
    }
}
void Library::clear()
{
    for(auto* user : users)
    {
        delete user; // 与 ~Library 一致的释放责任
    }
    users.clear();
    books.clear();
    cout << "图书馆已清空：全部用户与图书记录已移除！" << '\n';
}

// ===== 实验六：文件持久化 =====
namespace
{
    std::string stripCR(std::string s) // 去掉 Windows 换行残留的 '\r'
    {
        if(!s.empty() && s.back() == '\r')
        {
            s.pop_back();
        }
        return s;
    }
}

// 启动加载：先恢复用户（图书借阅状态需按借阅人 ID 校验），再恢复图书，最后做一致性修正
bool Library::loadData(const std::string& path)
{
    int userBadLines = 0;
    int bookBadLines = 0;

    std::ifstream userFile(path + "/users.txt");
    if(!userFile.is_open())
    {
        cout << "未找到 users.txt，从空用户列表开始！" << '\n';
    }
    else
    {
        std::string line;
        while(std::getline(userFile, line))
        {
            line = stripCR(line);
            if(line.empty())
            {
                continue;
            }
            User* user = User::loadFrom(line); 
            if(user == nullptr)
            {
                userBadLines++;
                continue;
            }
            bool dup = false;
            for(const auto* existing : users)
            {
                if(existing->getID() == user->getID())
                {
                    dup = true;
                    break;
                }
            }
            if(dup)
            {
                delete user; // 拒绝重复 ID，同时避免泄漏
                userBadLines++;
                continue;
            }
            users.push_back(user);
        }
        userFile.close();
    }

    std::ifstream bookFile(path + "/books.txt");
    if(!bookFile.is_open())
    {
        cout << "未找到 books.txt，从空图书列表开始！" << '\n';
    }
    else
    {
        std::string line;
        while(std::getline(bookFile, line))
        {
            line = stripCR(line);
            if(line.empty())
            {
                continue;
            }
            Book book;
            long long borrowerID = 0;
            std::string initDate;
            std::string retDate;
            if(!Book::loadFrom(line, book, borrowerID, initDate, retDate)) // 格式解析
            {
                bookBadLines++;
                continue;
            }
            bool dupBook = false;
            for(const auto& existing : books)
            {
                if(existing.getISBN() == book.getISBN())
                {
                    dupBook = true;
                    break;
                }
            }
            if(dupBook)
            {
                bookBadLines++;
                continue;
            }
            if(borrowerID == 0) // 在馆图书（loadFrom 对未借出的书返回借阅人 ID 0）直接入库
            {
                books.push_back(book);
                continue;
            }
            const User* borrower = nullptr;
            for(const auto* u : users)
            {
                if(u->getID() == borrowerID)
                {
                    borrower = u;
                    break;
                }
            }
            if(borrower == nullptr) // 无法对应的坏数据：跳过并警告
            {
                cout << "警告：图书 " << book.getISBN() << " 标记为借出，但借阅人 ID " << borrowerID << " 不存在，已跳过该书！" << '\n';
                bookBadLines++;
                continue;
            }
            book.GetOut(borrower->getName(), borrowerID, initDate, retDate); // friend 访问，恢复借出状态
            books.push_back(book);
        }
        bookFile.close();
    }

    // 一致性校验：以图书记录（book.text）为单一事实源，修正用户已借数量与借阅书名列表 
    for(auto* user : users)
    {
        vector<string> actualTitles;
        for(const auto& book : books)
        {
            if(!book.isAvailable() && book.getUserID() == user->getID())
            {
                actualTitles.push_back(book.getName());
            }
        }
        // 文件中的书名列表与图书不一致（顺序无关比较）时警告并按图书修正
        vector<string> fileTitles = user->borrowedBooks;
        sort(fileTitles.begin(), fileTitles.end());
        vector<string> sortedActual = actualTitles;
        sort(sortedActual.begin(), sortedActual.end());
        if(fileTitles != sortedActual)
        {
            cout << "警告：用户 " << user->getID() << " 的借阅书名列表与图书记录不符，已按图书修正！" << '\n';
            user->borrowedBooks = actualTitles; 
        }
        int actual = (int)actualTitles.size();
        if(user->current != actual)
        {
            cout << "警告：用户 " << user->getID() << " 记录的已借数量 " << user->current << " 与实际 " << actual << " 不符，已按实际修正！" << '\n';
            user->current = actual; 
        }
    }

    cout << "数据加载完成：用户 " << users.size() << " 个";
    if(userBadLines > 0)
    {
        cout << "（跳过坏行 " << userBadLines << "）";
    }
    cout << "，图书 " << books.size() << " 本";
    if(bookBadLines > 0)
    {
        cout << "（跳过坏行 " << bookBadLines << "）";
    }
    cout << '\n';
    return true;
}

// 退出保存：覆盖写回当前全部图书与用户数据
bool Library::saveData(const std::string& path)
{
    std::ofstream bookFile(path + "/books.txt");
    if(!bookFile.is_open())
    {
        cout << "保存失败：无法写入 books.txt！" << '\n';
        return false;
    }
    for(const auto& book : books)
    {
        book.saveTo(bookFile); // 由 Book 自己负责
    }
    bookFile.close();

    std::ofstream userFile(path + "/users.txt");
    if(!userFile.is_open())
    {
        cout << "保存失败：无法写入 users.txt！" << '\n';
        return false;
    }
    for(const auto* user : users)
    {
        user->saveTo(userFile); //  User 自己负责
    }
    userFile.close();

    cout << "数据已保存：图书 " << books.size() << " 本，用户 " << users.size() << " 个！" << '\n';
    return true;
}