#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(LoggedUser user, Room& room, RequestHandlerFactory& handlerFactory, Communicator& communicator)
	: m_user(user), m_room(room), m_handlerFactory(handlerFactory), m_communicator(communicator)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(Structs::RequestInfo& ri) const
{
    return ri.id == CLOSE_ROOM || ri.id == START_GAME || ri.id == GET_ROOM_STATE;
}

Structs::RequestResult RoomAdminRequestHandler::handleRequest(Structs::RequestInfo& ri) const
{
	switch (ri.id)
	{
	case CLOSE_ROOM:
		return closeRoom();
		break;
	case START_GAME:
		return startGame();
		break;
	case GET_ROOM_STATE:
		return getRoomState();
		break;
	default:
		return { JsonResponsePacketSerializer().serializeResponse({"Invalid Request"}), nullptr };
		break;
	}
}

Structs::RequestResult RoomAdminRequestHandler::closeRoom() const
{
	auto& roomManager = m_handlerFactory.getRoomManager();
	roomManager.deleteRoom(m_room.getRoomData().id);

	Structs::LeaveRoomResponse resp = { 1 };
	auto users = m_room.getAllUsers();
	std::vector<unsigned char> msg = JsonResponsePacketSerializer().serializeResponse(resp);

	for (const auto& username : users)
	{
		auto sockOpt = m_communicator->getUserSocket(username);
		if (sockOpt.has_value())
		{
			send(sockOpt.value(), reinterpret_cast<const char*>(msg.data()), msg.size(), 0);
		}
	}

	return { msg, m_handlerFactory.createMenuRequestHandler(m_user) };
}

Structs::RequestResult RoomAdminRequestHandler::startGame() const
{
	Structs::StartGameResponse resp = { 1 };
	std::vector<unsigned char> msg = JsonResponsePacketSerializer().serializeResponse(resp);

	return { msg, nullptr };
}

Structs::RequestResult RoomAdminRequestHandler::getRoomState() const
{
	Structs::RoomData rd = m_room.getRoomData();
	Structs::GetRoomStateResponse resp = { 1, m_room.getAllUsers(), rd.numOfQuestionsInGame, 0, rd.timePerQuestion, rd.maxPlayers};
	std::vector<unsigned char> msg = JsonResponsePacketSerializer().serializeResponse(resp);
	return { msg, nullptr };
}


