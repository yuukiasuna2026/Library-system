#pragma once
#include<string>

class Book
{
private:
	std::string name;
	std::string Username;
	std::string publisher;
	std::string author;
	std::string isbn;
	double price;
	int page;
	bool available;
	long long ID;
	std::string initialdate;
	std::string returndate;

public:
	Book();
	Book(std::string name, std::string publisher, std::string author,std::string isbn, double price, int page, bool available);
	void setName(const std::string name);
	void setUsername(const std::string username);
	void setUserID(const long long UserID);
	void setPublisher(const std::string publisher);
	void setAuthor(const std::string author);
	void setISBN(const std::string ISBN);
	void setPrice(const double price);
	void setPage(const int page);
	bool isAvailable() const;
	std::string getName() const;
	std::string getUsername () const;
	long long  getUserID() const; 
	std::string getPublisher() const;
	std::string getAuthor() const;
	std::string getISBN() const;
	double getPrice() const;
	int getPage() const;
	std::string getReturndate() const;
	void GetOut(std::string Username_,long long UserID, std::string initialdate, std::string returndate);
	void GetIn(std::string name, long long UserID);
    void PrintBookInformation() const;
	static bool checkISBN(std::string ISBN);
	
};
