#include <iostream>
#include <string>
#include "book.h"
#include "library.h"
#include "Student.h"
using namespace std;

int main()
{
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

    // 实验2测试

    Library lib1;
    Library lib2("schoollibrary","SWUST","123-456");
    Book b1("C++ from learn to death","Publisher of China","Niko","9780123456789",99.99,325,true);
    Book b2("My lover","Publisher of American","Trump","9780987654321",88.88,799,true);
    lib2.addBook(b1);
    lib2.printAll();
    lib2.addBook(b2);
    lib2.printAll();
    lib2.findBook("978987654321");
    lib2.findISBN("C++ from learn to death");
    Student s1();
    Student s2("Mask","history",5120258989);
    Student s3("Trump","computer",5120256767);
    
    return 0;
}