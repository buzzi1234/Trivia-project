#include "LoginRequestHandler.h"

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
    JsonResponsePacketSerializer j; // obj for serializer

    Structs::RequestResult* rr = new Structs::RequestResult();
    Structs::LoginResponse* sr = new Structs::LoginResponse(); //Response obj for seriazlie

    sr->status = ri.id;
    rr->response = j.serializeResponse(*sr);

    delete sr;

    rr->newHandler = new LoginRequestHandler();
    return *rr;
}


/// <summary>
/// The function handle sign request
/// </summary>
/// <param name="ri"> Request info ( id, time, buffer ) </param>
/// <returns> RequestResult of ( log, sign, error ) </returns>
Structs::RequestResult LoginRequestHandler::handleSignupRequest(Structs::RequestInfo& ri) const
{
    JsonResponsePacketSerializer j;// obj for serializer

    Structs::RequestResult* rr = new Structs::RequestResult();
    Structs::SignupResponse* sr = new Structs::SignupResponse(); //Response obj for seriazlie

    sr->status = ri.id;
    rr->response = j.serializeResponse(*sr);

    delete sr;

    rr->newHandler = new LoginRequestHandler();
    return *rr;
}

/// <summary>
/// The function handle error request
/// </summary>
/// <param name="ri"> Request info ( id, time, buffer ) </param>
/// <returns> RequestResult of ( log, sign, error ) </returns>
Structs::RequestResult LoginRequestHandler::handleErrorRequest(Structs::RequestInfo& ri) const
{
    JsonResponsePacketSerializer j; // obj for serializer

    Structs::RequestResult* rr = new Structs::RequestResult();
    Structs::ErrorResponse* sr = new Structs::ErrorResponse(); //Response obj for seriazlie

    sr->mesagge = R"({
        "mesagge" : "ERROR"})";
    rr->response = j.serializeResponse(*sr);

    delete sr;

    rr->newHandler = new LoginRequestHandler();
    return *rr;
}


