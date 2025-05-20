#include "SqliteDatabase.h"

#define DB_NAME "MyDB.sqlite"

SqliteDatabase::~SqliteDatabase()
{
    delete _db;
    _questionList.clear();
    _usersList.clear();
}

bool SqliteDatabase::open()
{
    std::string dbFileName = DB_NAME;

    int file_exist = _access(dbFileName.c_str(), 0);
    int res = sqlite3_open(dbFileName.c_str(), &_db);

    if (res != SQLITE_OK)
    {
        std::cout << "Failed to open DB" << std::endl;
        close();
        return false;
    }

    if (file_exist != 0)
    {
        initDB();
    }

    return true;
}

// CHECK
bool SqliteDatabase::close()
{
    // TO DO.
    sqlite3_close(_db);
    _db = nullptr;

    return true;
}

// CHECK
int SqliteDatabase::doesUserExist(std::string userName)
{
    std::string sqlQuery = "SELECT NAME FROM USERS WHERE USERNAME = '" + userName + "';";	// Get specific user name.
    UserSqlStatement(sqlQuery);		// Call the sqlStatement() in order to send the query.

    if (_usersList.empty())	// Check if the users list is empty.
    {
        return false;	// Return false.
    }

    return true;	// Return true.
}

// CHECK
int SqliteDatabase::doesPasswordMatch(std::string userName, std::string password)
{
    std::string sqlQuery = "SELECT PASSWORD FROM USERS WHERE USERNAME = '" + userName + "' AND PASSWORD = '" + password + "';";	// Get specific password by user name.
    UserSqlStatement(sqlQuery);		// Call the sqlStatement() in order to send the query.

    if (_usersList.empty())	// Check if the users list is empty.
    {
        return false;	// Return false.
    }

    return true;	// Return true.
}

// CHECK
int SqliteDatabase::addNewUser(std::string userName, std::string password, std::string email)
{
    std::string sqlQuery = "\0";

    // SQL QUERY that create new user in the DB.
    sqlQuery = "INSERT INTO USERS(USERNAME, PASSWORD, EMAIL) VALUES('" + userName + "', '" + password + "', '" + email  + "');";
    sqlStatement(sqlQuery);		// Call the sqlStatement() in order to send the query.

    return 90;
}

std::list<Question> SqliteDatabase::getQuestions(int numberOfQuestions)
{
    std::string sqlQuery = "SELECT * FROM QUESTION_BANK LIMIT '" + std::to_string(numberOfQuestions) + "' ;";
    std::cout << sqlQuery << std::endl;
    questionSqlStatement(sqlQuery);

    return _questionList;
}


// Private functions.

// Callback function to extract user data (ID and name)
int usercallback(void* data, int argc, char** argv, char** azColName)
{
    std::string userName = "\0";
    std::string email = "\0";
    std::string password = "\0";
    int id = 0;

    // Iterate over each column and extract the data
    for (int i = 0; i < argc; i++)
    {
        if (argv[i] != nullptr)
        {
            std::string columnName = std::string(azColName[i]);
            std::string value = argv[i];

            if (columnName == "ID")
            {
                id = stoi(value);
            }

            if (columnName == "USERNAME")
            {
                userName = value;
            }

            if (columnName == "PASSWORD")
            {
                password = value;
            }

            if (columnName == "EMAIL")
            {
                email = value;
            }    
        }
    }

    // Create a User object and add it to the list
    User user(id, userName, password, email);
    auto* usersList = static_cast<std::list<User>*>(data);
    usersList->push_back(user);

    return 0;
}

int questioncallback(void* data, int argc, char** argv, char** azColName)
{
    std::string the_question = "\0";

    std::string first_answer = "\0";
    std::string second_answer = "\0";
    std::string third_answer = "\0";
    std::string fourth_right_answer = "\0";

    // Iterate over each column and extract the data
    for (int i = 0; i < argc; i++)
    {
        if (argv[i] != nullptr)
        {
            std::string columnName = std::string(azColName[i]);
            std::string value = argv[i];

            if (columnName == "QUESTION")
            {
                the_question = value;
            }

            if (columnName == "ANSWER_1")
            {
                first_answer = value;
            }

            if (columnName == "ANSWER_2")
            {
                second_answer = value;
            }

            if (columnName == "ANSWER_3")
            {
                third_answer = value;
            }

            if (columnName == "RIGHT_ANSWER_4")
            {
                fourth_right_answer = value;
            }
        }
    }

    // Create a User object and add it to the list
    // , first_question, second_question, third_question, fourth_right_question
        // to do vector
    std::vector<std::string> possibleAnswers;
    possibleAnswers.push_back(first_answer);
    possibleAnswers.push_back(second_answer);
    possibleAnswers.push_back(third_answer);
    possibleAnswers.push_back(fourth_right_answer);

    Question question(the_question, possibleAnswers);
    auto* questionList = static_cast<std::list<Question>*>(data);
    questionList->push_back(question);

    return 0;
}

// Executes a general SQL command without returning data
bool SqliteDatabase::sqlStatement(std::string sqlQuery)
{
    const char* sqlStatement = sqlQuery.c_str();

    char* errMessage = nullptr;
    int res = sqlite3_exec(_db, sqlStatement, nullptr, nullptr, &errMessage);
    if (res != SQLITE_OK)
    {
        std::cout << "Error Sending SQL Statement." << errMessage << std::endl;
        sqlite3_free(errMessage);
        return false;
    }

    return true;
}

void SqliteDatabase::UserSqlStatement(std::string sqlQuery)
{
    _usersList.clear();

    const char* sqlStatement = sqlQuery.c_str();
    char* errMessage;
    int res;

    res = sqlite3_exec(_db, sqlStatement, usercallback, &_usersList, &errMessage);

    if (res != SQLITE_OK)
    {
        std::cout << "UserSqlStatement: " << errMessage << std::endl;
        sqlite3_free(errMessage);
    }
}

void SqliteDatabase::questionSqlStatement(std::string sqlQuery)
{
    _questionList.clear();

    const char* sqlStatement = sqlQuery.c_str();
    char* errMessage;
    int res;

    res = sqlite3_exec(_db, sqlStatement, questioncallback, &_questionList, &errMessage);

    if (res != SQLITE_OK)
    {
        std::cout << "Question SqlStatement: " << errMessage << std::endl;
        sqlite3_free(errMessage);
    }
}

bool SqliteDatabase::initDB()
{
    std::string createSqlStatement = "CREATE TABLE IF NOT EXISTS USERS(ID INTEGER PRIMARY KEY AUTOINCREMENT, USERNAME TEXT NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL);";
    isTheTableCreated(createSqlStatement, "USERS");

    // Create another table:
    std::string createSqlStatement_2 = "CREATE TABLE IF NOT EXISTS QUESTION_BANK(ID INTEGER PRIMARY KEY AUTOINCREMENT, QUESTION TEXT NOT NULL, ANSWER_1 TEXT NOT NULL, ANSWER_2 TEXT NOT NULL, ANSWER_3 TEXT NOT NULL,  RIGHT_ANSWER_4 TEXT NOT NULL);";
    isTheTableCreated(createSqlStatement_2, "QUESTION_BANK");

    return true;
}

bool SqliteDatabase::isTheTableCreated(std::string createSqlStatement, std::string tableName)
{
    if (!sqlStatement(createSqlStatement))
    {
        return false;
    }

    std::cout << "Table '" + tableName + "' created successfully." << std::endl;

    return true;
}
