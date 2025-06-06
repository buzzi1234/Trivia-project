#pragma once
#include "IRequestHandler.h"
#include "Constant.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"


class MenuRequestHandler : public IRequestHandler
{
private:
	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;

public:
	MenuRequestHandler() = default;

	virtual bool isRequestRelevant(Structs::RequestInfo& reqInfo) const override;
	virtual Structs::RequestResult handleRequest(Structs::RequestInfo& reqInfo) const override;
	Structs::RequestResult signout(Structs::RequestInfo reqInfo);
	Structs::RequestResult getRooms(Structs::RequestInfo reqInfo);
	Structs::RequestResult getPlayersInRoom(Structs::RequestInfo reqInfo);
	Structs::RequestResult getPersonalStats(Structs::RequestInfo reqInfo);
	Structs::RequestResult getHighScore(Structs::RequestInfo reqInfo);
	Structs::RequestResult joinRoom(Structs::RequestInfo reqInfo);
	Structs::RequestResult createRoom(Structs::RequestInfo reqInfo);
	Structs::RequestResult handleErrorRequest(Structs::RequestInfo reqInfo);



};
