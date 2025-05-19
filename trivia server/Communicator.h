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
private:
	void handleNewClient(SOCKET clientSocket);

	SOCKET _serverSocket;
	std::atomic<bool> _running;
	std::map<SOCKET, IRequestHandler*> _clients;
	std::mutex _clientsMutex;
};

