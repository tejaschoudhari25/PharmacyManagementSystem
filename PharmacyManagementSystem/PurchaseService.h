#pragma once

#include "DBConnection.h"

class PurchaseService
{
public:
    void purchaseStock(DBConnection& db);
};