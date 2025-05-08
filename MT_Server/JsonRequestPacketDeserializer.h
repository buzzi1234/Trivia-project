#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"

//Error code in bufffer
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
	JsonRequestPacketDeserializer() = default; //constrctor default
	~JsonRequestPacketDeserializer() = default; //destrctur default
	LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer) const;
	SignupRequest deserializeSignupRequest(std::vector<unsigned char> buffer) const;
	nlohmann::json jsonDeserializer(std::vector<unsigned char> buffer) const;
};

