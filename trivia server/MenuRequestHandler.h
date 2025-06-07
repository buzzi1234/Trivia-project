#pragma once
#include "IRequestHandler.h"
#include "Constant.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
private:
	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;

public:
	MenuRequestHandler(LoggedUser loged, RequestHandlerFactory& factory);
	~MenuRequestHandler() = default;

	virtual bool isRequestRelevant(Structs::RequestInfo& reqInfo) const override;
	virtual Structs::RequestResult handleRequest(Structs::RequestInfo& reqInfo) const override;
	Structs::RequestResult signout(Structs::RequestInfo& reqInfo) const;
	Structs::RequestResult getRooms(Structs::RequestInfo& reqInfo) const;
	Structs::RequestResult getPlayersInRoom(Structs::RequestInfo& reqInfo) const;
	Structs::RequestResult getPersonalStats(Structs::RequestInfo& reqInfo) const;
	Structs::RequestResult getHighScore(Structs::RequestInfo& reqInfo) const;
	Structs::RequestResult joinRoom(Structs::RequestInfo& reqInfo) const;
	Structs::RequestResult createRoom(Structs::RequestInfo& reqInfo) const;
	Structs::RequestResult handleErrorRequest(Structs::RequestInfo& reqInfo) const;



};
