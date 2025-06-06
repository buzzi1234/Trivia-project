#pragma once
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "LoginManager.h"
#include "IDatabase.h"
#include "RoomManager.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
private:
	LoginManager& _loginManager;
	IDatabase* _database;
	RoomManager m_roomManager;
public:
	RequestHandlerFactory(LoginManager& loginManager, IDatabase* db);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
	LoginManager& getLoginManager();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser logged_user);
	RoomManager& getRoomManager();
};
