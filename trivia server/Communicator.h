#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include <thread>
#include <mutex>
#include <vector>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"

class Communicator
{
public:
	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();

	void bindAndListen(int port) const;
	void startHandleRequests();
	void stop();
	RequestHandlerFactory& _handlerFactory;
	std::optional<SOCKET> getUserSocket(const std::string& username) const;
private:
	void handleNewClient(SOCKET clientSocket);

	SOCKET _serverSocket;
	std::atomic<bool> _running;
	std::map<SOCKET, IRequestHandler*> _clients;
	mutable std::mutex _clientsMutex;
	std::map<std::string, SOCKET> _userToSocket;

};

