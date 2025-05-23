#pragma once
#include "IDatabase.h"
#include "LoggedUser.h"
#include <vector>
#include <string>
#include "Constant.h"

#define LOG_CODE 1
#define SIGN_CODE 2
#define ERROR_CODE 3

class LoginManager
{
public:
	LoginManager(IDatabase* sqlDS);
	~LoginManager();
	int signup(std::string username, std::string password, std::string email);
	int login(std::string username, std::string password);
	void logout(std::string username);

private:
	IDatabase* m_database;
	std::vector<LoggedUser*> m_loggedUsers;
};

