#include "Communicator.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include <ctime>
#include <algorithm>
#include <iostream>

#define BUFFER_SIZE 1024

#pragma comment(lib, "ws2_32.lib")

//constructor
Communicator::Communicator(RequestHandlerFactory& handlerFactory) : _handlerFactory(handlerFactory), _running(false)
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData); //activate the Winsock DLL
    _serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // create a socket for TCP communication
    if (_serverSocket == INVALID_SOCKET)
        throw std::runtime_error("Failed to create socket");
}

//destructor
Communicator::~Communicator()
{
    stop();
    WSACleanup();
}

/// <summary>
/// The function binds the server socket to the specified port and starts listening for incoming connections.
/// </summary>
/// <param name="port"> the server port </param>
void Communicator::bindAndListen(int port) const
{
    sockaddr_in sa = { 0 };
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = INADDR_ANY;
    sa.sin_port = htons(port);

    if (bind(_serverSocket, (SOCKADDR*)&sa, sizeof(sa)) == SOCKET_ERROR) // bind the socket to the address and port
        throw std::runtime_error("Bind failed");

    if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR) // listen for incoming connections
        throw std::runtime_error("Listen failed");
}

/// <summary>
/// The func starts the server and listens for incoming client connections.
/// </summary>
void Communicator::startHandleRequests()
{
    _running = true;
    std::cout << "server is listening for connections " << std::endl;
    while (_running)
    {
        SOCKET clientSocket = accept(_serverSocket, nullptr, nullptr); // accept a new client connection
        if (clientSocket == INVALID_SOCKET)
        {
            if (!_running) break;
            std::cerr << "Accept failed" << std::endl;
            continue;
        }

        std::lock_guard<std::mutex> lock(_clientsMutex);
        _clients[clientSocket] = _handlerFactory.createLoginRequestHandler(); // create a new request handler for the client

        std::thread(&Communicator::handleNewClient, this, clientSocket).detach();
    }
}

/// <summary>
/// The func stops the server, closes the server socket, and disconnects all clients.
/// </summary>
void Communicator::stop()
{
    _running = false;
    closesocket(_serverSocket);

    std::lock_guard<std::mutex> lock(_clientsMutex);
    for (auto& pair : _clients)
    {
        SOCKET sock = pair.first;
        IRequestHandler* handler = pair.second;

        closesocket(sock);
        delete handler;
    }
    _clients.clear();
}

/// <summary>
/// The function handles a new client connection.
/// </summary>
/// <param name="clientSocket"> the client socket </param>
void Communicator::handleNewClient(SOCKET clientSocket)
{
    try
    {
        std::unique_ptr<const IRequestHandler> handler(_handlerFactory.createLoginRequestHandler());

        while (true)
        {
            char headerBuffer[5];
            int bytesRead = recv(clientSocket, headerBuffer, 5, 0);
            if (bytesRead <= 0)
            {
                break;
            }

            uint8_t id = headerBuffer[0];
            uint8_t size = headerBuffer[1] << 24 | headerBuffer[2] << 16 | headerBuffer[3] << 8 | headerBuffer[4];

            std::vector<unsigned char> buffer(size);
            bytesRead = recv(clientSocket, (char*)buffer.data(), size, 0);
            if (bytesRead <= 0)
                break;

            Structs::RequestInfo info;
            info.id = id;
            info.buffer = buffer;
            info.receivalTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

            Structs::RequestResult result = handler->handleRequest(info);
            if (result.newHandler != nullptr)
            {
                handler.reset(result.newHandler);
            }

            send(clientSocket, reinterpret_cast<const char*>(result.response.data()), result.response.size(), 0);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception in handleNewClient: " << e.what() << std::endl;
    }

    closesocket(clientSocket);
}
