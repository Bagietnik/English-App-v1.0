#pragma once

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <iomanip>

class DB 
{
public:
    DB(const std::string &host, const std::string &user, const std::string &password);
    ~DB();

    void showDBs();
    void showWords();
    void addWord();
    void removeWord();
    bool isConnected() const;

private:
    std::string _host;
    std::string _user;
    std::string _password;
    sql::mysql::MySQL_Driver *_driver;
    sql::Connection *_con;

    void openConnection();
    void closeConnection();
};