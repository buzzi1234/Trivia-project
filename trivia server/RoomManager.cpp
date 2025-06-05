#include "RoomManager.h"

//destructor
RoomManager::~RoomManager()
{
	this->m_rooms.clear();
}

/// <summary>
/// The function create a new room
/// </summary>
/// <param name="lu"> User that want to create a room </param>
/// <param name="rd"> Room data </param>
void RoomManager::createRoom(LoggedUser lu, Structs::RoomData rd)
{
	std::vector<LoggedUser> vec;
	vec.push_back(lu);
	this->m_rooms.insert({ rd.id, Room(rd, vec) });
}

/// <summary>
/// The function delete a room by his id
/// </summary>
/// <param name="id"> room id </param>
void RoomManager::deleteRoom(unsigned int id)
{
	this->m_rooms.erase(id);
}

/// <summary>
/// The func get the room status
/// </summary>
/// <param name="id"> The room id </param>
/// <returns> Room status</returns>
int RoomManager::getRoomState(unsigned int id) const
{
	auto it = this->m_rooms.find(id);
	if (it != this->m_rooms.end())
	{
		return it->second.getRoomData().status;
	}
	return ROOM_DOES_NOT_EXIST;
}

/// <summary>
/// The function return all the rooms 
/// </summary>
/// <returns> Vector of all the rooms </returns>
std::vector<Structs::RoomData> RoomManager::getRooms() const
{
	std::vector<Structs::RoomData> rd_lst;
	for (auto it : this->m_rooms)
	{
		rd_lst.push_back(it.second.getRoomData());
	}
	return rd_lst;
}

/// <summary>
/// The function get a room by his id
/// </summary>
/// <param name="id"> The room id </param>
/// <returns> Room if id exist else null </returns>
std::optional<Room*> RoomManager::getRoom(unsigned int id)
{
	std::optional<Room*> op = &(this->m_rooms.find(id)->second);
	if (op.has_value())
	{
		return op;
	}
	return std::nullopt;
}
