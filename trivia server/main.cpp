#pragma comment (lib, "ws2_32.lib")

#include "Server.h"
#include <iostream>
#include <exception>
#include <WinSock2.h>
#include "SqliteDatabase.h"
#include "RequestHandlerFactory.h"
#include "LoginManager.h"


int main()
{
	try
	{
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);

		SqliteDatabase* db = new SqliteDatabase();

		LoginManager loginManager(db);
		RequestHandlerFactory factory(loginManager, db);

		Server server(factory, db);
		server.run(8826);

		delete db;
		WSACleanup();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0; //Exit the program
}