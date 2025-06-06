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

Structs::RequestResult MenuRequestHandler::signout(Structs::RequestInfo& reqInfo) const
{
    Structs::RequestResult rr;
    Structs::LogoutResponse lr;
    JsonResponsePacketSerializer j;

    m_handlerFactory.getLoginManager().logout(m_user.getUserName());

    lr.status = reqInfo.id;

    rr.response = j.serializeResponse(lr);
    rr.newHandler = this;

    return rr;
}

Structs::RequestResult MenuRequestHandler::getRooms(Structs::RequestInfo& reqInfo) const
{
    Structs::RequestResult rr;
    Structs::GetRoomsResponse grr;
    JsonResponsePacketSerializer j;

    grr.rooms = m_handlerFactory.getRoomManager().getRooms();
    grr.status = reqInfo.id;

    rr.response = j.serializeResponse(grr);
    rr.newHandler = this;

}

Structs::RequestResult MenuRequestHandler::getPlayersInRoom(Structs::RequestInfo& reqInfo) const
{
    Structs::RequestResult rr;

    Structs::GetPlayersInRoomRequest rd;
    Structs::GetPlayersInRoomResponse grr;


    JsonResponsePacketSerializer j;
    JsonRequestPacketDeserializer h;

    rd = h.deserializeGetPlayersRequest(reqInfo.buffer);
    std::vector<Structs::RoomData> roomInfo = m_handlerFactory.getRoomManager().getRooms();

    for (auto it : roomInfo)
    {
        grr.players.push_back(it.name);
    }

    rr.response = j.serializeResponse(grr);
    rr.newHandler = this;
}

Structs::RequestResult MenuRequestHandler::getPersonalStats(Structs::RequestInfo& reqInfo) const
{
    return Structs::RequestResult();
}

Structs::RequestResult MenuRequestHandler::getHighScore(Structs::RequestInfo& reqInfo) const
{
    return Structs::RequestResult();
}

Structs::RequestResult MenuRequestHandler::joinRoom(Structs::RequestInfo& reqInfo) const
{
    return Structs::RequestResult();
}

Structs::RequestResult MenuRequestHandler::createRoom(Structs::RequestInfo& reqInfo) const
{
    return Structs::RequestResult();
}

Structs::RequestResult MenuRequestHandler::handleErrorRequest(Structs::RequestInfo& reqInfo) const
{
    return Structs::RequestResult();
}




