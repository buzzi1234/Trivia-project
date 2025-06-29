#pragma once
#include <vector>
#include <map>
#include <ctime>
#include <string>

class IRequestHandler;

class Structs
{
public:

	struct CreateRoomRequest
	{
		std::string roomName;
		unsigned int maxUsers;
		unsigned int questionCount;
		unsigned int answerTimeout;

	}typedef CreateRoomRequest;

	struct GetPlayersInRoomRequest
	{
		unsigned int roomId;

	}typedef GetPlayersInRoomRequest;
	
	struct JoinRoomRequest
	{
		unsigned int roomId;

	}typedef JoinRoomRequest;

	struct RoomData
	{
		unsigned int id;
		std::string name;
		unsigned int maxPlayers;
		unsigned int numOfQuestionsInGame;
		unsigned int timePerQuestion;
		unsigned int status;
	}typedef RoomData;

	struct LogoutResponse
	{
		unsigned int status;
	};

	struct JoinRoomResponse
	{
		unsigned int status;
	};

	struct CreateRoomResponse
	{
		unsigned int status;
	};

	struct GetRoomsResponse
	{
		unsigned int status;
		std::vector<Structs::RoomData> rooms;
	};

	struct GetPlayersInRoomResponse
	{
		std::vector<std::string> players;
	};

	struct GetHighScoreResponse
	{
		unsigned int status;
		std::map<std::string, int> statistics;
	};

	struct GetPersonalStatsResponse
	{
		unsigned int status;
		std::vector<std::string> statistics;
	};


	struct RequestResult
	{
		std::vector<unsigned char> response;
		const IRequestHandler* newHandler;

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
		std::string mail;
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

	struct LeaveRoomResponse
	{
		unsigned int status; //status need to be 1
	};

	struct StartGameResponse
	{
		unsigned int status; //status need to be 1
	};
	
	struct GetRoomStateResponse
	{
		unsigned int status; //status need to be 1
		std::vector<std::string> players;
		unsigned int questionCount;
		unsigned int hasGameBegun;
		unsigned int answerTimeout;
		unsigned int maxPlayers;
	};

	struct CloseRoomResponse
	{
		unsigned int status; //status need to be 1
	};
};

