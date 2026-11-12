#pragma once
#include<string>
#include<ostream>

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
	std::string getInitialdate() const;
    void PrintBookInformation() const;
	static bool checkISBN(std::string ISBN);
	// 实验六：Book 自己负责自己的存取格式
	void saveTo(std::ostream& os) const;
	static bool loadFrom(const std::string& line, Book& out, long long& borrowerID,
						 std::string& initDate, std::string& retDate);
	// 修改基本信息
	bool updateInfo(const std::string name, const std::string author,
					const std::string publisher, double price, int page);

private:
	// 借还状态只能由用户借还流程修改
	friend class User;
	friend class Teacher;
	void GetOut(std::string Username_,long long UserID, std::string initialdate, std::string returndate);
	void GetIn(std::string Username_, long long UserID);
	void extendDueDate(const std::string& newDue); // 仅续借流程使用：原应还日期上延长
	friend class Library; // 持久化恢复时写借阅状态
};

// 非成员运算符重载：仅使用 Book 的 public 接口
std::ostream& operator<<(std::ostream& os, const Book& book);
