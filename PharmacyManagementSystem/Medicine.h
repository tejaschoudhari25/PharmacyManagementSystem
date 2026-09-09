#pragma once

#include <string>

using namespace std;

class Medicine
{
public:
    int medicineId;
    string name;
    string manufacturer;
    string category;
    string batchNo;
    string mfgDate;
    string expiryDate;
    double price;
    int quantity;
};