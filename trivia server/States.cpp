#include "States.h"

States::States(int id, std::string name, std::string description) :_id(id), _name(name), _description(description)
{
}

int States::getId() const
{
	return _id;
}

std::string States::getName() const
{
	return _name;
}

std::string States::getDescription() const
{
	return _description;
}
