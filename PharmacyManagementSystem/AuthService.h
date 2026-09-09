#pragma once

#include "DBConnection.h"
#include <string>

using namespace std;

class AuthService
{
public:
    string login(DBConnection& db);
};