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
		for (int i = 0;i < 13; i++)
		{
			if (isbn[i] < '0' || isbn[i] > '9')
			{
				return false;
			}
			else
			{
				if ((isbn[i] - '0') % 2 == 0)
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
	int check = (10 - sum % 10) % 10;
	if (!check)
	{
		return false;
	}
	else
	{
		return true;
	}
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
