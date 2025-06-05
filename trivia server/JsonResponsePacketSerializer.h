#pragma once
#include <string>
#include <vector>
#include "Constant.h"

class JsonResponsePacketSerializer 
{
public:
	JsonResponsePacketSerializer() = default; //constructor default
	~JsonResponsePacketSerializer();
	std::vector<unsigned char> serializeResponse(Structs::ErrorResponse er);
	std::vector<unsigned char> serializeResponse(Structs::LoginResponse lr);
	std::vector<unsigned char> serializeResponse(Structs::SignupResponse sr);
	std::vector<unsigned char> serializeAll(std::vector<unsigned char> vec_char, int code);
	std::vector<unsigned char> buffer;

	std::vector<unsigned char> serializeResponse(Structs::LogoutResponse lor);
	std::vector<unsigned char> serializeResponse(Structs::GetRoomsResponse grr);
	std::vector<unsigned char> serializerResponse(Structs::GetPlayersInRoomResponse gpr);
	std::vector<unsigned char> serializeResponse(Structs::JoinRoomResponse jrr);
	std::vector<unsigned char> serializeResponse(Structs::CreateRoomResponse crr);
	std::vector<unsigned char> serializeResponse(Structs::GetHighScoreResponse ghr);
	std::vector<unsigned char> serializeResponse(Structs::GetPersonalStatsResponse gsr);

};

