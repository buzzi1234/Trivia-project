#include "JsonResponsePacketSerializer.h"
#include <bitset>


//destructor
JsonResponsePacketSerializer::~JsonResponsePacketSerializer()
{
	this->buffer.clear();
}

/// <summary>
/// The function serialize the ErrorResponse struct into buffer
/// </summary>
/// <param name="er"> A struct that containe error message </param>
/// <returns> Buffer ( row of bits ) to the client </returns>
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(Structs::ErrorResponse er)
{
	std::vector<unsigned char> vec_char(er.mesagge.begin(), er.mesagge.end());

	return serializeAll(vec_char, ERROR_CODE);
	
}

/// <summary>
/// The function serialize the LoginResponse struct into buffer
/// </summary>
/// <param name="lr"> A struct that containe statue num </param>
/// <returns> Buffer ( row of bits ) to the client </returns>
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(Structs::LoginResponse lr)
{
	std::string status = R"({"status": )" + std::to_string(lr.status) + "}";
	std::vector<unsigned char> vec_char(status.begin(), status.end());
	
	return serializeAll(vec_char, LOG_CODE);
}

/// <summary>
/// The function serialize the SigninResponse struct into buffer
/// </summary>
/// <param name="lr"> A struct that containe statue num </param>
/// <returns> Buffer ( row of bits ) to the client </returns>
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(Structs::SignupResponse sr)
{
	std::string status = R"({"status" : )" + std::to_string(sr.status) + "}";
	std::vector<unsigned char> vec_char(status.begin(), status.end());

	return serializeAll(vec_char, SIGN_CODE);
}

/// <summary>
/// The function create a buffer that containe the code, length, msg
/// </summary>
/// <param name="vec_char"> buffer of the message </param>
/// <param name="code"> code of the message </param>
/// <returns> the complete buffer </returns>
std::vector<unsigned char> JsonResponsePacketSerializer::serializeAll(std::vector<unsigned char> vec_char, int code)
{
	unsigned char code_byte = static_cast<unsigned char>(code); //turn code into byte

	//turn length of msg into 4 byte 
	std::vector<unsigned char> len(4);
	len[0] = (vec_char.size() >> 24) & 0xFF;
	len[1] = (vec_char.size() >> 16) & 0xFF;
	len[2] = (vec_char.size() >> 8) & 0xFF;
	len[3] = vec_char.size() & 0xFF;


	this->buffer.push_back(code_byte);

	for (unsigned char c : len) {
		this->buffer.push_back(c);
	}

	for (unsigned char c : vec_char) {
		this->buffer.push_back(c);
	}

	return this->buffer;
}

/// <summary>
/// The func turn room data to json masagge
/// </summary>
/// <param name="rd"> Room data </param>
/// <returns> json msg </returns>
std::string JsonResponsePacketSerializer::RoomDataToJsonMsg(Structs::RoomData rd)
{
	std::string str = R"({"id" : )" + std::to_string(rd.id) +
		R"(,"name" : )" + rd.name +
		R"(,"maxPlayers" : )" + std::to_string(rd.maxPlayers) +
		R"(,"numOfQuestionsInGame" : )" + std::to_string(rd.numOfQuestionsInGame) +
		R"(,"timePerQuestion" : )" + std::to_string(rd.timePerQuestion) +
		R"(,"status" : )" + std::to_string(rd.status) + "}";
	return str;
}

/// <summary>
/// The function serialize the LogoutResponse struct into buffer
/// </summary>
/// <param name="lr"> A struct that containe status num </param>
/// <returns> Buffer ( row of bits ) to the client </returns>
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(Structs::LogoutResponse lor)
{
	std::string status = R"({"status" : )" + std::to_string(lor.status) + "}";
	std::vector<unsigned char> vec_char(status.begin(), status.end());

	return serializeAll(vec_char, LOGOUT);
}

/// <summary>
/// The function serialize the GetRoomsResponse struct into buffer
/// </summary>
/// <param name="lr"> A struct that containe status num and a vector of room data </param>
/// <returns> Buffer ( row of bits ) to the client </returns>
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(Structs::GetRoomsResponse grr)
{
	std::string status = R"({"status" : )" + std::to_string(grr.status);
	int i = 1;
	for (auto it : grr.rooms)
	{
		status += R"(,room)" + std::to_string(i) + R"( : )" + RoomDataToJsonMsg(it) + "}";
		i++;
	}
	std::vector<unsigned char> vec_char(status.begin(), status.end());

	return serializeAll(vec_char, GET_ROOMS);

}

/// <summary>
/// The function serialize the GetPlayersInRoomResponse struct into buffer
/// </summary>
/// <param name="lr"> A struct that containe status num and a vector of players that in the room </param>
/// <returns> Buffer ( row of bits ) to the client </returns>
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(Structs::GetPlayersInRoomResponse gpr)
{
	std::string status = "{";
	int i = 1;
	for (auto it : gpr.players)
	{
		status += R"(player)" + std::to_string(i) + " : " + it + ",";
		i++;
	}
	status[status.size() - 1] = '}';
	std::vector<unsigned char> vec_char(status.begin(), status.end());

	return serializeAll(vec_char, GET_PLAYERS_IN_ROOM);
}

/// <summary>
/// The function serialize the JoinRoomResponse struct into buffer
/// </summary>
/// <param name="lr"> A struct that containe status num </param>
/// <returns> Buffer ( row of bits ) to the client </returns>
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(Structs::JoinRoomResponse jrr)
{
	std::string status = R"({"status" : )" + std::to_string(jrr.status) + "}";
	std::vector<unsigned char> vec_char(status.begin(), status.end());

	return serializeAll(vec_char, JOIN_ROOM);
}

/// <summary>
/// The function serialize the CreateRoomResponse struct into buffer
/// </summary>
/// <param name="lr"> A struct that containe status num </param>
/// <returns> Buffer ( row of bits ) to the client </returns>
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(Structs::CreateRoomResponse crr)
{
	std::string status = R"({"status" : )" + std::to_string(crr.status) + "}";
	std::vector<unsigned char> vec_char(status.begin(), status.end());

	return serializeAll(vec_char, CREATE_ROOM);
}


/// <summary>
/// The function serialize the GetHighScoreResponse struct into buffer
/// </summary>
/// <param name="lr"> A struct that containe status num and a vector of the highest scores </param>
/// <returns> Buffer ( row of bits ) to the client </returns>
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(Structs::GetHighScoreResponse ghr)
{
	std::string status = R"({"status" : )" + std::to_string(ghr.status);
	int i = 1;
	for (auto it : ghr.statistics)
	{
		status += R"(score)" + std::to_string(i) + " : " + std::to_string(it.second) + ",";
		i++;
	}
	std::vector<unsigned char> vec_char(status.begin(), status.end());

	return serializeAll(vec_char, GET_HIGH_SCORE);
}

/// <summary>
/// The function serialize the GetPersonalStatsResponse struct into buffer
/// </summary>
/// <param name="lr"> A struct that containe status num and a vector of the stats </param>
/// <returns> Buffer ( row of bits ) to the client </returns>
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(Structs::GetPersonalStatsResponse gsr)
{
	std::string status = R"({"status" : )" + std::to_string(gsr.status);
	int i = 1;
	for (auto it : gsr.statistics)
	{
		status += R"(stats)" + std::to_string(i) + " : " + it + ",";
		i++;
	}
	std::vector<unsigned char> vec_char(status.begin(), status.end());

	return serializeAll(vec_char, GET_PERSONAL_STATS);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(Structs::LeaveRoomResponse lrr)
{
	std::string jsonMsg = R"({"status" : )" + std::to_string(lrr.status) + "}";
	std::vector<unsigned char> vec_char(jsonMsg.begin(), jsonMsg.end());

	return serializeAll(vec_char, LEAVE_ROOM);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(Structs::StartGameResponse sgr)
{
	std::string jsonMsg = R"({"status" : )" + std::to_string(sgr.status) + "}";
	std::vector<unsigned char> vec_char(jsonMsg.begin(), jsonMsg.end());

	return serializeAll(vec_char, START_GAME);;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(Structs::GetRoomStateResponse ggr)
{
	std::string jsonMsg = "{\"status\":" + std::to_string(ggr.status) +
		",\"hasGameBegun\":" + std::to_string(ggr.hasGameBegun) +
		",\"players\":[";

	for (int i = 0; i < ggr.players.size(); i++)
	{
		jsonMsg += "\"" + ggr.players[i] + "\"";
		if (i != ggr.players.size() - 1)
		{
			jsonMsg += ",";
		}
	}

	jsonMsg += "],\"questionCount\":" + std::to_string(ggr.questionCount) +
		",\"answerTimeout\":" + std::to_string(ggr.answerTimeout) +
		",\"maxPlayers\":" + std::to_string(ggr.maxPlayers) + "}";

	std::vector<unsigned char> vec_char(jsonMsg.begin(), jsonMsg.end());
	return serializeAll(vec_char, GET_ROOM_STATE);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(Structs::CloseRoomResponse crr)
{
	std::string jsonMsg = R"({"status" : )" + std::to_string(crr.status) + "}";
	std::vector<unsigned char> vec_char(jsonMsg.begin(), jsonMsg.end());

	return serializeAll(vec_char, CLOSE_ROOM);
}

