#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"

#define ERROR_CODE 3

struct LoginRequest
{
	std::string username;
	std::string password;
}typedef LoginRequest;

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
}typedef SignupRequest;



class JsonRequestPacketDeserializer
{
public:
	LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer);
	SignupRequest deserializeSignupRequest(std::vector<unsigned char> buffer);
	nlohmann::json jsonDeserializer(std::vector<unsigned char> buffer);
};

