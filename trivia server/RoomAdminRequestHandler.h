#pragma once
#include "Constant.h"
#include "IRequestHandler.h"
#include "Structs.h"
#include "Room.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"

class RequestHandlerFactory;
class Communicator;

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(LoggedUser user, Room& room, RequestHandlerFactory& handlerFactory, Communicator& communicator);


	virtual bool isRequestRelevant(Structs::RequestInfo& ri) const override;
	virtual Structs::RequestResult handleRequest(Structs::RequestInfo& ri) const override;

private:
	LoggedUser m_user;
	Room& m_room;
	RequestHandlerFactory& m_handlerFactory;
	Communicator& m_communicator;
	
	Structs::RequestResult closeRoom() const;
	Structs::RequestResult startGame() const;
	Structs::RequestResult getRoomState() const;
};

