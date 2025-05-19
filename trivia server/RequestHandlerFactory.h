#pragma once

#include "LoginManager.h"
#include "IDatabase.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
private:
	LoginManager& _loginManager;
	IDatabase* _database;

public:
	RequestHandlerFactory(LoginManager& loginManager, IDatabase* database);

	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
};

