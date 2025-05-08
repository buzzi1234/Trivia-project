#include "Server.h"
#include <stdexcept>
#include <string>

#pragma comment(lib, "ws2_32.lib")
/// <summary>
/// creates a socket and verifies that it was created successfully
/// </summary>
Server::Server() : _running(true)
{
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //creates TCP
	if (_serverSocket == INVALID_SOCKET)
	{
		throw std::runtime_error("Failed to create socet");
	}
}
/// <summary>
/// closes the main socket and all client connections
/// </summary>
Server::~Server()
{
	closesocket(_serverSocket);
	for (auto& pair : _clients)
	{
		closesocket(pair.first);
		delete pair.second;
	}
}
/// <summary>
/// binds to a listening port and starts input and client acceptance processes
/// </summary>
/// <param name="port"></param>
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
/// <summary>
/// listens for new clients and runs a separate thread for each one
/// </summary>
void Server::acceptClients()
{
	while (_running)
	{
		SOCKET clientSocket = accept(_serverSocket, nullptr, nullptr);
		if (clientSocket == INVALID_SOCKET)
		{
			if (!_running) //if the server closed
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
/// <summary>
/// handles a single client: sends Hello and prints answer
/// </summary>
/// <param name="clientSocket"></param>
void Server::handleClient(SOCKET clientSocket) // Sending Hello to the client
{
	std::string hello = "Hello";
	send(clientSocket, hello.c_str(), hello.size(), 0);

	char buffer[6] = { 0 }; // buffer for receiving up to 5 char
	int bytesReceived = recv(clientSocket, buffer, 5, 0); //receiving a message from the client
	if (bytesReceived > 0)
	{
		std::cout << "Cliet said: " << std::string(buffer, bytesReceived) << std::endl;
	}

	closesocket(clientSocket);

	std::lock_guard<std::mutex> lock(_clientsMutex);
	delete _clients[clientSocket];
	_clients.erase(clientSocket);
}
/// <summary>
/// listens for commands to stops the server when "EXIT" is entered
/// </summary>
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