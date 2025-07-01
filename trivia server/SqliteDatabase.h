#pragma once
#include "IDatabase.h"
#include "User.h"
#include "Question.h"
#include "States.h"
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

	std::map<std::string, int> getHighScore() override;
	float getPllayerAverageAnswerTime(const std::string& username) override;
	int getNumOfCorrectAnswers(const std::string& username) override;
	int getNumOfTotalAnswers(const std::string& username) override;
	int getNumOfPlayerGames(const std::string& username) override;
	int getPlayerScore(const std::string& username) override;


private:
	sqlite3* _db;	// Data base info.
	std::list<User> _usersList;	// List of User (User).
	std::list<Question> _questionList;	// List of Question (Question).
	std::list<States> _statesList;	// List of States (States).
	std::string _password;
	std::map<std::string, int> _highScoreMap;


	bool sqlStatement(std::string sqlQuery);
	void UserSqlStatement(std::string sqlQuery);
	void HightScoreSqlStatement(std::string sqlQuery);
	void AverageAnswerTimeSqlStatement(std::string sqlQuery);
	void NumOfCurrectAnswersSqlStatement(std::string sqlQuery);
	void NumOfTotalAnswersSqlStatement(std::string sqlQuery);
	void NumOfPlayerGamesSqlStatement(std::string sqlQuery);
	void PlayerScoreSqlStatement(std::string sqlQuery);
	void questionSqlStatement(std::string sqlQuery);
	void statesSqlStatement(std::string sqlQuery);
	bool initDB();
	bool isTheTableCreated(std::string createSqlStatement, std::string tableName);
};