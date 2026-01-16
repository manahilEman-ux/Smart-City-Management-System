#include <iostream>
#include <fstream>
using namespace std;

/* ======================
   STRUCT + ARRAY (DS)
====================== */
struct Citizen
{
    int id;
    string name;
    int age;
    string cnic;
    string phone;
    string address;
};

Citizen citizens[100];
int countCitizen = 0;

/* ======================
   FILE READ FUNCTION
====================== */
void loadCitizensFromFile()
{
    ifstream file("SmartCity_Data/citizen.txt");

    if (!file)
    {
        cout << "Citizen file not found.\n";
        return;
    }

    while (file >> citizens[countCitizen].id)
    {
        file.ignore();
        getline(file, citizens[countCitizen].name, ',');
        file >> citizens[countCitizen].age;
        file.ignore();
        getline(file, citizens[countCitizen].cnic, ',');
        getline(file, citizens[countCitizen].phone, ',');
        getline(file, citizens[countCitizen].address);

        countCitizen++;
    }

    file.close();
}

/* ======================
   DISPLAY (DS TRAVERSAL)
====================== */
void displayCitizens()
{
    cout << "\n--- Citizen Records ---\n";
    for (int i = 0; i < countCitizen; i++)
    {
        cout << citizens[i].id << " "
             << citizens[i].name << " "
             << citizens[i].age << " "
             << citizens[i].cnic << " "
             << citizens[i].phone << " "
             << citizens[i].address << endl;
    }
}

int main()
{
    loadCitizensFromFile();
    displayCitizens();
    return 0;
}
