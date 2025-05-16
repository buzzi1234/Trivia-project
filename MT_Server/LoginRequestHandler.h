#pragma once
#include "IRequestHandler.h"
#include "JsonResponsePacketSerializer.h"


class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler() = default;
	~LoginRequestHandler() = default;
	virtual bool isRequestRelevant(Structs::RequestInfo& ri) const override;
	virtual Structs::RequestResult handleRequest(Structs::RequestInfo& ri) const override;
private:
	Structs::RequestResult handleLoginRequest(Structs::RequestInfo& ri) const;
	Structs::RequestResult handleSignupRequest(Structs::RequestInfo& ri) const;
	Structs::RequestResult handleErrorRequest(Structs::RequestInfo& ri) const;
};

