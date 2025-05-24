#pragma once
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "LoginManager.h"
#include "IDatabase.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
private:
	LoginManager& _loginManager;
	IDatabase* _database;
public:
	RequestHandlerFactory(LoginManager& loginManager, IDatabase* db);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
	LoginManager& getLoginManager();
};