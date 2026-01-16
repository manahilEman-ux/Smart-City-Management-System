#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* ==========================
   STRUCT (Utility Record)
========================== */
struct Utility
{
    int utilityId;
    string utilityType;
    string consumerName;
    int units;
    int billAmount;
};

/* ==========================
   ARRAY DECLARATION
========================== */
Utility utilities[50];
int countUtility = 0;

/* ==========================
   LOAD FILE → ARRAY
========================== */
void loadUtilityFromFile()
{
    ifstream file("Utility_Record.txt");

    if (!file)
    {
        cout << "Utility record file not found.\n";
        return;
    }

    string line;
    Utility temp;

    while (getline(file, line))
    {

        if (line.find("Utility ID") != string::npos)
        {
            temp.utilityId = stoi(line.substr(line.find(":") + 1));
        }
        else if (line.find("Utility Type") != string::npos)
        {
            temp.utilityType = line.substr(line.find(":") + 1);
        }
        else if (line.find("Consumer Name") != string::npos)
        {
            temp.consumerName = line.substr(line.find(":") + 1);
        }
        else if (line.find("Units Consumed") != string::npos)
        {
            temp.units = stoi(line.substr(line.find(":") + 1));
        }
        else if (line.find("Bill Amount") != string::npos)
        {
            temp.billAmount = stoi(line.substr(line.find(":") + 1));
            utilities[countUtility++] = temp; // COMPLETE RECORD → ARRAY
        }
    }

    file.close();
}

/* ==========================
   DISPLAY ARRAY RECORDS
========================== */
void displayUtilities()
{
    if (countUtility == 0)
    {
        cout << "No utility records available.\n";
        return;
    }

    cout << "\n===== UTILITY BILLING RECORDS =====\n";

    for (int i = 0; i < countUtility; i++)
    {
        cout << "\nUtility ID     : " << utilities[i].utilityId;
        cout << "\nUtility Type   : " << utilities[i].utilityType;
        cout << "\nConsumer Name  : " << utilities[i].consumerName;
        cout << "\nUnits Consumed : " << utilities[i].units;
        cout << "\nBill Amount    : " << utilities[i].billAmount;
        cout << "\n----------------------------------\n";
    }
}

/* ==========================
   MAIN
========================== */
int main()
{
    loadUtilityFromFile();
    displayUtilities();
    return 0;
}
