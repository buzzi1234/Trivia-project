#include "LoggedUser.h"

//constructor
LoggedUser::LoggedUser(std::string userName)
{
    this->m_username = userName;
}

/// <summary>
/// The funcion return the user name
/// </summary>
/// <returns> user name </returns>
std::string LoggedUser::getUserName() const
{
    return this->m_username;
}
