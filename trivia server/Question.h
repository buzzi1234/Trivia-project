#pragma once

#include <iostream>
#include <string>
#include <vector>

class Question
{
public:
	Question(const std::string& questionText, const std::vector<std::string>& answers);
	~Question() = default;

	std::string getQuestion() const;
	std::vector<std::string> getAnswers() const;

private:
	std::string _question;
	std::vector<std::string> _answers;
};