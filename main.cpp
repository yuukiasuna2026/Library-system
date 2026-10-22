#include <iostream>
#include <string>
#include <windows.h>
#include "book.h"
#include "library.h"
#include "Student.h"
#include "Teacher.h"
using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);  // 输出 UTF-8
    SetConsoleCP(CP_UTF8);        // 输入也 UTF-8（需要 cin 中文时）
    // 实验1测试

    // Book b1;
    // Book b2("Object Oriented Programming","People of China publisher", "YuukiAsuna", "9780123456789", 325799.99 , 114514, true);
    // std::cout << "The information of b2 is as followd: " << std::endl;
    // b2.PrintBookInformation();
    // std::cout << "The information of b1 must be setted! And the information of b1 is as followd:" << std::endl;
    // b1.setName("C++ from beginner to death");
    // b1.setPublisher("People of America publisher");
    // b1.setAuthor("Trump");
    // b1.setISBN("9789876543210");
    // b1.setPrice(114514.99);
    // b1.setPage(799);
    // std::cout << "The information of b1 is as followed:" << std::endl;
    // b1.PrintBookInformation();
    // std::cout << "Is the book b1 and b2 available?" << std::endl;
    // std::cout << "The book b1 is " << (b1.isAvailable() ? "available" : "not available") << std::endl;
    // std::cout << "The book b2 is " << (b2.isAvailable() ? "available" : "not available") << std::endl;
    // std::cout << "Now,let's check the function of get the single book information!" << std::endl;
    // std::cout << "The name of b1 is :" << b1.getName() << std::endl;
    // std::cout << "The publisher of b1 is :" << b1.getPublisher() << std::endl;
    // std::cout << "The author of b1 is :" << b1.getAuthor() << std::endl;
    // std::cout << "The ISBN of b1 is :" << b1.getISBN() << std::endl;
    // std::cout << "The price of b1 is :" << b1.getPrice() << std::endl;
    // std::cout << "The page of b1 is :" << b1.getPage() << std::endl;
    // std::cout << "Then,let's check the function of borrowing and returning books!" << std::endl;
    // std::cout << "Now,Trump is borrowing the book b2!" << std::endl;
    // b2.GetOut("Trump",5120267878,"2026.09.19","2026.09.26");
    // std::cout << "The book b2 is :" << (b2.isAvailable() ? "available" : "not available") << std::endl;
    // std::cout << "Mask tries to borrow the book b2!" << std::endl;
    // b2.GetOut("Mask",520269191,"2026.09.20","2026.09.27");
    // std::cout <<"Trump is returning the book b2" << std::endl;
    // b2.GetIn("Trump",5120267878);
    // std::cout << "The book b2 is :" << (b2.isAvailable() ? "available" : "not available") << std::endl;

    // // 实验2测试

    // Library lib1;
    // Library lib2("schoollibrary","SWUST","123-456");
    // Book b1("C++ from learn to death","Publisher of China","Niko","9780306406157",99.99,325,true);
    // Book b2("My lover","Publisher of American","Trump","9783161484100",88.88,799,true);
    // lib2.addBook(b1);
    // lib2.printAll();
    // lib2.addBook(b2);
    // lib2.printAll();
    // lib2.findBook("978987654321");
    // lib2.findISBN("C++ from learn to death");
    // Student s1;
    // Student s2("Mask","history",5120258989);
    // Student s3("Trump","computer",5120256767);
    // s2.borrow(b1,"2026.09.19","2026.09.26");
    // s3.borrow(b2,"2026.09.20","2026.09.27");
    // s2.returnbook(b1,"2026.09.26");
    // s3.returnbook(b2,"2026.09.30");
    
    // 实验三四
    Book b("C++ Primer", "China", "Stanley", "9787121155352", 100.0, 800, true);

    // 用基类指针指向子类对象，=（向上赋值）将子类对象地址赋值给父类指针，调用是体现多态（调用子类实现的函数）
    // 此处new可以用 ：
    // auto u1 = make_unique<Studnet>(………………); 智能指针避免手动delete
    // unique_ptr<User> u1(new Student(…………)); c++ 11 写法 (注意只能用括号初始化，不能=赋值)
    User* u1 = new Student("张三","计算机科学与技术",5120256666);
    User* u2 = new Teacher("李四","软件工程",5120258888);

    cout << u1 -> getUserType() << "逾期比例为：" << u1 -> getDivisor() << endl;
    cout << u2 -> getUserType() << "逾期比例为：" << u2 -> getDivisor() << endl;

    // 测试还借功能
    u1 -> borrow(b,"2026-10-01","2026-10-10");
    u1 -> returnbook(b,"2026-10-15"); // 测试逾期五天

    // 虚析构保持正确的释放
    delete u1; // vptr(虚表指针) -> Student类的虚析构表 -> student的析构 -> ~User() -> 调用operator delete 将子类对象落内存归还操作系统
    delete u2;
    
    return 0;
}