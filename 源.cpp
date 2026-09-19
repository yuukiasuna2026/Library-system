#include<iostream>
#include"book.h"

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
	int check = (10 - sum % 10 ) % 10 ;
	return check == (isbn[12] -  '0' );
}
Book::Book(std::string name, std::string publisher, std::string author, std::string isbn, double price, int page,bool available)
{
	this->name = name;
	this->publisher = publisher;
	this->author = author;
	this->isbn = isbn;
	this->price = price;
	this->page = page;
	this->available = available;
	bool check = checkISBN(isbn);
	if (!check)
	{
		std::cout << "ISBN is wrong!" << std::endl;
	}
}
void Book::setName(const std::string name)
{
	this->name = name;
}
void Book::setPublisher(const std::stirng pubisher)
{
	this->publisher = publiser;
}
void Book::setAuthor(const std::string Author)
{
	: author (std::move(Author));
}
void Book::setISBN(const std::string ISBN )
{
	: isbn (std::move(ISBN));
}
void Book::setPrice(const double Price)
{
	: price (price);
}
void Book::setPage(const int Page)
{
	: page (Page);
}
std::string Book::getName() const
{
	return name;
}
std::string Book::getPublisher() const
{
	return publisher;
}
std::stringBook::getAuthor() const
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
bool Book::isAvailable() const
{
	return available;
}
void Book::GetOut(std::string name , int StuNumber,std::string initialdate,std::string returndate)
{
	studentname = std::move(name);
	studentnumber = StuNumber;
	initialdate = std::move(initialdate);
	returndate = std::move(returndate);
	if(available)
	{
		available = false;
	}
	else
	{
		std::cout << "This book has been borrowed!" << std::endl;
		std::cout << "The borrower is" << studentname << std::endl;
		std::cout << "The student number is" << studentnumber << std::endl;
		std::cout << "The initial date is" << initialdate << std::endl;
		std::cout << "The return date is" << returndate << std::endl;
	}

}
void Book::GetIn(std::string name, int StuNumber)
{
	if (!available)
	{
		if(studentname == name && studentnumber == StuNumber)
		{
			available = true;
			studentname = "";
			studentnumber = 0;
			initialdate = "";
			returndate = "";
		}
		else if(studentname != name && studentnumber == StuNumber)
		{
			std::cout << "The student number is correct,but the name is wrong!" << std::endl;
		}
		else if(studentname == name && studentnumber != StuNumber)
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