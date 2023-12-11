#include <DB.h>

DB::DB(const std::string &host, const std::string &user, const std::string &password)
        : _host(host), _user(user), _password(password), _con(nullptr)
{
    openConnection();
}

DB::~DB()
{
    closeConnection();
}

void DB::openConnection()
{
    try
    {
        _driver = sql::mysql::get_mysql_driver_instance();
        _con = _driver->connect("tcp://" + _host + ":3306", _user, _password);
        if (_con->isValid())
        {
            std::cout << "Successfully connected to the database.\n" << std::endl;
        }
        else
        {
            std::cerr << "Error: Failed to establish a valid connection to the database." << std::endl;
        }
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "Database connection error: " << e.what() << std::endl;
    }
}

void DB::closeConnection()
{
    if (_con != nullptr)
    {
        delete _con;
    }
}

void DB::showWords()
{
    if (!_con || _con->isClosed())
    {
        std::cerr << "Error: Database connection is not open." << std::endl;
        return;
    }

    try
    {
        sql::Statement *stmt = _con->createStatement();

        std::string useQuery = "USE the_game;";
        stmt->execute(useQuery);

        std::string selectQuery = "SELECT * FROM words;";
        sql::ResultSet *res = stmt->executeQuery(selectQuery);

        sql::ResultSetMetaData *metaData = res->getMetaData();
        int numColumns = metaData->getColumnCount();

        for (int i = 1; i <= numColumns; ++i)
        {
            std::cout << metaData->getColumnName(i) << "\t";
        }
        std::cout << std::endl;

        while (res->next())
        {
            for (int i = 1; i <= numColumns; ++i)
            {
                std::cout << res->getString(i) << "\t";
            }
            std::cout << std::endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "Database query error: " << e.what() << std::endl;
    }
}

bool DB::isConnected() const
{
    return (_con != nullptr && _con->isValid() && !_con->isClosed());
}

