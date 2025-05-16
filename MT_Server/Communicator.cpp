#include "Communicator.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

Communicator::Communicator() : _running(false)
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    _serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_serverSocket == INVALID_SOCKET)
        throw std::runtime_error("Failed to create socket");
}

Communicator::~Communicator()
{
    stop();
    WSACleanup();
}

void Communicator::bindAndListen(int port) const
{
	sockaddr_in sa = { 0 };
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;
    sa.sin_port = htons(port);

    if (bind(_serverSocket, (SOCKADDR*)&sa, sizeof(sa)) == SOCKET_ERROR)
        throw std::runtime_error("Bind failed");

    if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
        throw std::runtime_error("Listen failed");
}

void Communicator::startHandleRequests()
{
    _running = true;
    std::cout << "server is listening for connections " << std::endl;
    while (_running)
    {
        SOCKET clientSocket = accept(_serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET)
        {
            if (!_running) break;
            std::cerr << "Accept failed" << std::endl;
            continue;
        }

        std::lock_guard<std::mutex> lock(_clientsMutex);
        _clients[clientSocket] = new LoginRequestHandler();

        std::thread(&Communicator::handleNewClient, this, clientSocket).detach();
    }
}

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

void Communicator::handleNewClient(SOCKET clientSocket)
{
    try
    {
        std::unique_ptr<IRequestHandler> handler = std::make_unique<LoginRequestHandler>();

        while (true)
        {
            char headerBuffer[5];
            int bytesRead = recv(clientSocket, headerBuffer, 5, 0);
            if (bytesRead <= 0)
            {
                break;
            }
            uint8_t id = headerBuffer[0];
            uint32_t size = *(uint32_t*)(headerBuffer + 1); 

            std::vector<uint8_t> buffer(size);
            bytesRead = recv(clientSocket, reinterpret_cast<char*>(buffer.data()), size, 0);
            if (bytesRead <= 0)
                break;

            Structs::RequestInfo info;
            info.id = id;
            info.buffer = buffer;
            info.receivalTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            Structs::RequestResult result = handler->handleRequest(info);
            send(clientSocket, reinterpret_cast<const char*>(result.response.data()), result.response.size(), 0);
            handler.reset(result.newHandler);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception in handleNewClient: " << e.what() << std::endl;
    }

    closesocket(clientSocket);
}