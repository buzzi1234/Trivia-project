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

class States
{
public:
	// Constructor to initialize the state with an ID, name, and description
	States(int id, std::string name, std::string description);
	int getId() const;
	std::string getName() const;
	std::string getDescription() const;

private:
	int _id;  // Unique identifier for the state
	std::string _name;  // Name of the state
	std::string _description;  // Description of the state
};

