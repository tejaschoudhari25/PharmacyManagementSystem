#include "ExpiryService.h"
#include <iostream>

using namespace std;

void ExpiryService::showExpiredMedicines(DBConnection& db)
{
    string query =
        "SELECT medicine_id,name,expiry_date "
        "FROM medicines "
        "WHERE expiry_date < CURRENT_DATE";

    PGresult* result =
        PQexec(db.getConnection(), query.c_str());

    int rows = PQntuples(result);

    cout << "\n===== EXPIRED MEDICINES =====\n";

    if (rows == 0)
    {
        cout << "No Expired Medicines Found.\n";
    }

    for (int i = 0; i < rows; i++)
    {
        cout << "\nID : "
            << PQgetvalue(result, i, 0);

        cout << "\nName : "
            << PQgetvalue(result, i, 1);

        cout << "\nExpiry Date : "
            << PQgetvalue(result, i, 2);

        cout << "\n----------------------\n";
    }

    PQclear(result);
}

void ExpiryService::showNearExpiryMedicines(DBConnection& db)
{
    string query =
        "SELECT medicine_id,name,expiry_date "
        "FROM medicines "
        "WHERE expiry_date BETWEEN CURRENT_DATE "
        "AND CURRENT_DATE + INTERVAL '30 days'";

    PGresult* result =
        PQexec(db.getConnection(), query.c_str());

    int rows = PQntuples(result);

    cout << "\n===== NEAR EXPIRY MEDICINES =====\n";

    if (rows == 0)
    {
        cout << "No Near Expiry Medicines Found.\n";
    }

    for (int i = 0; i < rows; i++)
    {
        cout << "\nID : "
            << PQgetvalue(result, i, 0);

        cout << "\nName : "
            << PQgetvalue(result, i, 1);

        cout << "\nExpiry Date : "
            << PQgetvalue(result, i, 2);

        cout << "\n----------------------\n";
    }

    PQclear(result);
}