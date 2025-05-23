#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"


LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) : _handlerFactory(handlerFactory)
{
}



/// <summary>
/// The function gets RequestInfo struct and checks
/// if the code is login or signup
/// </summary>
/// <param name="ri"> Request info ( id, time, buffer ) </param>
/// <returns> True if login or signup otherwise false </returns>
bool LoginRequestHandler::isRequestRelevant(Structs::RequestInfo& ri) const
{
    return (ri.id == LOG_CODE || ri.id == SIGN_CODE);
}

/// <summary>
/// The function handle any request ( log, sign, error )
/// </summary>
/// <param name="ri"> Request info ( id, time, buffer ) </param>
/// <returns> RequestResult of ( log, sign, error ) </returns>
Structs::RequestResult LoginRequestHandler::handleRequest(Structs::RequestInfo& ri) const
{
    if (isRequestRelevant(ri))
    {
        if (ri.id == LOG_CODE)
        {
            return handleLoginRequest(ri);
        }
        if (ri.id == SIGN_CODE)
        {
            return handleSignupRequest(ri);
        }
    }
    return handleErrorRequest(ri);

}

/// <summary>
/// The function handle log request
/// </summary>
/// <param name="ri"> Request info ( id, time, buffer ) </param>
/// <returns> RequestResult of ( log, sign, error ) </returns>
Structs::RequestResult LoginRequestHandler::handleLoginRequest(Structs::RequestInfo& ri) const
{
    JsonResponsePacketSerializer serializer;

    try 
    {
        nlohmann::json j = nlohmann::json::parse(ri.buffer);
        std::string username = j["username"];
        std::string password = j["password"];

        LoginManager& loginManager = _handlerFactory.getLoginManager();
        int loginResult = loginManager.login(username, password);

        Structs::RequestResult rr;
        Structs::LoginResponse loginResponse;

        loginResponse.status = loginResult;
        rr.response = serializer.serializeResponse(loginResponse);

        rr.newHandler = _handlerFactory.createLoginRequestHandler();

        return rr;
    }
    catch (const std::exception& e) 
    {
        return handleErrorRequest(ri);
    }
}


/// <summary>
/// The function handle sign request
/// </summary>
/// <param name="ri"> Request info ( id, time, buffer ) </param>
/// <returns> RequestResult of ( log, sign, error ) </returns>
Structs::RequestResult LoginRequestHandler::handleSignupRequest(Structs::RequestInfo& ri) const
{
    JsonResponsePacketSerializer serializer;

    try 
    {

        nlohmann::json j = nlohmann::json::parse(ri.buffer);
        std::string username = j["username"];
        std::string password = j["password"];
        std::string email = j["email"];

        LoginManager& loginManager = _handlerFactory.getLoginManager();
        int signupResult = loginManager.signup(username, password, email);

        Structs::RequestResult rr;
        Structs::SignupResponse signupResponse;

        signupResponse.status = signupResult; 
        rr.response = serializer.serializeResponse(signupResponse);

        rr.newHandler = _handlerFactory.createLoginRequestHandler();

        return rr;
    }
    catch (const std::exception& e) 
    {
        return handleErrorRequest(ri);
    }
}

/// <summary>
/// The function handle error request
/// </summary>
/// <param name="ri"> Request info ( id, time, buffer ) </param>
/// <returns> RequestResult of ( log, sign, error ) </returns>
Structs::RequestResult LoginRequestHandler::handleErrorRequest(Structs::RequestInfo& ri) const
{
    JsonResponsePacketSerializer serializer;

    Structs::RequestResult rr;
    Structs::ErrorResponse errorResponse;

    errorResponse.mesagge = R"({"message": "ERROR"})";
    rr.response = serializer.serializeResponse(errorResponse);
    rr.newHandler = _handlerFactory.createLoginRequestHandler();

    return rr;
}


