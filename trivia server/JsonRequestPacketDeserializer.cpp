#include "JsonRequestPacketDeserializer.h"

/// <summary>
/// The function deserialize the buffer into json
/// and than it takes the json and convert it to a LoginRequest struct
/// </summary>
/// <param name="buffer"> Row of bytes </param>
/// <returns> LoginRequest struct ( password, username ) </returns>
Structs::LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer) const
{
    nlohmann::json loginJson = jsonDeserializer(buffer); // converting buffer into json 

    //Create new LoginRequest with parmeters from json
    Structs::LoginRequest* t = new Structs::LoginRequest();
    t->password = loginJson["password"];
    t->username = loginJson["username"];

    return *t;
}

/// <summary>
/// The function deserialize the buffer into json
/// and than it takes the json and convert it to a SignupRequest struct 
/// </summary>
/// <param name="buffer"> Row of bytes </param>
/// <returns> SignupRequest struct ( password, username, email ) </returns>
Structs::SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer) const
{
    nlohmann::json SignupJson = jsonDeserializer(buffer); // converting into json

    //Create new SignupRequest with parmeters
    Structs::SignupRequest t;
    t.password = SignupJson["password"];
    t.username = SignupJson["username"];
    t.mail = SignupJson["mail"];

    return t;
}

/// <summary>
/// The function convert the buffer into json parmeter
/// </summary>
/// <param name="buffer"> Row of bytes </param>
/// <returns> the json parameter </returns>
nlohmann::json JsonRequestPacketDeserializer::jsonDeserializer(std::vector<unsigned char> buffer) const
{
    std::string jsonStr(buffer.begin(), buffer.end());

    return nlohmann::json::parse(jsonStr);
}

/// <summary>
/// The function deserialize the buffer into json
/// and than it takes the json and convert it to a GetPlayersInRoomRequest struct 
/// </summary>
/// <param name="buffer"> Row of bytes </param>
/// <returns> GetPlayersInRoomRequest struct ( roomId ) </returns>
Structs::GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(std::vector<unsigned char> buffer) const
{
    nlohmann::json PlayersInRoom = jsonDeserializer(buffer); // converting into json

    //Create new GetPlayersInRoomRequest with parmeters
    Structs::GetPlayersInRoomRequest t;
    t.roomId = PlayersInRoom["roomId"];

    return t;
}

/// <summary>
/// The function deserialize the buffer into json
/// and than it takes the json and convert it to a JoinRoomRequest struct 
/// </summary>
/// <param name="buffer"> Row of bytes </param>
/// <returns> JoinRoomRequest struct ( roomId ) </returns>
Structs::JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> buffer) const
{
    nlohmann::json JoinRoom = jsonDeserializer(buffer); // converting into json

    //Create new JoinRoomRequest with parmeters
    Structs::JoinRoomRequest t;
    t.roomId = JoinRoom["roomId"];

    return t;
}

/// <summary>
/// The function deserialize the buffer into json
/// and than it takes the json and convert it to a CreateRoomRequest struct 
/// </summary>
/// <param name="buffer"> Row of bytes </param>
/// <returns> CreateRoomRequest struct ( roomName, maxUsers, questionCount, answerTimeout ) </returns>
Structs::CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> buffer) const
{
    nlohmann::json CreateRoom = jsonDeserializer(buffer); // converting into json

    //Create new CreateRoomRequest with parmeters
    Structs::CreateRoomRequest t;
    t.roomName = CreateRoom["roomName"];
    t.maxUsers = CreateRoom["maxUsers"];
    t.questionCount = CreateRoom["questionCount"];
    t.answerTimeout = CreateRoom["answerTimeout"];

    return t;
}

Structs::CloseRoomRequest JsonRequestPacketDeserializer::deserializeCloseRoomRequest(std::vector<unsigned char> buffer) const
{
	Structs::CloseRoomRequest t;
    return t;
}

Structs::StartGameRequest JsonRequestPacketDeserializer::deserializeStartGameRequest(std::vector<unsigned char> buffer) const
{
	Structs::StartGameRequest t;
    return t;
}

Structs::GetRoomStateRequest JsonRequestPacketDeserializer::deserializeGetRoomStateRequest(std::vector<unsigned char> buffer) const
{
	Structs::GetRoomStateRequest t; 
    return t;
}

Structs::LeaveRoomRequest JsonRequestPacketDeserializer::deserializeLeaveRoomRequest(std::vector<unsigned char> buffer) const
{
	Structs::LeaveRoomRequest t;
    return t;
}
