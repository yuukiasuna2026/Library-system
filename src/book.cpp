#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include"book.h"

namespace
{
	std::vector<std::string> splitLine(const std::string& line) // 按 '|' 切分字段
	{
		std::vector<std::string> fields;
		std::string field;
		std::istringstream ss(line);
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
Book::Book()
	: name(""), publisher(""), author(""), isbn(""), price(0.0), page(0),
	  available(true), Username(""), ID(0), initialdate(""), returndate("")
{}
Book::Book(std::string name, std::string publisher, std::string author, std::string isbn, double price, int page,bool available)
	: name(""), publisher(""), author(""), isbn(""), price(0.0), page(0),
	  available(true), Username(""), ID(0), initialdate(""), returndate("")
{
	if (!checkISBN(isbn))
	{
		std::cout << "Sorry,ISBN is wrong!" << std::endl;
		return;
	}

	this->name = std::move(name);
	this->publisher = std::move(publisher);
	this->author = std::move(author);
	this->isbn = std::move(isbn);
	this->price = price;
	this->page = page;
	this->available = available;
}

// 获取类函数
std::string Book::getName() const
{
	return name;
}
std::string Book::getUsername() const
{
	return Username;
}
long long Book::getUserID() const
{
	return ID;
}
std::string Book::getPublisher() const
{
	return publisher;
}
std::string Book::getAuthor() const
{
	return author;
}
std::string Book::getISBN() const
{
	return isbn;
}
double Book::getPrice() const
{
	return price;
}
int Book::getPage() const
{
	return page;
}
std::string Book::getReturndate() const
{
	return returndate;
}
std::string Book::getInitialdate() const
{
	return initialdate;
}
bool Book::isAvailable() const
{
	return available;
}

// 主要功能实现函数
bool Book::checkISBN(std::string isbn)
{
	int sum = 0;
	if (isbn.length() != 13)
	{
		return false;
	}
	else 
	{
		for (int i = 0;i < 12; i++)
		{
			if (isbn[i] < '0' || isbn[i] > '9')
			{
				return false;
			}
			else
			{
				if ((i + 1 ) % 2 == 0)
				{
					sum += (isbn[i] - '0') * 3;
				}
				else
				{
					sum += isbn[i] - '0';
				}
			}
		}
	}
	if (isbn[12] < '0' || isbn[12] > '9')
        return false;
	int check = (10 - sum % 10 ) % 10 ;
	return check == (isbn[12] -  '0' );
}
void Book::GetOut(std::string Username_ ,long long IDnum,std::string initialdate,std::string returndate)
{
	if(available)
	{
		Username = std::move(Username_);
		ID = IDnum;
		this->initialdate = std::move(initialdate);
		this->returndate = std::move(returndate);
		available = false;
	}
	else
	{
		std::cout << "这本书已经被借出了！" << std::endl;
		std::cout << "借阅者是" << Username << std::endl;
		std::cout << "ID是" << ID << std::endl;
		std::cout << "借阅日期是" << initialdate << std::endl;
		std::cout << "归还日期是" << returndate << std::endl;
	}

}
// 续借专用：仅延长应还日期，借阅人与借阅日期不变；仅 User::renew 经友元调用
void Book::extendDueDate(const std::string& newDue)
{
	returndate = newDue;
}
void Book::GetIn(std::string Username_, long long IDnum)
{
	if (!available)
	{
		if(Username_ == Username && ID == IDnum)
		{
			available = true;
			Username = "";
			ID = 0;
			initialdate = "";
			returndate = "";
		}
		else if(Username_ != Username && ID == IDnum)
		{
			std::cout << "你的ID是正确的，但名字不对!" << std::endl;
		}
		else if(Username_ == Username && ID != IDnum)
		{
			std::cout << "你的名字是对的，但ID不对!" << std::endl;
		}
		else
		{
			std::cout << "你的名字和ID都不对!" << std::endl;
		}
	}
	else
	{
		std::cout << "这本书还没有被借出！" << std::endl;
	}
}
void Book::PrintBookInformation() const
{
	std::cout << *this; // 复用 operator<<，保持原有功能
}
// 实验六：Book 自己负责自己的存取格式
void Book::saveTo(std::ostream& os) const
{
	os << isbn << '|' << name << '|' << author << '|' << publisher << '|'
	   << price << '|' << page << '|' << (available ? 1 : 0) << '|' << ID << '|'
	   << initialdate << '|' << returndate << '\n';
}
bool Book::loadFrom(const std::string& line, Book& out, long long& borrowerID,
					std::string& initDate, std::string& retDate)
{
	std::vector<std::string> f = splitLine(line);
	// ISBN|书名|作者|出版社|价格|页数|在馆|借阅人ID|借阅日期|应还日期
	if(f.size() != 10)
	{
		return false;
	}
	double price = 0.0;
	int page = 0;
	int avail = 0;
	borrowerID = 0;
	initDate = "";
	retDate = "";
	try
	{
		price = std::stod(f[4]);
		page = std::stoi(f[5]);
		avail = std::stoi(f[6]);
		if(avail == 0)
		{
			borrowerID = std::stoll(f[7]);
			initDate = f[8];
			retDate = f[9];
		}
	}
	catch(...)
	{
		return false;
	}
	if(!checkISBN(f[0]) || price < 0 || page < 0 || (avail != 0 && avail != 1))
	{
		return false;
	}
	out = Book(f[1], f[3], f[2], f[0], price, page, true); // 构造顺序：name,publisher,author,isbn,...
	return true;
}
bool Book::updateInfo(const std::string name, const std::string author,
					  const std::string publisher, double price, int page)
{
	if(price < 0 || page < 0)
	{
		std::cout << "修改失败：价格与页数不能为负数！" << std::endl;
		return false;
	}
	this->name = name;
	this->author = author;
	this->publisher = publisher;
	this->price = price;
	this->page = page;
	return true;
}
std::ostream& operator<<(std::ostream& os, const Book& book)
{
	os << "书名 :" << book.getName() << std::endl;
	os << "出版社 :" << book.getPublisher() << std::endl;
	os << "作者 :" << book.getAuthor() << std::endl;
	os << "ISBN :" << book.getISBN() << std::endl;
	os << "价格 :" << book.getPrice() << std::endl;
	os << "页数 :" << book.getPage() << std::endl;
	os << "是否可借 :" << (book.isAvailable() ? "Yes" : "No!") << std::endl;
	return os;
}
