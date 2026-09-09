#include "SalesService.h"
#include <iostream>
#include <string>

using namespace std;

void SalesService::sellMedicine(DBConnection& db)
{
    string medicineQuery =
        "SELECT medicine_id,name,price,quantity,expiry_date "
        "FROM medicines "
        "ORDER BY medicine_id";

    PGresult* medicineResult =
        PQexec(db.getConnection(), medicineQuery.c_str());

    int rows = PQntuples(medicineResult);

    cout << "\n========== AVAILABLE MEDICINES ==========\n";

    for (int i = 0; i < rows; i++)
    {
        cout << "\nID : "
            << PQgetvalue(medicineResult, i, 0);

        cout << "\nName : "
            << PQgetvalue(medicineResult, i, 1);

        cout << "\nPrice : "
            << PQgetvalue(medicineResult, i, 2);

        cout << "\nStock : "
            << PQgetvalue(medicineResult, i, 3);

        cout << "\nExpiry Date : "
            << PQgetvalue(medicineResult, i, 4);

        cout << "\n-------------------------\n";
    }

    PQclear(medicineResult);

    int customerId;
    int medicineId;
    int quantity;

    cout << "\nCustomer ID : ";
    cin >> customerId;

    cout << "Medicine ID : ";
    cin >> medicineId;

    cout << "Quantity : ";
    cin >> quantity;

    string stockQuery =
        "SELECT name, price, quantity, expiry_date "
        "FROM medicines "
        "WHERE medicine_id=" +
        to_string(medicineId) +
        " AND expiry_date >= CURRENT_DATE";

    PGresult* stockResult =
        PQexec(db.getConnection(), stockQuery.c_str());

    if (PQntuples(stockResult) == 0)
    {
        cout << "\nMedicine Not Found Or Medicine Has Expired.\n";

        PQclear(stockResult);
        return;
    }

    string medicineName =
        PQgetvalue(stockResult, 0, 0);

    double price =
        stod(PQgetvalue(stockResult, 0, 1));

    int availableStock =
        stoi(PQgetvalue(stockResult, 0, 2));

    if (availableStock < quantity)
    {
        cout << "\nInsufficient Stock.\n";

        PQclear(stockResult);
        return;
    }

    PQclear(stockResult);

    double totalAmount = price * quantity;

    string saleQuery =
        "INSERT INTO sales(customer_id,total_amount)"
        " VALUES("
        + to_string(customerId)
        + ","
        + to_string(totalAmount)
        + ")";

    PQexec(db.getConnection(), saleQuery.c_str());

    PGresult* saleIdResult =
        PQexec(
            db.getConnection(),
            "SELECT MAX(sale_id) FROM sales"
        );

    int saleId =
        stoi(PQgetvalue(saleIdResult, 0, 0));

    PQclear(saleIdResult);

    string saleItemQuery =
        "INSERT INTO sale_items "
        "(sale_id,medicine_id,quantity,price)"
        " VALUES("
        + to_string(saleId)
        + ","
        + to_string(medicineId)
        + ","
        + to_string(quantity)
        + ","
        + to_string(price)
        + ")";

    PQexec(db.getConnection(), saleItemQuery.c_str());

    string updateStockQuery =
        "UPDATE medicines "
        "SET quantity = quantity - "
        + to_string(quantity)
        + " WHERE medicine_id = "
        + to_string(medicineId);

    PQexec(db.getConnection(), updateStockQuery.c_str());

    string customerQuery =
        "SELECT name FROM customers "
        "WHERE customer_id=" +
        to_string(customerId);

    PGresult* customerResult =
        PQexec(db.getConnection(), customerQuery.c_str());

    string customerName = "Unknown";

    if (PQntuples(customerResult) > 0)
    {
        customerName =
            PQgetvalue(customerResult, 0, 0);
    }

    PQclear(customerResult);

    cout << "\n";
    cout << "=========================================\n";
    cout << "          PHARMACY INVOICE\n";
    cout << "=========================================\n";
    cout << "Sale ID      : " << saleId << endl;
    cout << "Customer     : " << customerName << endl;
    cout << "Medicine     : " << medicineName << endl;
    cout << "Quantity     : " << quantity << endl;
    cout << "Unit Price   : " << price << endl;
    cout << "-----------------------------------------\n";
    cout << "Total Amount : " << totalAmount << endl;
    cout << "=========================================\n";

    cout << "\nSale Completed Successfully.\n";
}