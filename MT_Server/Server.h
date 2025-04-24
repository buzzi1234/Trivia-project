#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <exception>
#include <fstream>
#include <algorithm>
#include <map>
#include "LoginRequestHandler.h"

class Server
{
public:
	Server();
	~Server();
	void run(int port);

private:
	void acceptClients();
	void handleClient(SOCKET clientSocket);
	void consoleListener();

	SOCKET _serverSocket;
	std::map<SOCKET, LoginRequestHandler*> _clients;
	std::mutex _clientsMutex;
	std::atomic<bool> _running;
};

