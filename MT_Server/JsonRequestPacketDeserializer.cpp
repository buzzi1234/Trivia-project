#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
    nlohmann::json loginJson = jsonDeserializer(buffer);

    LoginRequest* t = new LoginRequest();
    t->password = loginJson["password"];
    t->username = loginJson["username"];

    return *t;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
    nlohmann::json SignupJson = jsonDeserializer(buffer);

    SignupRequest* t = new SignupRequest();
    t->password = SignupJson["password"];
    t->username = SignupJson["username"];
    t->email = SignupJson["email"];

    return *t;
}

nlohmann::json JsonRequestPacketDeserializer::jsonDeserializer(std::vector<unsigned char> buffer)
{
    int len = (static_cast<int>(buffer[1]) << 24) |
        (static_cast<int>(buffer[2]) << 16) |
        (static_cast<int>(buffer[3]) << 8) |
        (static_cast<int>(buffer[4]));

    for (int i = 0; i < 5; i++)
    {
        buffer.erase(buffer.begin());
    }

    std::string jsonStr(buffer.begin(), buffer.end());

    return nlohmann::json::parse(jsonStr);
}
