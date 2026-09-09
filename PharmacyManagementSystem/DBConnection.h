#pragma once

#include <iostream>
#include <libpq-fe.h>

using namespace std;

class DBConnection
{
private:
    PGconn* conn;

public:
    DBConnection();

    bool connect();

    void disconnect();

    PGconn* getConnection();
};