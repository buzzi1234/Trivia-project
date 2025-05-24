#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
#include <iostream>

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
    JsonResponsePacketSerializer s; // obj for serializer
    JsonRequestPacketDeserializer d;

    Structs::LoginRequest req = d.deserializeLoginRequest(ri.buffer);
    int status = _handlerFactory.getLoginManager().login(req.username, req.password);

    Structs::LoginResponse res;
    res.status = status;

    Structs::RequestResult result;
    result.response = s.serializeResponse(res);

    if (status == LOG_CODE)
    {
        result.newHandler = _handlerFactory.createMenuRequestHandler();
    }
    else
    {
        result.newHandler = new LoginRequestHandler(_handlerFactory);
    }

    return result;
}


/// <summary>
/// The function handle sign request
/// </summary>
/// <param name="ri"> Request info ( id, time, buffer ) </param>
/// <returns> RequestResult of ( log, sign, error ) </returns>
Structs::RequestResult LoginRequestHandler::handleSignupRequest(Structs::RequestInfo& ri) const
{
    JsonResponsePacketSerializer s;// obj for serializer
    JsonRequestPacketDeserializer d;

    Structs::SignupRequest req = d.deserializeSignupRequest(ri.buffer);
    int status = _handlerFactory.getLoginManager().signup(req.username, req.password, req.email);

    Structs::SignupResponse res;
    res.status = status;
    Structs::RequestResult result;
    result.response = s.serializeResponse(res);
    if (status == SIGN_CODE)
    {
        result.newHandler = _handlerFactory.createMenuRequestHandler();
    }
    else
    {
        result.newHandler = new LoginRequestHandler(_handlerFactory);
    }
    return result;
}

/// <summary>
/// The function handle error request
/// </summary>
/// <param name="ri"> Request info ( id, time, buffer ) </param>
/// <returns> RequestResult of ( log, sign, error ) </returns>
Structs::RequestResult LoginRequestHandler::handleErrorRequest(Structs::RequestInfo& ri) const
{
    JsonResponsePacketSerializer s; // obj for serializer

    Structs::ErrorResponse res;

    res.mesagge = R"({
        "mesagge" : "ERROR"})";
    Structs::RequestResult reault;
    reault.response = s.serializeResponse(res);
    reault.newHandler = nullptr;

    return reault;
}


