#pragma once
#include "Constant.h"
#include "IRequestHandler.h"

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler() = default;
	~RoomAdminRequestHandler() = default;
	virtual bool isRequestRelevant(Structs::RequestInfo& ri) const override;
	virtual Structs::RequestResult handleRequest(Structs::RequestInfo& ri) const override;
};

