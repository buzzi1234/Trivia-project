#pragma once
#include "IRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"


class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory);
	~LoginRequestHandler() = default;
	virtual bool isRequestRelevant(Structs::RequestInfo& ri) const override;
	virtual Structs::RequestResult handleRequest(Structs::RequestInfo& ri) const override;
private:
	RequestHandlerFactory& _handlerFactory;

	Structs::RequestResult handleLoginRequest(Structs::RequestInfo& ri) const;
	Structs::RequestResult handleSignupRequest(Structs::RequestInfo& ri) const;
	Structs::RequestResult handleErrorRequest(Structs::RequestInfo& ri) const;
};

