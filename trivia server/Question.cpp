#include "Question.h"

Question::Question(const std::string& questionText, const std::vector<std::string>& answers) :
	_question(questionText), _answers(answers) {
}

std::string Question::getQuestion() const
{
    return _question;
}

std::vector<std::string> Question::getAnswers() const
{
    return _answers;
}
