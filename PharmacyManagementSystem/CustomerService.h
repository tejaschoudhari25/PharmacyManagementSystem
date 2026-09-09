#pragma once

#include "DBConnection.h"

class CustomerService
{
public:
    void addCustomer(DBConnection& db);
    void viewCustomers(DBConnection& db);
    void updateCustomer(DBConnection& db);
};