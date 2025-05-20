#include "Server.h"
#include <stdexcept>
#include <string>

#pragma comment(lib, "ws2_32.lib")
/// <summary>
/// creates a socket and verifies that it was created successfully
/// </summary>
Server::Server(RequestHandlerFactory handlerFactory, IDatabase* database) : _running(true), _handlerFactory(handlerFactory), _database(database), _communicator(_handlerFactory)
{
}
/// <summary>
/// closes the main socket and all client connections
/// </summary>
Server::~Server()
{
	_running = false;
	_communicator.stop();
	_consoleThread.join();
}
/// <summary>
/// binds to a listening port and starts input and client acceptance processes
/// </summary>
/// <param name="port"></param>
void Server::run(int port)
{
	std::cout << "Starting server on port " << port << std::endl;

	_consoleThread = std::thread(&Server::consoleListener, this);
	try
	{
		_communicator.bindAndListen(port);
		_communicator.startHandleRequests();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Server Error: " << e.what() << std::endl;
	}
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
			std::cout << "Shutting down server " << std::endl;
			_running = false;
			_communicator.stop();
			break;
		}
	}
}