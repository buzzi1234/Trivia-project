#include "User.h"

User::User(int id, std::string name, std::string password, std::string email) :
	_id(id), _name(name), _password(password), _email(email)
{}

int User::getId() const
{
	return _id;
}

std::string User::getName() const
{
	return _name;
}

std::string User::getPassword() const
{
	return _password;
}

std::string User::getEmail() const
{
	return _email;
}
