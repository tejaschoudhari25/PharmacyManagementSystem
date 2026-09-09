#include "PurchaseService.h"
#include <iostream>
#include <string>

using namespace std;

void PurchaseService::purchaseStock(DBConnection& db)
{
    int medicineId;
    int quantity;
    double costPrice;

    cout << "\nMedicine ID : ";
    cin >> medicineId;

    cout << "Quantity Purchased : ";
    cin >> quantity;

    cout << "Cost Price : ";
    cin >> costPrice;

    string insertQuery =
        "INSERT INTO purchases "
        "(medicine_id,quantity,cost_price) VALUES(" +
        to_string(medicineId) + "," +
        to_string(quantity) + "," +
        to_string(costPrice) + ")";

    PQexec(db.getConnection(), insertQuery.c_str());

    string updateQuery =
        "UPDATE medicines "
        "SET quantity = quantity + " +
        to_string(quantity) +
        " WHERE medicine_id = " +
        to_string(medicineId);

    PGresult* result =
        PQexec(db.getConnection(), updateQuery.c_str());

    if (PQresultStatus(result) == PGRES_COMMAND_OK)
    {
        cout << "\nStock Updated Successfully.\n";
    }

    PQclear(result);
}