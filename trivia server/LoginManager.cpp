#include "LoginManager.h"
#include <iostream>

//constructor
LoginManager::LoginManager(IDatabase* sqlDS)
{
    this->m_database = sqlDS;
    this->m_database->open();
}

//destructor
LoginManager::~LoginManager()
{
    for (auto user : m_loggedUsers)
        delete user;
    this->m_loggedUsers.clear();
    this->m_database->close();
}


/// <summary>
/// The func check if the user exist if not he sign up
/// </summary>
/// <param name="username"> The username </param>
/// <param name="password"> The user password </param>
/// <param name="email"> The user email </param>
/// <returns> Signup status if complete if not than error status </returns>
int LoginManager::signup(std::string username, std::string password, std::string email)
{
    if (username.empty() || username.length() < 3 || username.length() > 20)
    {
        std::cout << "Invalid username length" << std::endl;
        return ERROR_CODE;
    }

    for (char c : username)
    {
        if (!isalnum(c) && c != '_')
        {
            std::cout << "Invalid character in username: " << c << std::endl;
            return ERROR_CODE;
        }
    }

    if (!this->m_database->doesUserExist(username))
    {
        this->m_database->addNewUser(username, password, email);
        this->m_loggedUsers.push_back(new LoggedUser(username));
        return SIGN_CODE;
    }
    else
    {
        std::cout << "Signup failed: user already exists" << std::endl;
    }
    return ERROR_CODE;
}

/// <summary>
/// The func check if the user exist and than check if the user is logged if not than it login in
/// </summary>
/// <param name="username"> The username </param>
/// <param name="password"> The user password </param>
/// <returns> Login status if complete if not than error status </returns>
int LoginManager::login(std::string username, std::string password)
{
    if (this->m_database->doesUserExist(username) && this->m_database->doesPasswordMatch(username, password))
    {
        for (auto it : this->m_loggedUsers)
        {
            if (it->getUserName() == username)
            {
                std::cout << "fls" << std::endl;
                return ERROR_CODE;
            }
        }
        
        this->m_loggedUsers.push_back(new LoggedUser(username));
        return LOG_CODE;
    }
    return ERROR_CODE;
}


/// <summary>
/// The func check if user exist and is logged if he do than the function logged out
/// </summary>
/// <param name="username"> The username </param>
void LoginManager::logout(std::string username)
{
    if (this->m_database->doesUserExist(username))
    {
        for (int i = 0; i < this->m_loggedUsers.size(); i++)
        {
            if (this->m_loggedUsers[i]->getUserName() == username)
            {
                this->m_loggedUsers.erase(this->m_loggedUsers.begin() + i);
            }
        }
    }
    else
    {
        std::cout << "User Does not exist or does not login" << std::endl;
    }

}
