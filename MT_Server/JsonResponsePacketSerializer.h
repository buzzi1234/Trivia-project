#pragma once
#include <string>
#include <vector>

//Codes for the buffer 
#define LOG_CODE 1
#define SIGN_CODE 2
#define ERROR_CODE 3


struct LoginResponse
{
	unsigned int status; //status need to be 1
} typedef LoginResponse;

struct SignupResponse
{
	unsigned int status; //status need to be 1
} typedef SignupResponse;

struct ErrorResponse
{
	std::string mesagge; //message need to be "{mesagge:"ERROR"}"
} typedef ErrorResponse;

class JsonResponsePacketSerializer 
{
public:
	JsonResponsePacketSerializer();
	~JsonResponsePacketSerializer();
	std::vector<unsigned char> serializeResponse(ErrorResponse er);
	std::vector<unsigned char> serializeResponse(LoginResponse lr);
	std::vector<unsigned char> serializeResponse(SignupResponse sr);
	std::vector<unsigned char> serializeAll(std::vector<unsigned char> vec_char);
	static std::vector<unsigned char> buffer;
};

