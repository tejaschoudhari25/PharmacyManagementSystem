#include "DBConnection.h"

DBConnection::DBConnection()
{
    conn = nullptr;
}

bool DBConnection::connect()
{
    conn = PQconnectdb(
        "host=localhost "
        "port=5432 "
        "dbname=pharmacy_db "
        "user=postgres "
        "password=HclNoida@2025"
    );

    if (PQstatus(conn) != CONNECTION_OK)
    {
        cout << "Connection Failed!" << endl;
        cout << PQerrorMessage(conn) << endl;

        return false;
    }

    cout << "Database Connected Successfully!" << endl;

    return true;
}

void DBConnection::disconnect()
{
    if (conn != nullptr)
    {
        PQfinish(conn);
        cout << "Database Connection Closed." << endl;
    }
}

PGconn* DBConnection::getConnection()
{
    return conn;
}