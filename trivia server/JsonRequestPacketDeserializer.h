#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"
#include "Constant.h"


class JsonRequestPacketDeserializer
{
public:
	JsonRequestPacketDeserializer() = default; //constrctor default
	~JsonRequestPacketDeserializer() = default; //destrctur default
	Structs::LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer) const;
	Structs::SignupRequest deserializeSignupRequest(std::vector<unsigned char> buffer) const;
	nlohmann::json jsonDeserializer(std::vector<unsigned char> buffer) const;

	Structs::GetPlayersInRoomRequest deserializeGetPlayersRequest(std::vector<unsigned char> buffer) const;
	Structs::JoinRoomRequest deserializeJoinRoomRequest(std::vector<unsigned char> buffer) const;
	Structs::CreateRoomRequest deserializeCreateRoomRequest(std::vector<unsigned char> buffer) const;
};

