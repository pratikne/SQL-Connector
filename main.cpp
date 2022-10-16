#include "common_header.h"
#include "my_sql_header.h"
#include "connection_details.h"
using namespace std;

short ptr;

int main(int argc, char *argv[])
{
    if (argc >= 2)
        ptr = stoi(argv[1]);
    else
        ptr = 0;

    ios::sync_with_stdio(false);

    // defining connection variables
    string url = EXAMPLE_HOST;
    const string user = EXAMPLE_USER;
    const string password = EXAMPLE_PASS;
    const string database = EXAMPLE_DB;

    Log1 << "connection: [" << url << "]";
    Log1 << "user: [" << user << "]";
    Log1 << "password: [" << password << "]";
    Log1 << "database: [" << database << "]";

    string tempSqlString;
    stringstream sql;
    stringstream msg;

    try
    {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect(url, user, password);
        /* Connect to the MySQL test database */
        con->setSchema(database);

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT 'Hello World!' AS _message"); // replace with your statement
        while (res->next())
        {
            cout << "\t... MySQL replies: ";
            /* Access column data by alias or column name */
            cout << res->getString("_message") << endl;
            cout << "\t... MySQL says it again: ";
            /* Access column fata by numeric offset, 1 is the first column */
            cout << res->getString(1) << endl;
        }
        delete res;
        delete stmt;
        delete con;
    }
    catch (sql::SQLException &e)
    {
        Log0 << "SQL Exception: [" << e.getErrorCode() << "] " << e.what();
        return EXIT_FAILURE;
    }
    catch (std::runtime_error &e)
    {
        Log0 << "Run tme error exception: [" << e.what();
        return EXIT_FAILURE;
    }

    Log0 << "Code completed successfully exiting..."
         << "\n";
    return EXIT_SUCCESS;
}
