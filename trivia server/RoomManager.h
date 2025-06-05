#pragma once

#include "Constant.h"
#include "Room.h"
#include <map>
#include <vector>


class RoomManager
{
public:
	RoomManager() = default;
	~RoomManager();

	void createRoom(LoggedUser lu, Structs::RoomData rd);
	void deleteRoom(unsigned int id);
	int getRoomState(unsigned int id) const;
	std::vector<Structs::RoomData> getRooms() const;
	std::optional<Room*> getRoom(unsigned int id);
private:
	std::map<unsigned int, Room> m_rooms;
};

