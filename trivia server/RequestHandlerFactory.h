#pragma once

#include "LoginManager.h"
#include "IDatabase.h"
#include "MenuRequestHandler.h"
#include "LoginRequestHandler.h"

class RequestHandlerFactory
{
private:
	LoginManager& _loginManager;
	IDatabase* _database;

public:

	RequestHandlerFactory(LoginManager& loginManager, IDatabase* database);
	MenuRequestHandler* createMenuRequestHandler();
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
};

