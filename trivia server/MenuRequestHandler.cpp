#include "MenuRequestHandler.h"


//consructor
MenuRequestHandler::MenuRequestHandler(LoggedUser loged, RequestHandlerFactory& factory, Communicator& communicator) : m_user(loged), m_handlerFactory(factory), m_communicator(communicator)
{
}


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

    try {
        m_handlerFactory.getLoginManager().logout(m_user.getUserName());
        lr.status = reqInfo.id;
    }
  
    catch (std::exception e)
    {
        lr.status = FAIL_LOGOUT;
    }

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
    if (grr.rooms.empty())
    {
        grr.status = FAIL_GET_ROOMS;
    }
    else
    {
        grr.status = reqInfo.id;
    }

    rr.response = j.serializeResponse(grr);
    rr.newHandler = this;

    return rr;

}

Structs::RequestResult MenuRequestHandler::getPlayersInRoom(Structs::RequestInfo& reqInfo) const
{
    Structs::RequestResult rr;

    Structs::GetPlayersInRoomRequest rd;
    Structs::GetPlayersInRoomResponse grr;


    JsonResponsePacketSerializer j;
    JsonRequestPacketDeserializer h;

    rd = h.deserializeGetPlayersRequest(reqInfo.buffer);
    std::optional<Room*> roomInfo = m_handlerFactory.getRoomManager().getRoom(rd.roomId);

    if (roomInfo.has_value())
    {
        grr.players = roomInfo.value()->getAllUsers();
    }

    rr.response = j.serializeResponse(grr);
    rr.newHandler = this;
    return rr;
}

Structs::RequestResult MenuRequestHandler::getPersonalStats(Structs::RequestInfo& reqInfo) const
{
    Structs::RequestResult rr;
    Structs::GetPersonalStatsResponse ps;

    JsonResponsePacketSerializer j;
    
    ps.statistics = m_handlerFactory.getStatisticsManager().getUserStatistics(m_user.getUserName());

    if (ps.statistics.empty())
    {
        ps.status = FAIL_GET_PERSONAL_STATS;
    }
    else
    {
        ps.status = reqInfo.id;
    }

    rr.response = j.serializeResponse(ps);
    rr.newHandler = this;

    return rr;
    
}

Structs::RequestResult MenuRequestHandler::getHighScore(Structs::RequestInfo& reqInfo) const
{
    Structs::RequestResult rr;
    Structs::GetHighScoreResponse ps;

    JsonResponsePacketSerializer j;

    
    ps.statistics = m_handlerFactory.getStatisticsManager().getHighScore();

    if (ps.statistics.empty())
    {
        ps.status = FAIL_GET_HIGH_SCORE;
    }
    else
    {
        ps.status = reqInfo.id;
    }

    rr.response = j.serializeResponse(ps);
    rr.newHandler = this;

    return rr;
}

Structs::RequestResult MenuRequestHandler::joinRoom(Structs::RequestInfo& reqInfo) const
{
    Structs::RequestResult rr;
    Structs::JoinRoomRequest req;
    Structs::JoinRoomResponse res;

    JsonResponsePacketSerializer j;
    JsonRequestPacketDeserializer d;

    req = d.deserializeJoinRoomRequest(reqInfo.buffer);
    std::optional<Room*> room = m_handlerFactory.getRoomManager().getRoom(req.roomId);
    if (room == std::nullopt)
    {
        res.status = FAIL_JOIN_ROOM;
		rr.newHandler = this;
    }
    else {
        res.status = JOIN_ROOM;
        rr.newHandler = new RoomMemberRequestHandler(m_user, *room.value(), m_handlerFactory);
    }

    rr.response = j.serializeResponse(res);

    return rr;

    
}

Structs::RequestResult MenuRequestHandler::createRoom(Structs::RequestInfo& reqInfo) const
{
    Structs::RequestResult rr;
    Structs::CreateRoomRequest res;
    Structs::CreateRoomResponse req;

    JsonResponsePacketSerializer j;
    JsonRequestPacketDeserializer d;

    res = d.deserializeCreateRoomRequest(reqInfo.buffer);
    if (res.maxUsers > 0 && res.questionCount > 0 && res.roomName != "")
    {
		Structs::RoomData roomData;
        Room* newRoom = m_handlerFactory.getRoomManager().createRoom(m_user, roomData);
        req.status = CREATE_ROOM;
        if (newRoom != nullptr)
        {
            req.status = CREATE_ROOM;
            rr.newHandler = new RoomAdminRequestHandler(m_user, *newRoom, m_handlerFactory, m_communicator);
        }
        else
        {
            req.status = FAIL_CREATE_ROOM;
            rr.newHandler = this;
        }
    }
    else
    {
        req.status = FAIL_CREATE_ROOM;
		rr.newHandler = this;
    }

    rr.response = j.serializeResponse(req);

    return rr;

}

Structs::RequestResult MenuRequestHandler::handleErrorRequest(Structs::RequestInfo& reqInfo) const
{
    JsonResponsePacketSerializer s; // obj for serializer

    Structs::ErrorResponse res;

    res.mesagge = R"({
        "mesagge" : "ERROR"})";
    Structs::RequestResult reault;
    reault.response = s.serializeResponse(res);
    reault.newHandler = nullptr;

    return reault;
}

LoggedUser MenuRequestHandler::getUser() const
{
    return m_user;
}




