#pragma once
#include "Constant.h"
#include "IRequestHandler.h"
#include "Room.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(LoggedUser user, Room room, RequestHandlerFactory& factory);

	virtual bool isRequestRelevant(Structs::RequestInfo& ri) const override;
	virtual Structs::RequestResult handleRequest(Structs::RequestInfo& ri) const override;

private:
	LoggedUser m_user;
	Room m_room;
	RequestHandlerFactory& m_handlerFactory;
	
	Structs::RequestResult leaveRoom() const;
	Structs::RequestResult getRoomState() const;
};

