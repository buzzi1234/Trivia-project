#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* database) : m_database(database)
{
}
std::map<std::string, int> StatisticsManager::getHighScore()
{
	return m_database->getHighScore();
}

std::vector<std::string> StatisticsManager::getUserStatistics(const std::string& username)
{
	std::vector<std::string> stats;
	stats.push_back(std::to_string(m_database->getPllayerAverageAnswerTime(username)));
	stats.push_back(std::to_string(m_database->getNumOfCorrectAnswers(username)));
	stats.push_back(std::to_string(m_database->getNumOfTotalAnswers(username)));
	stats.push_back(std::to_string(m_database->getNumOfPlayerGames(username)));
	stats.push_back(std::to_string(m_database->getPlayerScore(username)));
	return stats;
}