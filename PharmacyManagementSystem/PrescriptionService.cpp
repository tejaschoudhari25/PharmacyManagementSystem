#include "PrescriptionService.h"
#include <iostream>
#include <string>

using namespace std;

void PrescriptionService::savePrescription(DBConnection& db)
{
    int customerId;
    string prescription;

    cout << "\nCustomer ID : ";
    cin >> customerId;

    cin.ignore();

    cout << "Prescription : ";
    getline(cin, prescription);

    string query =
        "INSERT INTO prescriptions(customer_id,prescription_text) "
        "VALUES(" +
        to_string(customerId) +
        ",'" +
        prescription +
        "')";

    PGresult* result =
        PQexec(db.getConnection(), query.c_str());

    if (PQresultStatus(result) == PGRES_COMMAND_OK)
    {
        cout << "\nPrescription Saved Successfully.\n";
    }

    PQclear(result);
}

void PrescriptionService::viewPrescriptions(DBConnection& db)
{
    string query =
        "SELECT prescription_id, customer_id, prescription_text "
        "FROM prescriptions "
        "ORDER BY prescription_id";

    PGresult* result =
        PQexec(db.getConnection(), query.c_str());

    int rows = PQntuples(result);

    cout << "\n===== PRESCRIPTIONS =====\n";

    for (int i = 0; i < rows; i++)
    {
        cout << "\nPrescription ID : "
            << PQgetvalue(result, i, 0);

        cout << "\nCustomer ID : "
            << PQgetvalue(result, i, 1);

        cout << "\nPrescription : "
            << PQgetvalue(result, i, 2);

        cout << "\n------------------------\n";
    }

    PQclear(result);
}