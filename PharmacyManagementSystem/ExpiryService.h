#pragma once

#include "DBConnection.h"

class ExpiryService
{
public:
    void showExpiredMedicines(DBConnection& db);
    void showNearExpiryMedicines(DBConnection& db);
};