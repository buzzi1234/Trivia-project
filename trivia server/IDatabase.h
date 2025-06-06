#pragma once
#include "Question.h"
#include <list>
#include "Constant.h"
#include <map>

#include <iostream>

class IDatabase
{
public:
	virtual bool open() = 0;
	virtual bool close() = 0;

	virtual int doesUserExist(std::string) = 0;
	virtual int doesPasswordMatch(std::string, std::string) = 0;
	virtual int addNewUser(std::string, std::string, std::string) = 0;

	virtual std::list<Question> getQuestions(int) = 0;

	virtual std::map<std::string, int> getHighScore() = 0;
	virtual float getPllayerAverageAnswerTime(const std::string& username) = 0;
	virtual int getNumOfCorrectAnswers(const std::string& username) = 0;
	virtual int getNumOfTotalAnswers(const std::string& username) = 0;
	virtual int getNumOfPlayerGames(const std::string& username) = 0;
	virtual int getPlayerScore(const std::string& username) = 0;

};