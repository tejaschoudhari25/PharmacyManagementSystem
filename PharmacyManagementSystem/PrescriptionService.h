#pragma once

#include "DBConnection.h"

class PrescriptionService
{
public:
    void savePrescription(DBConnection& db);
    void viewPrescriptions(DBConnection& db);
};