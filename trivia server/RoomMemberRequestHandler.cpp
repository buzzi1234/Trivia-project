#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(LoggedUser user, Room room, RequestHandlerFactory& factory)
	: m_user(user), m_room(room), m_handlerFactory(factory)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(Structs::RequestInfo& ri) const
{
    return ri.id == LEAVE_ROOM || ri.id == GET_ROOM_STATE;
}

Structs::RequestResult RoomMemberRequestHandler::handleRequest(Structs::RequestInfo& ri) const
{
	switch (ri.id)
	{
	case LEAVE_ROOM:
		return leaveRoom();
		break;
	case GET_ROOM_STATE:
		return getRoomState();
		break;
	default:
		return { JsonResponsePacketSerializer().serializeResponse({"Invalid Request"}), nullptr };
		break;
	}
}

Structs::RequestResult RoomMemberRequestHandler::leaveRoom() const
{
	auto& roomManager = m_handlerFactory.getRoomManager();
	auto roomOptional = roomManager.getRoom(m_room.getRoomData().id);

	if (roomOptional)
	{
		roomOptional.value()->removeUser(m_user);
	}
	Structs::LeaveRoomResponse resp = { 1 };
	std::vector<unsigned char> msg = JsonResponsePacketSerializer().serializeResponse(resp);

	return { msg, m_handlerFactory.createMenuRequestHandler(m_user) };
}

Structs::RequestResult RoomMemberRequestHandler::getRoomState() const
{
	Structs::RoomData rd = m_room.getRoomData();
	Structs::GetRoomStateResponse resp = { 1, m_room.getAllUsers(), rd.numOfQuestionsInGame, 0, rd.timePerQuestion,};
	std::vector<unsigned char> msg = JsonResponsePacketSerializer().serializeResponse(resp);

	return { msg, nullptr };
}

