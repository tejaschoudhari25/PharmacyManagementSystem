#include "CustomerService.h"
#include <iostream>
#include <string>


using namespace std;

void CustomerService::addCustomer(DBConnection& db)
{
    string name, phone, address;

    cin.ignore();

    cout << "\nCustomer Name : ";
    getline(cin, name);

    cout << "Phone : ";
    getline(cin, phone);

    cout << "Address : ";
    getline(cin, address);

    string query =
        "INSERT INTO customers(name,phone,address) VALUES('" +
        name + "','" +
        phone + "','" +
        address + "')";

    PGresult* result =
        PQexec(db.getConnection(), query.c_str());

    if (PQresultStatus(result) == PGRES_COMMAND_OK)
        cout << "\nCustomer Added Successfully.\n";

    PQclear(result);
}

void CustomerService::viewCustomers(DBConnection& db)
{
    string query =
        "SELECT * FROM customers ORDER BY customer_id";

    PGresult* result =
        PQexec(db.getConnection(), query.c_str());

    int rows = PQntuples(result);

    cout << "\n======= CUSTOMERS =======\n";

    for (int i = 0; i < rows; i++)
    {
        cout << "\nID : "
            << PQgetvalue(result, i, 0);

        cout << "\nName : "
            << PQgetvalue(result, i, 1);

        cout << "\nPhone : "
            << PQgetvalue(result, i, 2);

        cout << "\nAddress : "
            << PQgetvalue(result, i, 3);

        cout << "\n---------------------------\n";
    }

    PQclear(result);
}

void CustomerService::updateCustomer(DBConnection& db)
{
    int customerId;
    string phone;

    cout << "\nCustomer ID : ";
    cin >> customerId;

    cout << "New Phone : ";
    cin >> phone;

    string query =
        "UPDATE customers SET phone='" +
        phone +
        "' WHERE customer_id=" +
        to_string(customerId);

    PGresult* result =
        PQexec(db.getConnection(), query.c_str());

    if (PQresultStatus(result) == PGRES_COMMAND_OK)
        cout << "\nCustomer Updated Successfully.\n";

    PQclear(result);
}