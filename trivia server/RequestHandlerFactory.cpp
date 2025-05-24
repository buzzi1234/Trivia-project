#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory(LoginManager& loginManager, IDatabase* db) : _loginManager(loginManager), _database(db) 
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
	return new MenuRequestHandler();
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return _loginManager;
}