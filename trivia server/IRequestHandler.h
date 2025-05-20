#pragma once
#include <vector>
#include <ctime>
#include "JsonRequestPacketDeserializer.h"


class IRequestHandler
{
public:
	virtual ~IRequestHandler() = default;
	virtual bool isRequestRelevant(Structs::RequestInfo& ri) const = 0;
	virtual Structs::RequestResult handleRequest(Structs::RequestInfo& ri) const = 0;
};

