#pragma once
#include "IRequestHandler.h"
#include "Structs.h"


class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler() = default;

	virtual bool isRequestRelevant(Structs::RequestInfo& reqInfo) const override;
	virtual Structs::RequestResult handleRequest(Structs::RequestInfo& reqInfo) const override;

};

