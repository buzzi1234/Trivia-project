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
