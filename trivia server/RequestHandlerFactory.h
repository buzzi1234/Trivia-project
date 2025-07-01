#pragma once
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "LoginManager.h"
#include "IDatabase.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "Communicator.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class RoomManager;
class Communicator;

class RequestHandlerFactory
{
private:
	LoginManager& _loginManager;
	IDatabase* _database;
	RoomManager& m_roomManager;
	StatisticsManager& m_StatisticsManager;
	Communicator* m_communicator;

public:
	RequestHandlerFactory(LoginManager& loginManager, IDatabase* db, RoomManager& roomManager, StatisticsManager& StatisticsManager, Communicator* communicator);
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser logged_user);
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser user, Room& room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser user, Room& room);
};
