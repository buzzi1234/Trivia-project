#include "RoomMemberRequestHandler.h"

bool RoomMemberRequestHandler::isRequestRelevant(Structs::RequestInfo& ri) const
{
    return false;
}

Structs::RequestResult RoomMemberRequestHandler::handleRequest(Structs::RequestInfo& ri) const
{
    return Structs::RequestResult();
}
