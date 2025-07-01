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
    std::string sqlQuery = "SELECT USERNAME FROM USERS WHERE USERNAME = '" + userName + "';";	// Get specific user name.
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

std::map<std::string, int> SqliteDatabase::getHighScore()
{
    std::string query = "SELECT user_name, score FROM statistics ORDER BY score DESC LIMIT 3;";
    HightScoreSqlStatement(query);

    for (const auto& state : _statesList)
    {
        std::string userName = state.getName();
        int score = std::stoi(state.getDescription()); // Assuming the score is stored in the description field.
        _highScoreMap[userName] = score; // Add to the high score map.
    }
    return _highScoreMap;
}

float SqliteDatabase::getPllayerAverageAnswerTime(const std::string& username)
{
    std::string query = "SELECT average_answer_time FROM statistics WHERE user_name = '" + username + "';";
    AverageAnswerTimeSqlStatement(query);

    if (_statesList.empty())
    {
        throw std::runtime_error("No statistics found for the user: " + username);
    }
    return std::stof(_statesList.front().getDescription());
}

int SqliteDatabase::getNumOfCorrectAnswers(const std::string& username)
{
    std::string query = "SELECT num_of_correct_answers FROM statistics WHERE user_name = '" + username + "';";
    NumOfCurrectAnswersSqlStatement(query);
    if (_statesList.empty())
    {
        throw std::runtime_error("No statistics found for the user: " + username);
    }
    return std::stoi(_statesList.front().getDescription());
}

int SqliteDatabase::getNumOfTotalAnswers(const std::string& username)
{
    std::string query = "SELECT num_of_total_answers FROM statistics WHERE user_name = '" + username + "';";
    NumOfTotalAnswersSqlStatement(query);
    if (_statesList.empty())
    {
        throw std::runtime_error("No statistics found for the user: " + username);
    }
    return std::stoi(_statesList.front().getDescription());
}

int SqliteDatabase::getNumOfPlayerGames(const std::string& username)
{
    std::string query = "SELECT num_of_player_games FROM statistics WHERE user_name = '" + username + "';";
    NumOfPlayerGamesSqlStatement(query);
    if (_statesList.empty())
    {
        throw std::runtime_error("No statistics found for the user: " + username);
    }
    return std::stoi(_statesList.front().getDescription());
}

int SqliteDatabase::getPlayerScore(const std::string& username)
{
    std::string query = "SELECT player_score FROM statistics WHERE user_name = '" + username + "';";
    PlayerScoreSqlStatement(query);
    if (_statesList.empty())
    {
        throw std::runtime_error("No statistics found for the user: " + username);
    }
    return std::stoi(_statesList.front().getDescription());
}


//צריך לפתוח כלביק של סתטוס ולהשתמש במחלקה ובליסט שעשיתי ולעשות את השאילתות

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
    std::string questionText;
    std::vector<std::string> answers(4);

    for (int i = 0; i < argc; i++)
    {
        if (argv[i])
        {
			std::string col = azColName[i];
            std::string val = argv[i];

            if (col == "QUESTION") questionText = val;
            else if (col == "ANSWER_1") answers[0] = val;
            else if (col == "ANSWER_2") answers[1] = val;
            else if (col == "ANSWER_3") answers[2] = val;
            else if (col == "CORRECT_ANSWER") answers[3] = val;
        }
    }

    // Create a User object and add it to the list
    // , first_question, second_question, third_question, fourth_right_question
        // to do vector

    Question question(questionText, answers);
    auto* questionList = static_cast<std::list<Question>*>(data);
    questionList->push_back(question);

    return 0;
}

int statesCallback(void* data, int argc, char** argv, char** azColName)
{
    int id = 0;
    std::string name = "\0";
    std::string description = "\0";

    for (int i = 0; i < argc; i++)
    {
        if (argv[i] != nullptr)
        {
            std::string columnName = std::string(azColName[i]);
            std::string value = argv[i];
            if (columnName == "ID")
            {
                id = std::stoi(value);
            }
            if (columnName == "NAME")
            {
                name = value;
            }
            if (columnName == "DESCRIPTION")
            {
                description = value;
            }
        }
    }

    States state(id, name, description);
    auto* statesList = static_cast<std::list<States>*>(data);
    statesList->push_back(state);

    return 0;
}

int highScoreCallback(void* data, int argc, char** argv, char** azColName)
{
    int id = 0; // You can leave this 0 or remove if unused
    std::string name = "";
    std::string description = "";

    for (int i = 0; i < argc; i++)
    {
        if (argv[i] != nullptr)
        {
            std::string columnName = std::string(azColName[i]);
            std::string value = argv[i];

            if (columnName == "user_name") // Match your query
            {
                name = value;
            }
            else if (columnName == "score") // Match your query
            {
                description = value; // store score as string
            }
        }
    }

    States state(id, name, description);
    auto* statesList = static_cast<std::list<States>*>(data);
    statesList->push_back(state);

    return 0;
}

int AverageAnswerTimeCallback(void* data, int argc, char** argv, char** azColName)
{
    int id = 0; // You can leave this 0 or remove if unused
    std::string name = "";
    std::string description = "";

    for (int i = 0; i < argc; i++)
    {
        if (argv[i] != nullptr)
        {
            std::string columnName = std::string(azColName[i]);
            std::string value = argv[i];

            if (columnName == "user_name") // Match your query
            {
                name = value;
            }
            else if (columnName == "average_answer_time") // Match your query
            {
                description = value; // store score as string
            }
        }
    }

    States state(id, name, description);
    auto* statesList = static_cast<std::list<States>*>(data);
    statesList->push_back(state);

    return 0;
}

int NumOfCorrectAnswersCallback(void* data, int argc, char** argv, char** azColName)
{
    int id = 0; // You can leave this 0 or remove if unused
    std::string name = "";
    std::string description = "";

    for (int i = 0; i < argc; i++)
    {
        if (argv[i] != nullptr)
        {
            std::string columnName = std::string(azColName[i]);
            std::string value = argv[i];

            if (columnName == "user_name") // Match your query
            {
                name = value;
            }
            else if (columnName == "num_of_correct_answers") // Match your query
            {
                description = value; // store score as string
            }
        }
    }

    States state(id, name, description);
    auto* statesList = static_cast<std::list<States>*>(data);
    statesList->push_back(state);

    return 0;
}

int NumOfTotalAnswersCallback(void* data, int argc, char** argv, char** azColName)
{
    int id = 0; // You can leave this 0 or remove if unused
    std::string name = "";
    std::string description = "";

    for (int i = 0; i < argc; i++)
    {
        if (argv[i] != nullptr)
        {
            std::string columnName = std::string(azColName[i]);
            std::string value = argv[i];

            if (columnName == "user_name") // Match your query
            {
                name = value;
            }
            else if (columnName == "num_of_total_answers") // Match your query
            {
                description = value; // store score as string
            }
        }
    }

    States state(id, name, description);
    auto* statesList = static_cast<std::list<States>*>(data);
    statesList->push_back(state);

    return 0;
}

int NumOfPlayerGamesCallback(void* data, int argc, char** argv, char** azColName)
{
    int id = 0; // You can leave this 0 or remove if unused
    std::string name = "";
    std::string description = "";

    for (int i = 0; i < argc; i++)
    {
        if (argv[i] != nullptr)
        {
            std::string columnName = std::string(azColName[i]);
            std::string value = argv[i];

            if (columnName == "user_name") // Match your query
            {
                name = value;
            }
            else if (columnName == "num_of_player_games") // Match your query
            {
                description = value; // store score as string
            }
        }
    }

    States state(id, name, description);
    auto* statesList = static_cast<std::list<States>*>(data);
    statesList->push_back(state);

    return 0;
}

int PlayerScoreCallback(void* data, int argc, char** argv, char** azColName)
{
    int id = 0; // You can leave this 0 or remove if unused
    std::string name = "";
    std::string description = "";

    for (int i = 0; i < argc; i++)
    {
        if (argv[i] != nullptr)
        {
            std::string columnName = std::string(azColName[i]);
            std::string value = argv[i];

            if (columnName == "user_name") // Match your query
            {
                name = value;
            }
            else if (columnName == "player_score") // Match your query
            {
                description = value; // store score as string
            }
        }
    }

    States state(id, name, description);
    auto* statesList = static_cast<std::list<States>*>(data);
    statesList->push_back(state);

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
void SqliteDatabase::HightScoreSqlStatement(std::string sqlQuery)
{
    _statesList.clear();

    const char* sqlStatement = sqlQuery.c_str();
    char* errMessage;
    int res;

    res = sqlite3_exec(_db, sqlStatement, highScoreCallback, &_statesList, &errMessage);

    if (res != SQLITE_OK)
    {
        std::cout << "HightScoreSqlStatement: " << errMessage << std::endl;
        sqlite3_free(errMessage);
    }
}

void SqliteDatabase::AverageAnswerTimeSqlStatement(std::string sqlQuery)
{
    _statesList.clear();

    const char* sqlStatement = sqlQuery.c_str();
    char* errMessage;
    int res;

    res = sqlite3_exec(_db, sqlStatement, AverageAnswerTimeCallback, &_statesList, &errMessage);

    if (res != SQLITE_OK)
    {
        std::cout << "AverageAnswerTimeSqlStatement: " << errMessage << std::endl;
        sqlite3_free(errMessage);
    }
}

void SqliteDatabase::NumOfCurrectAnswersSqlStatement(std::string sqlQuery)
{
    _statesList.clear();

    const char* sqlStatement = sqlQuery.c_str();
    char* errMessage;
    int res;

    res = sqlite3_exec(_db, sqlStatement, NumOfCorrectAnswersCallback, &_statesList, &errMessage);

    if (res != SQLITE_OK)
    {
        std::cout << "NumOfCurrectAnswersSqlStatement: " << errMessage << std::endl;
        sqlite3_free(errMessage);
    }
}

void SqliteDatabase::NumOfTotalAnswersSqlStatement(std::string sqlQuery)
{
    _statesList.clear();

    const char* sqlStatement = sqlQuery.c_str();
    char* errMessage;
    int res;

    res = sqlite3_exec(_db, sqlStatement, NumOfTotalAnswersCallback, &_statesList, &errMessage);

    if (res != SQLITE_OK)
    {
        std::cout << "NumOfTotalAnswersSqlStatement: " << errMessage << std::endl;
        sqlite3_free(errMessage);
    }
}

void SqliteDatabase::NumOfPlayerGamesSqlStatement(std::string sqlQuery)
{
    _statesList.clear();

    const char* sqlStatement = sqlQuery.c_str();
    char* errMessage;
    int res;

    res = sqlite3_exec(_db, sqlStatement, NumOfPlayerGamesCallback, &_statesList, &errMessage);

    if (res != SQLITE_OK)
    {
        std::cout << "NumOfPlayerGamesSqlStatement: " << errMessage << std::endl;
        sqlite3_free(errMessage);
    }
}

void SqliteDatabase::PlayerScoreSqlStatement(std::string sqlQuery)
{
    _statesList.clear();

    const char* sqlStatement = sqlQuery.c_str();
    char* errMessage;
    int res;

    res = sqlite3_exec(_db, sqlStatement, PlayerScoreCallback, &_statesList, &errMessage);

    if (res != SQLITE_OK)
    {
        std::cout << "PlayerScoreSqlStatement: " << errMessage << std::endl;
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

void SqliteDatabase::statesSqlStatement(std::string sqlQuery)
{
    _statesList.clear();

    const char* sqlStatement = sqlQuery.c_str();
    char* errMessage;
    int res;

    res = sqlite3_exec(_db, sqlStatement, statesCallback, &_statesList, &errMessage);
    if (res != SQLITE_OK)
    {
        std::cout << "States SqlStatement: " << errMessage << std::endl;
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
