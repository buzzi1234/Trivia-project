#pragma once

#include <iostream>
#include "Constant.h"
#include <vector>
#include "LoggedUser.h"

class Room
{
public:
	Room() = default;
	Room(Structs::RoomData rd, std::vector<LoggedUser> lu_list);
	~Room();
	void addUser(LoggedUser lu);
	void removeUser(LoggedUser lu);
	std::vector<std::string> getAllUsers() const;
	Structs::RoomData getRoomData() const;

private:
	Structs::RoomData m_metadata;
	std::vector<LoggedUser> m_users;
	bool isUserExist(LoggedUser lu);
};

