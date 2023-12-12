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

        std::cout << "\n*******************************************************************************************" << '\n';

    for (int i = 1; i <= numColumns; ++i)
    {
        std::cout << std::setw(15) << std::left << metaData->getColumnName(i);
    }
    std::cout << '\n';
    std::cout << std::endl;

    while (res->next())
    {
        for (int i = 1; i <= numColumns; ++i)
        {
            std::cout << std::setw(15) << std::left << res->getString(i);
        }
        std::cout << std::endl;
    }

    std::cout << "\n*******************************************************************************************" << '\n';
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

void DB::addWord()
{
    if (!_con || _con->isClosed())
    {
        std::cerr << "Error: Database connection is not open." << std::endl;
        return;
    }else{
        ;
    }
}

void DB::removeWord()
{
    ;
}