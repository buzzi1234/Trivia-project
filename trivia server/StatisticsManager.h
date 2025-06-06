#pragma once
#include <string>
#include <vector>
#include "IDatabase.h"


class StatisticsManager
{
public:
	StatisticsManager(IDatabase* database);
	~StatisticsManager() = default;

	std::map<std::string, int> getHighScore();
	std::vector<std::string> getUserStatistics(const std::string& username);

private:
	IDatabase* m_database;
};

