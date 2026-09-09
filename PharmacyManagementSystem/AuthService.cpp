#include "AuthService.h"
#include <iostream>

using namespace std;

string AuthService::login(DBConnection& db)
{
    string username;
    string password;

    cout << "\n===== LOGIN =====\n";

    cout << "Username : ";
    cin >> username;

    cout << "Password : ";
    cin >> password;

    string query =
        "SELECT role FROM users WHERE username='" +
        username +
        "' AND password='" +
        password +
        "'";

    PGresult* result =
        PQexec(db.getConnection(), query.c_str());

    if (PQntuples(result) > 0)
    {
        string role = PQgetvalue(result, 0, 0);

        cout << "\nLogin Successful!\n";
        cout << "Role : " << role << endl;

        PQclear(result);
        return role;
    }

    PQclear(result);

    cout << "\nInvalid Username or Password!\n";

    return "";
}