#pragma once
#include <string>
#include <ostream>

// 管理员登录凭证类：管理员之间没有类型差异，不需要继承
class Admin
{
private:
    std::string account;   // 账号
    std::string password;  // 密码（课程项目明文存储）
public:
    Admin(std::string account, std::string password);
    bool check(const std::string& account, const std::string& password) const; // 账号密码校验
    const std::string& getAccount() const;
    void saveTo(std::ostream& os) const; // 序列化自己负责，格式：账号|密码
};
