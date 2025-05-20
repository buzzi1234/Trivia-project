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
#include <atomic>
#include "Communicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"

class Server
{
public:
	Server(RequestHandlerFactory handlerFactory, IDatabase* database);
	~Server();
	void run(int port);
	IDatabase* _database;
	RequestHandlerFactory _handlerFactory;

private:
	void consoleListener();

	Communicator _communicator;
	std::thread _consoleThread;
	std::atomic<bool> _running;
};

