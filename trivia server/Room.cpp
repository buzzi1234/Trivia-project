#include "Room.h"

//constructor
Room::Room(Structs::RoomData rd, std::vector<LoggedUser> lu_list) : m_metadata(rd), m_users(lu_list)
{
}

//destructor
Room::~Room()
{
	m_users.clear();
}

/// <summary>
/// The function add a new user to the room
/// </summary>
/// <param name="lu"> User that want to log to the room </param>
void Room::addUser(LoggedUser lu)
{
	if (!isUserExist(lu))
	{
		m_users.push_back(lu);
	}
	else
	{
		std::cout << "Name Already Exist!, " << NAME_EXIST_ERROR;
	}
}

/// <summary>
/// he function remove a user from the room
/// </summary>
/// <param name="lu"> User that want to log to the room </param>
void Room::removeUser(LoggedUser lu)
{
	int i = 0;
	for (auto it : this->m_users)
	{
		if (it.getUserName() == lu.getUserName())
		{
			this->m_users.erase(this->m_users.begin() + i);
		}
		i++;
	}
}

/// <summary>
/// The function gets all the logged users in this room
/// </summary>
/// <returns> The names of the logged users in this room </returns>
std::vector<std::string> Room::getAllUsers() const
{
	std::vector<std::string> names;
	for (auto it : this->m_users)
	{
		names.push_back(it.getUserName());
	}
	return names;
}

/// <summary>
/// The func get the data of the room
/// </summary>
/// <returns> room data </returns>
Structs::RoomData Room::getRoomData() const
{
	return this->m_metadata;
}

/// <summary>
/// The func checks if the user is already logged to this room
/// </summary>
/// <param name="lu"> User that want to log to the room </param>
/// <returns> True if the user exist false otherwise </returns>
bool Room::isUserExist(LoggedUser lu)
{
	for (auto it : this->m_users)
	{
		if (it.getUserName() == lu.getUserName())
		{
			return true;
		}
	}
	return false;
}
