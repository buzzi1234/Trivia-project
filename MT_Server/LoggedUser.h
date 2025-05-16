#pragma once
#include <string>

class LoggedUser
{
public:
	LoggedUser(std::string userName);
	~LoggedUser() = default;
	std::string getUserName() const;
private:
	std::string m_username;
};

