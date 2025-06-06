#include "MenuRequestHandler.h"

bool MenuRequestHandler::isRequestRelevant(Structs::RequestInfo& reqInfo) const
{
    if (reqInfo.id == LOGOUT || reqInfo.id == GET_PERSONAL_STATS ||
        reqInfo.id == GET_HIGH_SCORE || reqInfo.id == JOIN_ROOM ||
        reqInfo.id == GET_PLAYERS_IN_ROOM || reqInfo.id == CREATE_ROOM ||
        reqInfo.id == GET_ROOMS)
    {
        return true;
    }
    return false;
}

Structs::RequestResult MenuRequestHandler::handleRequest(Structs::RequestInfo& reqInfo) const
{
    if (isRequestRelevant(reqInfo))
    {
        switch (reqInfo.id)
        {
        case LOGOUT:
            return signout(reqInfo);
            break;
        case GET_PERSONAL_STATS:
            return getPersonalStats(reqInfo);
            break;
        case GET_HIGH_SCORE:
            return getHighScore(reqInfo);
            break;
        case JOIN_ROOM:
            return joinRoom(reqInfo);
            break;
        case GET_PLAYERS_IN_ROOM:
            return getPlayersInRoom(reqInfo);
            break;
        case CREATE_ROOM:
            return createRoom(reqInfo);
            break;
        case GET_ROOMS:
            return getRooms(reqInfo);

        }
        
    }
  
    return handleErrorRequest(reqInfo);

}

Structs::RequestResult MenuRequestHandler::signout(Structs::RequestInfo reqInfo)
{
    JsonResponsePacketSerializer s; // obj for serializer
    

    Structs::LogoutResponse res;
    res.status = reqInfo.id;

    Structs::RequestResult result;
    result.response = s.serializeResponse(res);

    if (res.status == LOGOUT)
    {
        result.newHandler = m_handlerFactory.createMenuRequestHandler();
    }
    else
    {
        result.newHandler = nullptr;
    }

    return result;
}

