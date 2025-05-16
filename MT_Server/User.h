#pragma once
#include "IDatabase.h"
#include "sqlite3.h"

#include <iostream>
#include <Windows.h>
#include <io.h>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <list>


class User
{
public:
	User(int id, std::string name, std::string password, std::string email);

	int getId() const;
	std::string getName() const;
	std::string getPassword() const;
	std::string getEmail() const;

private:
	int _id;

	std::string _name;
	std::string _password;
	std::string _email;
};