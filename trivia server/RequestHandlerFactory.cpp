#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory(LoginManager& loginManager, IDatabase* db, RoomManager& roomManager, StatisticsManager& StatisticsManager) : _loginManager(loginManager), _database(db), m_roomManager(roomManager), m_StatisticsManager(StatisticsManager)
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}


LoginManager& RequestHandlerFactory::getLoginManager()
{
	return _loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser logged_user)
{
	return new MenuRequestHandler();
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_StatisticsManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}
