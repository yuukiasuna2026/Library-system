#include "Admin.h"
#include <utility>

Admin::Admin(std::string account, std::string password)
    : account(std::move(account)), password(std::move(password))
{
}

bool Admin::check(const std::string& account, const std::string& password) const
{
    return this->account == account && this->password == password;
}

const std::string& Admin::getAccount() const
{
    return account;
}

void Admin::saveTo(std::ostream& os) const
{
    os << account << '|' << password << '\n';
}
