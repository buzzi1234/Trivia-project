#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory(LoginManager& loginManager, IDatabase* db, RoomManager& roomManager, StatisticsManager& StatisticsManager, Communicator* communicator) : _loginManager(loginManager), _database(db), m_roomManager(roomManager), m_StatisticsManager(StatisticsManager), m_communicator(communicator)
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
	return new MenuRequestHandler(logged_user, *this, *m_communicator);
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_StatisticsManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser user, Room& room)
{
	return new RoomAdminRequestHandler(user, room, *this, *m_communicator);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, Room& room)
{
	return new RoomMemberRequestHandler(user, room, *this);
}
