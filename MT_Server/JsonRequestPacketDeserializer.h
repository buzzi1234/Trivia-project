#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"
#include "Structs.h"

//Error code in bufffer
#define ERROR_CODE 3

class JsonRequestPacketDeserializer
{
public:
	JsonRequestPacketDeserializer() = default; //constrctor default
	~JsonRequestPacketDeserializer() = default; //destrctur default
	Structs::LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer) const;
	Structs::SignupRequest deserializeSignupRequest(std::vector<unsigned char> buffer) const;
	nlohmann::json jsonDeserializer(std::vector<unsigned char> buffer) const;
};

