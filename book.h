#pragma once
#include<string>

class Book
{
private:
	std::string name;
	std::string publisher;
	std::string author;
	std::string isbn;
	double price;
	int page;
	bool available;
	int StuNumber;
	std::string initialdate;
	std::string returndate;
	std::string borrower;
public:
	Book();
	Book(std::string name, std::string publisher, std::string author,std::string isbn, double price, int page, bool available);
	void setName(const std::string name);
	void setPublisher(const std::string publisher);
	void setAuthor(const std::string author);
	void setISBN(const std::string ISBN);
	void setPrice(const double price);
	void setPage(const int page);
	bool isAvailable();
	std::string getName() const;
	std::string getPublisher() const;
	std::string getAuthor() const;
	std::string getISBN() const;
	double getPrice() const;
	int getPage() const;
	void GetOut(std::string name,int StuNumber, std::string initialdate, std::string returndate);
	void GetIn(std::string name, int StuNumber);
private:
	bool checkISBN(std::string ISBN);
};
