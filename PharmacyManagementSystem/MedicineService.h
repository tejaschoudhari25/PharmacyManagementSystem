#pragma once

#include "DBConnection.h"

class MedicineService
{
public:
    void addMedicine(DBConnection& db);
    void viewMedicines(DBConnection& db);
    void updateMedicine(DBConnection& db);
    void deleteMedicine(DBConnection& db);
    void searchMedicine(DBConnection& db);
};