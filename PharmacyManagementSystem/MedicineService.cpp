#include "MedicineService.h"
#include <iostream>
#include <string>
#include<iomanip>

using namespace std;

void MedicineService::addMedicine(DBConnection& db)
{
    string name;
    string manufacturer;
    string category;
    string batchNo;
    string mfgDate;
    string expiryDate;
    double price;
    int quantity;

    cout << "\nMedicine Name : ";
    cin >> name;

    cout << "Manufacturer : ";
    cin >> manufacturer;

    cout << "Category : ";
    cin >> category;

    cout << "Batch Number : ";
    cin >> batchNo;

    cout << "Manufacturing Date (YYYY-MM-DD) : ";
    cin >> mfgDate;

    cout << "Expiry Date (YYYY-MM-DD) : ";
    cin >> expiryDate;

    cout << "Price : ";
    cin >> price;

    cout << "Quantity : ";
    cin >> quantity;

    string query =
        "INSERT INTO medicines "
        "(name,manufacturer,category,batch_no,mfg_date,expiry_date,price,quantity) "
        "VALUES ('" +
        name + "','" +
        manufacturer + "','" +
        category + "','" +
        batchNo + "','" +
        mfgDate + "','" +
        expiryDate + "'," +
        to_string(price) + "," +
        to_string(quantity) + ")";

    PGresult* result =
        PQexec(db.getConnection(), query.c_str());

    if (PQresultStatus(result) == PGRES_COMMAND_OK)
    {
        cout << "\nMedicine Added Successfully.\n";
    }
    else
    {
        cout << "\nError : "
            << PQerrorMessage(db.getConnection())
            << endl;
    }

    PQclear(result);
}

void MedicineService::viewMedicines(DBConnection& db)
{
    string query =
        "SELECT * FROM medicines "
        "WHERE is_active = TRUE "
        "ORDER BY medicine_id";

    PGresult* result =
        PQexec(db.getConnection(), query.c_str());

    int rows = PQntuples(result);

    cout << "\n";

    cout << setfill(' ');

    cout << left
        << setw(6) << "ID"
        << setw(20) << "NAME"
        << setw(20) << "MANUFACTURER"
        << setw(20) << "CATEGORY"
        << setw(12) << "PRICE"
        << setw(10) << "QTY"
        << setw(15) << "EXPIRY DATE"
        << endl;

    cout << string(101, '=') << endl;

    for (int i = 0; i < rows; i++)
    {
        cout << left
            << setw(6) << PQgetvalue(result, i, 0)
            << setw(20) << PQgetvalue(result, i, 1)
            << setw(20) << PQgetvalue(result, i, 2)
            << setw(20) << PQgetvalue(result, i, 3)
            << setw(12) << PQgetvalue(result, i, 7)
            << setw(8) << PQgetvalue(result, i, 8)
            << setw(15) << PQgetvalue(result, i, 6)
            << endl;
    }

    cout << string(101, '=') << endl;

    PQclear(result);
}



void MedicineService::updateMedicine(DBConnection& db)
{
    int id;
    double price;
    int quantity;

    cout << "\nMedicine ID : ";
    cin >> id;

    cout << "New Price : ";
    cin >> price;

    cout << "New Quantity : ";
    cin >> quantity;

    string query =
        "UPDATE medicines "
        "SET price=" + to_string(price) +
        ", quantity=" + to_string(quantity) +
        " WHERE medicine_id=" + to_string(id);

    PGresult* result =
        PQexec(db.getConnection(), query.c_str());

    if (PQresultStatus(result) == PGRES_COMMAND_OK)
    {
        cout << "\nMedicine Updated Successfully.\n";
    }

    PQclear(result);
}

void MedicineService::deleteMedicine(DBConnection& db)
{
    int id;

    cout << "\nMedicine ID : ";
    cin >> id;

    string query =
        "UPDATE medicines "
        "SET is_active = FALSE "
        "WHERE medicine_id = " +
        to_string(id);

    PGresult* result =
        PQexec(db.getConnection(), query.c_str());

    if (PQresultStatus(result) == PGRES_COMMAND_OK)
    {
        if (atoi(PQcmdTuples(result)) > 0)
        {
            cout << "\nMedicine Deactivated Successfully.\n";
        }
        else
        {
            cout << "\nMedicine ID Not Found.\n";
        }
    }
    else
    {
        cout << "\nDelete Failed!\n";
        cout << PQerrorMessage(db.getConnection()) << endl;
    }

    PQclear(result);
}

void MedicineService::searchMedicine(DBConnection& db)
{
    string name;

    cout << "\nEnter Medicine Name : ";
    cin >> name;

    string query =
        "SELECT * FROM medicines "
        "WHERE name ILIKE '%" + name + "%'";

    PGresult* result =
        PQexec(db.getConnection(), query.c_str());

    int rows = PQntuples(result);

    for (int i = 0; i < rows; i++)
    {
        cout << "\nID : "
            << PQgetvalue(result, i, 0);

        cout << "\nName : "
            << PQgetvalue(result, i, 1);

        cout << "\nManufacturer : "
            << PQgetvalue(result, i, 2);

        cout << "\nQty : "
            << PQgetvalue(result, i, 8);

        cout << "\n-------------------\n";
    }

    PQclear(result);
}