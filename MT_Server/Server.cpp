#include "Server.h"
#include <stdexcept>
#include <string>

#pragma comment(lib, "ws2_32.lib")

Server::Server() : _running(true)
{
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_serverSocket == INVALID_SOCKET)
	{
		throw std::runtime_error("Failed to create socet");
	}
}

Server::~Server()
{
	closesocket(_serverSocket);
	for (auto& pair : _clients)
	{
		closesocket(pair.first);
		delete pair.second;
	}
}

void Server::run(int port)
{
	sockaddr_in service{};
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = INADDR_ANY;
	service.sin_port = htons(port);

	if (bind(_serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		throw std::runtime_error("bind failed");
	}

	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::runtime_error("listen failed");
	}

	std::cout << "Server is listening on port " << port << std::endl;

	std::thread consoleThread(&Server::consoleListener, this);
	acceptClients();
	consoleThread.join();
}

void Server::acceptClients()
{
	while (_running)
	{
		SOCKET clientSocket = accept(_serverSocket, nullptr, nullptr);
		if (clientSocket == INVALID_SOCKET)
		{
			if (!_running)
			{
				break;
			}
			std::cerr << "Accept failed" << std::endl;
			continue;
		}

		{
			std::lock_guard<std::mutex> lock(_clientsMutex);
			_clients[clientSocket] = new LoginRequestHandler();
		}

		std::thread(&Server::handleClient, this, clientSocket).detach();
	}
}

void Server::handleClient(SOCKET clientSocket)
{
	std::string hello = "Hello";
	send(clientSocket, hello.c_str(), hello.size(), 0);

	char buffer[6] = { 0 };
	int bytesReceived = recv(clientSocket, buffer, 5, 0);
	if (bytesReceived > 0)
	{
		std::cout << "Cliet said: " << std::string(buffer, bytesReceived) << std::endl;
	}

	closesocket(clientSocket);

	std::lock_guard<std::mutex> lock(_clientsMutex);
	delete _clients[clientSocket];
	_clients.erase(clientSocket);
}

void Server::consoleListener()
{
	std::string input;
	while (_running)
	{
		std::getline(std::cin, input);
		if (input == "EXIT")
		{
			_running = false;
			closesocket(_serverSocket);
		}
	}
}