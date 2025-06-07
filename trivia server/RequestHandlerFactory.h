#pragma once
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "LoginManager.h"
#include "IDatabase.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
private:
	LoginManager& _loginManager;
	IDatabase* _database;
	RoomManager& m_roomManager;
	StatisticsManager& m_StatisticsManager;

public:
	RequestHandlerFactory(LoginManager& loginManager, IDatabase* db, RoomManager& roomManager, StatisticsManager& StatisticsManager);
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser logged_user);
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();
};
