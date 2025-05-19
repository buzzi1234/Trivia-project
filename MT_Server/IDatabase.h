#pragma once
#include "Question.h"
#include <list>
#include "Constant.h"

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
};