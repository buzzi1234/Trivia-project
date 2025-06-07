#include "RoomAdminRequestHandler.h"

bool RoomAdminRequestHandler::isRequestRelevant(Structs::RequestInfo& ri) const
{
    return false;
}

Structs::RequestResult RoomAdminRequestHandler::handleRequest(Structs::RequestInfo& ri) const
{
    return Structs::RequestResult();
}
