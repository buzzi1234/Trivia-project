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
};

