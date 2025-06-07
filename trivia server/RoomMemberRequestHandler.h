#pragma once
#include "Constant.h"
#include "IRequestHandler.h"
class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler() = default;
	~RoomMemberRequestHandler() = default;
	virtual bool isRequestRelevant(Structs::RequestInfo& ri) const override;
	virtual Structs::RequestResult handleRequest(Structs::RequestInfo& ri) const override;
};

