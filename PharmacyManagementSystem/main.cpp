#include <iostream>

#include "DBConnection.h"
#include "AuthService.h"
#include "MedicineService.h"
#include "CustomerService.h"
#include "SalesService.h"
#include "ExpiryService.h"
#include "PrescriptionService.h"

using namespace std;

void medicineMenu(DBConnection& db, MedicineService& medicineService);
void customerMenu(DBConnection& db, CustomerService& customerService);
void expiryMenu(DBConnection& db, ExpiryService& expiryService);
void prescriptionMenu(DBConnection& db, PrescriptionService& prescriptionService);

int main()
{
    DBConnection db;

    if (!db.connect())
        return 1;

    AuthService auth;

    string role = auth.login(db);

    if (role == "")
    {
        db.disconnect();
        return 1;
    }

    MedicineService medicineService;
    CustomerService customerService;
    SalesService salesService;
    ExpiryService expiryService;
    PrescriptionService prescriptionService;

    int choice;

    do
    {
        cout << "\n=================================\n";
        cout << " PHARMACY MANAGEMENT SYSTEM\n";
        cout << " Logged In As : " << role << endl;
        cout << "=================================\n";

        if (role == "ADMIN")
        {
            cout << "1. Medicine Management\n";
            cout << "2. Customer Management\n";
            cout << "3. Purchase Management\n";
            cout << "4. Sales Management\n";
            cout << "5. Expiry Management\n";
            cout << "6. Prescription Management\n";
            cout << "7. Logout\n";
        }
        else if (role == "PHARMACIST")
        {
            cout << "2. Customer Management\n";
            cout << "4. Sales Management\n";
            cout << "6. Prescription Management\n";
            cout << "7. Logout\n";
        }
        else if (role == "STORE_MANAGER")
        {
            cout << "1. Medicine Management\n";
            cout << "3. Purchase Management\n";
            cout << "5. Expiry Management\n";
            cout << "7. Logout\n";
        }

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:

            if (role == "ADMIN" || role == "STORE_MANAGER")
            {
                medicineMenu(db, medicineService);
            }
            else
            {
                cout << "\nAccess Denied!\n";
            }

            break;

        case 2:

            if (role == "ADMIN" || role == "PHARMACIST")
            {
                customerMenu(db, customerService);
            }
            else
            {
                cout << "\nAccess Denied!\n";
            }

            break;

        case 3:

            if (role == "ADMIN" || role == "STORE_MANAGER")
            {
                cout << "\nPurchase Module\n";
                cout << "Connect PurchaseService here.\n";
            }
            else
            {
                cout << "\nAccess Denied!\n";
            }

            break;

        case 4:

            if (role == "ADMIN" || role == "PHARMACIST")
            {
                salesService.sellMedicine(db);
            }
            else
            {
                cout << "\nAccess Denied!\n";
            }

            break;

        case 5:

            if (role == "ADMIN" || role == "STORE_MANAGER")
            {
                expiryMenu(db, expiryService);
            }
            else
            {
                cout << "\nAccess Denied!\n";
            }

            break;

        case 6:

            if (role == "ADMIN" || role == "PHARMACIST")
            {
                prescriptionMenu(db, prescriptionService);
            }
            else
            {
                cout << "\nAccess Denied!\n";
            }

            break;

        case 7:

            cout << "\nLogging Out...\n";
            break;

        default:

            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 7);

    db.disconnect();

    return 0;
}

void medicineMenu(DBConnection& db, MedicineService& medicineService)
{
    int choice;

    do
    {
        cout << "\n===== MEDICINE MANAGEMENT =====\n";
        cout << "1. Add Medicine\n";
        cout << "2. View Medicines\n";
        cout << "3. Update Medicine\n";
        cout << "4. Delete Medicine\n";
        cout << "5. Search Medicine\n";
        cout << "6. Back\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            medicineService.addMedicine(db);
            break;

        case 2:
            medicineService.viewMedicines(db);
            break;

        case 3:
            medicineService.updateMedicine(db);
            break;

        case 4:
            medicineService.deleteMedicine(db);
            break;

        case 5:
            medicineService.searchMedicine(db);
            break;

        case 6:
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);
}

void customerMenu(DBConnection& db, CustomerService& customerService)
{
    int choice;

    do
    {
        cout << "\n===== CUSTOMER MANAGEMENT =====\n";
        cout << "1. Add Customer\n";
        cout << "2. View Customers\n";
        cout << "3. Update Customer\n";
        cout << "4. Back\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            customerService.addCustomer(db);
            break;

        case 2:
            customerService.viewCustomers(db);
            break;

        case 3:
            customerService.updateCustomer(db);
            break;

        case 4:
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 4);
}

void expiryMenu(DBConnection& db, ExpiryService& expiryService)
{
    int choice;

    do
    {
        cout << "\n===== EXPIRY MANAGEMENT =====\n";
        cout << "1. View Expired Medicines\n";
        cout << "2. View Near Expiry Medicines\n";
        cout << "3. Back\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            expiryService.showExpiredMedicines(db);
            break;

        case 2:
            expiryService.showNearExpiryMedicines(db);
            break;

        case 3:
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 3);
}

void prescriptionMenu(DBConnection& db, PrescriptionService& prescriptionService)
{
    int choice;

    do
    {
        cout << "\n===== PRESCRIPTION MANAGEMENT =====\n";
        cout << "1. Save Prescription\n";
        cout << "2. View Prescriptions\n";
        cout << "3. Back\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            prescriptionService.savePrescription(db);
            break;

        case 2:
            prescriptionService.viewPrescriptions(db);
            break;

        case 3:
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 3);
}