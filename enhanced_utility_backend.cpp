#include "data_structures.h"
#include <sstream>

// Global Data Structures - Array with Sorting
vector<Utility> utilityArray;
// Using map for type-based lookup (simpler than hash table for this case)
#include <map>
map<string, vector<Utility>> utilityHashByType;

// ============================================
// ARRAY OPERATIONS
// ============================================

void addUtility(Utility u)
{
    utilityArray.push_back(u);

    // Add to map by type
    utilityHashByType[u.utilityType].push_back(u);

    cout << "Utility record added successfully!\n";
}

Utility *searchByUtilityId(int id)
{
    for (auto &utility : utilityArray)
    {
        if (utility.utilityId == id)
        {
            return &utility;
        }
    }
    return nullptr;
}

void deleteUtility(int id)
{
    auto it = utilityArray.begin();
    while (it != utilityArray.end())
    {
        if (it->utilityId == id)
        {
            // Remove from map
            if (utilityHashByType.find(it->utilityType) != utilityHashByType.end())
            {
                auto &typeList = utilityHashByType[it->utilityType];
                typeList.erase(
                    remove_if(typeList.begin(), typeList.end(),
                              [id](Utility u)
                              { return u.utilityId == id; }),
                    typeList.end());
            }

            utilityArray.erase(it);
            cout << "Utility record deleted successfully!\n";
            return;
        }
        it++;
    }
    cout << "Utility ID not found!\n";
}

// ============================================
// FILE OPERATIONS
// ============================================

void loadUtilityFromFile()
{
    ifstream file("../SmartCity_Data/utility.txt");

    if (!file)
    {
        cout << "Utility file not found. Creating new file.\n";
        return;
    }

    string line;
    Utility temp;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        if (line.find("Utility ID") != string::npos)
        {
            temp.utilityId = stoi(line.substr(line.find(":") + 2));
        }
        else if (line.find("Utility Type") != string::npos)
        {
            temp.utilityType = line.substr(line.find(":") + 2);
        }
        else if (line.find("Consumer Name") != string::npos)
        {
            temp.consumerName = line.substr(line.find(":") + 2);
        }
        else if (line.find("Units Consumed") != string::npos)
        {
            temp.units = stoi(line.substr(line.find(":") + 2));
        }
        else if (line.find("Bill Amount") != string::npos)
        {
            temp.billAmount = stoi(line.substr(line.find(":") + 2));
            addUtility(temp);
        }
    }

    file.close();
    cout << "Loaded " << utilityArray.size() << " utility records.\n";
}

void saveUtilityToFile()
{
    ofstream file("../SmartCity_Data/utility.txt");

    for (const auto &utility : utilityArray)
    {
        file << "Utility ID     : " << utility.utilityId << "\n";
        file << "Utility Type   : " << utility.utilityType << "\n";
        file << "Consumer Name  : " << utility.consumerName << "\n";
        file << "Units Consumed : " << utility.units << "\n";
        file << "Bill Amount    : " << utility.billAmount << "\n";
        file << "----------------------------------------\n";
    }

    file.close();
    cout << "Saved " << utilityArray.size() << " records to file.\n";
}

// ============================================
// DISPLAY OPERATIONS
// ============================================

void displayAllUtilities()
{
    if (utilityArray.empty())
    {
        cout << "No utility records available.\n";
        return;
    }

    cout << "\n=== ALL UTILITY BILLING RECORDS ===\n";
    cout << setw(5) << "UID" << setw(15) << "Type" << setw(20) << "Consumer Name"
         << setw(12) << "Units" << setw(12) << "Bill\n";
    cout << string(64, '-') << "\n";

    for (const auto &utility : utilityArray)
    {
        cout << setw(5) << utility.utilityId
             << setw(15) << utility.utilityType
             << setw(20) << utility.consumerName
             << setw(12) << utility.units
             << setw(12) << utility.billAmount << "\n";
    }

    cout << "\nTotal Records: " << utilityArray.size() << "\n";
}

void displaySortedByBill()
{
    if (utilityArray.empty())
    {
        cout << "No records to sort.\n";
        return;
    }

    vector<Utility> sorted = utilityArray;
    SortingAlgorithms::mergeSort(sorted, 0, sorted.size() - 1,
                                 [](const Utility &a, const Utility &b)
                                 { return a.billAmount > b.billAmount; });

    cout << "\n=== UTILITIES SORTED BY BILL (Descending - Merge Sort) ===\n";
    cout << setw(5) << "UID" << setw(15) << "Type" << setw(20) << "Consumer Name"
         << setw(12) << "Units" << setw(12) << "Bill\n";
    cout << string(64, '-') << "\n";

    for (const auto &utility : sorted)
    {
        cout << setw(5) << utility.utilityId
             << setw(15) << utility.utilityType
             << setw(20) << utility.consumerName
             << setw(12) << utility.units
             << setw(12) << utility.billAmount << "\n";
    }
}

void displayByType(string type)
{
    if (utilityHashByType.find(type) == utilityHashByType.end() ||
        utilityHashByType[type].empty())
    {
        cout << "No records found for type: " << type << "\n";
        return;
    }

    vector<Utility> &typeList = utilityHashByType[type];

    cout << "\n=== UTILITY RECORDS FOR TYPE: " << type << " (Map Search) ===\n";
    cout << setw(5) << "UID" << setw(20) << "Consumer Name"
         << setw(12) << "Units" << setw(12) << "Bill\n";
    cout << string(49, '-') << "\n";

    for (const auto &utility : typeList)
    {
        cout << setw(5) << utility.utilityId
             << setw(20) << utility.consumerName
             << setw(12) << utility.units
             << setw(12) << utility.billAmount << "\n";
    }

    cout << "\nTotal " << type << " Records: " << typeList.size() << "\n";
}

// ============================================
// STATISTICS
// ============================================

void displayStatistics()
{
    if (utilityArray.empty())
    {
        cout << "No data available for statistics.\n";
        return;
    }

    int total = utilityArray.size();
    int totalBill = 0;
    int totalUnits = 0;
    int electricity = 0, water = 0, gas = 0;

    for (const auto &utility : utilityArray)
    {
        totalBill += utility.billAmount;
        totalUnits += utility.units;

        if (utility.utilityType.find("Electricity") != string::npos)
            electricity++;
        else if (utility.utilityType.find("Water") != string::npos)
            water++;
        else if (utility.utilityType.find("Gas") != string::npos)
            gas++;
    }

    double avgBill = (double)totalBill / total;
    double avgUnits = (double)totalUnits / total;

    cout << "\n=== UTILITY STATISTICS ===\n";
    cout << "Total Records        : " << total << "\n";
    cout << "Total Bill Amount    : " << totalBill << "\n";
    cout << "Total Units Consumed : " << totalUnits << "\n";
    cout << "Average Bill         : " << fixed << setprecision(2) << avgBill << "\n";
    cout << "Average Units        : " << fixed << setprecision(2) << avgUnits << "\n";
    cout << "Electricity Records  : " << electricity << "\n";
    cout << "Water Records        : " << water << "\n";
    cout << "Gas Records          : " << gas << "\n";
    cout << "Data Structures      : Array, Map (Hash Table)\n";
}

// ============================================
// MAIN MENU
// ============================================

void displayMenu()
{
    cout << "\n========================================\n";
    cout << "   SMART CITY - UTILITY MANAGEMENT\n";
    cout << "   Array & Hash Table System\n";
    cout << "========================================\n";
    cout << "1. Add New Utility Record\n";
    cout << "2. Search Utility by ID\n";
    cout << "3. Delete Utility Record\n";
    cout << "4. Display All Records\n";
    cout << "5. Display Sorted by Bill (Merge Sort)\n";
    cout << "6. Display by Type (Hash Table Search)\n";
    cout << "7. Display Statistics\n";
    cout << "8. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

int main()
{
    loadUtilityFromFile();

    int choice;
    Utility newUtility;
    string searchType;

    while (true)
    {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "\nEnter Utility ID: ";
            cin >> newUtility.utilityId;
            cin.ignore();
            cout << "Enter Utility Type (Electricity/Water/Gas): ";
            getline(cin, newUtility.utilityType);
            cout << "Enter Consumer Name: ";
            getline(cin, newUtility.consumerName);
            cout << "Enter Units Consumed: ";
            cin >> newUtility.units;
            cout << "Enter Bill Amount: ";
            cin >> newUtility.billAmount;
            addUtility(newUtility);
            saveUtilityToFile();
            break;

        case 2:
            cout << "\nEnter Utility ID to search: ";
            cin >> choice;
            {
                Utility *found = searchByUtilityId(choice);
                if (found != nullptr)
                {
                    cout << "\n=== Utility Found ===\n";
                    cout << "Utility ID     : " << found->utilityId << "\n";
                    cout << "Utility Type   : " << found->utilityType << "\n";
                    cout << "Consumer Name  : " << found->consumerName << "\n";
                    cout << "Units Consumed : " << found->units << "\n";
                    cout << "Bill Amount    : " << found->billAmount << "\n";
                }
                else
                {
                    cout << "Utility ID not found!\n";
                }
            }
            break;

        case 3:
            cout << "\nEnter Utility ID to delete: ";
            cin >> choice;
            deleteUtility(choice);
            saveUtilityToFile();
            break;

        case 4:
            displayAllUtilities();
            break;

        case 5:
            displaySortedByBill();
            break;

        case 6:
            cout << "\nEnter Utility Type to search (Electricity/Water/Gas): ";
            getline(cin, searchType);
            displayByType(searchType);
            break;

        case 7:
            displayStatistics();
            break;

        case 8:
            saveUtilityToFile();
            cout << "Exiting... Goodbye!\n";
            return 0;

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
