#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <iomanip>

class DB 
{
public:
    DB(const std::string &host, const std::string &user, const std::string &password);
    ~DB();

    void showDBs();
    void showWords() const;
    void addWord(const std::string &name, const std::string &translation, const std::string &category, const std::string &level);
    void removeWord(const std::string &name);
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