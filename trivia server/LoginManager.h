#pragma once
#include "IDatabase.h"
#include "LoggedUser.h"
#include <vector>
#include <string>
#include "Constant.h"

class LoginManager
{
public:
	LoginManager(IDatabase* sqlDS);
	~LoginManager();
	int signup(std::string username, std::string password, std::string email);
	int login(std::string username, std::string password);
	void logout(std::string username);
	void printUsers() const;

private:
	IDatabase* m_database;
	std::vector<LoggedUser*> m_loggedUsers;
};

