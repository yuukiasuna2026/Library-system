#include<iostream>
#include"book.h"

// 构造函数
Book::Book()
{
	name = "";
	publisher = "";
	author = "";
	isbn = "";
	price = 0.00;
	page = 0;
	available = true;
}
Book::Book(std::string name, std::string publisher, std::string author, std::string isbn, double price, int page,bool available)
{
	
	bool check = checkISBN(isbn);
	if (check)
	{
		this->name =std::move(name);
		this->publisher = std::move(publisher);
		this->author = std::move(author);
		this->isbn = std::move(isbn);
		this->price = price;
		this->page = page;
		this->available = available;
	}
	else
	{
		std::cout << "Sorry,ISBN is wrong!" << std::endl;
	}
}

// 设置类函数
void Book::setName(const std::string name)
{
	this->name = name;
}
void Book::setUsername(const std::string Username)
{
	this->name = std::move(Username);
}
void Book::setUserID(const long long IDnum)
{
	this->ID = IDnum;
}
void Book::setPublisher(const std::string publisher)
{
	this->publisher = publisher;
}
void Book::setAuthor(const std::string author)
{
	this ->author = std::move(author);
}
void Book::setISBN(const std::string ISBN )
{
	bool check = checkISBN(ISBN);
	if(check)
	{
		this -> isbn  = ISBN;
	}
	else
	{
		std::cout << "Sorry,ISBN is wrong!" << std::endl;
	}

}
void Book::setPrice(const double Price)
{
	this -> price = Price;
}
void Book::setPage(const int Page)
{
	this -> page = Page ;
}

// 获取类函数
std::string Book::getName() const
{
	return name;
}
std::string Book::getUsername() const
{
	return name;
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
		std::cout << "This book has been borrowed!" << std::endl;
		std::cout << "The borrower is" << Username << std::endl;
		std::cout << "The ID is" << ID << std::endl;
		std::cout << "The initial date is" << initialdate << std::endl;
		std::cout << "The return date is" << returndate << std::endl;
	}

}
void Book::GetIn(std::string Username_, long long IDnum)
{
	if (!available)
	{
		if(Username_ == Username && ID == IDnum)
		{
			available = true;
			name = "";
			ID = 0;
			initialdate = "";
			returndate = "";
		}
		else if(Username_ != Username && ID == IDnum)
		{
			std::cout << "The student number is correct,but the name is wrong!" << std::endl;
		}
		else if(Username_ == Username && ID != IDnum)
		{
			std::cout << "The name is correct,but the student number is wrong!" << std::endl;
		}
		else
		{
			std::cout << "The name and student number are both wrong!" << std::endl;
		}
	}
	else
	{
		std::cout << "This book has not been borrowed!" << std::endl;
	}
}
void Book::PrintBookInformation() const
{
	std::cout << "Book name is :" << name << std::endl;
	std::cout << "Book publisher is :" << publisher << std::endl;
	std::cout << "Book author is :" << author << std::endl;
	std::cout << "Book ISBN is :" << isbn <<std::endl;
	std::cout << "Book price is :" << price << std::endl;
	std::cout << "Book page is :" << page << std::endl;
	std::cout << "Book available is :" << (available ? "Yes" : "No!It has benn borrowed") << std::endl;
}
