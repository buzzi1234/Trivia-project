#pragma once
#include <vector>
#include <ctime>
#include <string>

class IRequestHandler;

class Structs
{
public:
	struct RequestResult
	{
		std::vector<unsigned char> response;
		IRequestHandler* newHandler;

	}typedef RequestResult;

	struct RequestInfo
	{
		unsigned char id;
		std::time_t receivalTime;
		std::vector<unsigned char> buffer;
	};

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

};

