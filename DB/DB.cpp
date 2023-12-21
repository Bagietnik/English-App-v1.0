#include <DB.h>

DB::DB(const std::string &host, const std::string &user, const std::string &password)
        : _host(host), _user(user), _password(password), _con(nullptr), _driver(_driver = sql::mysql::get_mysql_driver_instance())
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

void DB::showWords() const
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

void DB::addWord(const std::string &name, const std::string &translation, const std::string &category, const std::string &level)
{
    if (!_con || _con->isClosed())
    {
        std::cerr << "Error: Database connection is not open." << std::endl;
        return;
    }

    try
    {
        _con->setSchema("the_game");

        sql::PreparedStatement *prepStmt;
        prepStmt = _con->prepareStatement("INSERT INTO words (word, translation, category, level) VALUES (?, ?, ?, ?)");

        prepStmt->setString(1, name);
        prepStmt->setString(2, translation);
        prepStmt->setString(3, category);
        prepStmt->setString(4, level);

        prepStmt->executeUpdate();

        system("clear");
        std::cout << "Word added successfully!" << std::endl;

        delete prepStmt;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "Database query error: " << e.what() << std::endl;
    }
}

void DB::removeWord(const std::string &name)
{
    if (!_con || _con->isClosed())
    {
        std::cerr << "Error: Database connection is not open." << std::endl;
        return;
    }

    try
    {
        _con->setSchema("the_game");

        sql::PreparedStatement *checkStmt;
        checkStmt = _con->prepareStatement("SELECT COUNT(*) FROM words WHERE word = ?");
        checkStmt->setString(1, name);
        sql::ResultSet *result = checkStmt->executeQuery();

        int rowCount = 0;
        if (result->next())
        {
            rowCount = result->getInt(1);
        }

        delete checkStmt;

        if (rowCount == 0)
        {
            system("clear");
            std::cerr << "Error: Word '" << name << "' does not exist in the database." << std::endl;
            return;
        }

        sql::PreparedStatement *prepStmt;
        prepStmt = _con->prepareStatement("DELETE FROM words WHERE word = ?");
        prepStmt->setString(1, name);
        prepStmt->executeUpdate();

        system("clear");
        std::cout << "Word removed successfully!" << std::endl;

        delete prepStmt;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "Database query error: " << e.what() << std::endl;
    }
}
