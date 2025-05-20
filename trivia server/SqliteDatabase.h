#pragma once
#include "IDatabase.h"
#include "User.h"
#include "sqlite3.h"

#include <iostream>
#include <Windows.h>
#include <io.h>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <list>


class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase() = default;
	~SqliteDatabase();

	bool open() override;
	bool close() override;
	int doesUserExist(std::string userName) override;
	int doesPasswordMatch(std::string userName, std::string password) override;
	int addNewUser(std::string userName, std::string password, std::string email) override;
	std::list<Question> getQuestions(int) override;

private:
	sqlite3* _db;	// Data base info.
	std::list<User> _usersList;	// List of User (User).
	std::list<Question> _questionList;	// List of Question (Question).
	std::string _password;

	bool sqlStatement(std::string sqlQuery);
	void UserSqlStatement(std::string sqlQuery);
	void questionSqlStatement(std::string sqlQuery);
	bool initDB();
	bool isTheTableCreated(std::string createSqlStatement, std::string tableName);
};