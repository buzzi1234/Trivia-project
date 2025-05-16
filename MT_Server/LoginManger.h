#pragma once
#include "SqliteDataBase.h"
#include "LoggedUser.h"
#include <vector>
#include "Constant.h"

class LoginManger
{
public:
	LoginManger(SqliteDatabase* sqlDS);
	~LoginManger();
	int signup(std::string username, std::string password, std::string email);
	int login(std::string username, std::string password);
	void logout(std::string username);

private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};

