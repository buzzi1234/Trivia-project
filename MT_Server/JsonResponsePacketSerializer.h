#pragma once
#include <string>
#include <vector>
#include "Structs.h"

//Codes for the buffer 
#define LOG_CODE 1
#define SIGN_CODE 2
#define ERROR_CODE 3

class JsonResponsePacketSerializer 
{
public:
	JsonResponsePacketSerializer() = default; //constructor default
	~JsonResponsePacketSerializer();
	std::vector<unsigned char> serializeResponse(Structs::ErrorResponse er);
	std::vector<unsigned char> serializeResponse(Structs::LoginResponse lr);
	std::vector<unsigned char> serializeResponse(Structs::SignupResponse sr);
	std::vector<unsigned char> serializeAll(std::vector<unsigned char> vec_char, int code);
	static std::vector<unsigned char> buffer;
};

