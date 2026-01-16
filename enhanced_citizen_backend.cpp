#include "data_structures.h"
#include <sstream>

// Global Data Structures
BinarySearchTree<Citizen> citizenBST;
HashTable<int, Citizen> citizenHashTable;
vector<Citizen> citizenArray;

// ============================================
// FILE OPERATIONS
// ============================================

void loadCitizensFromFile() {
    ifstream file("../SmartCity_Data/citizen.txt");
    
    if (!file) {
        cout << "Citizen file not found. Creating new file.\n";
        return;
    }
    
    string line;
    Citizen temp;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 6) {
            temp.id = stoi(tokens[0]);
            temp.name = tokens[1];
            temp.age = stoi(tokens[2]);
            temp.cnic = tokens[3];
            temp.phone = tokens[4];
            temp.address = tokens[5];
            
            // Insert into all data structures
            citizenBST.insert(temp);
            citizenHashTable.insert(temp.id, temp);
            citizenArray.push_back(temp);
        }
    }
    
    file.close();
    cout << "Loaded " << citizenArray.size() << " citizen records.\n";
}

void saveCitizensToFile() {
    ofstream file("../SmartCity_Data/citizen.txt");
    
    vector<Citizen> sorted = citizenBST.inOrderTraversal();
    
    for (const auto& citizen : sorted) {
        file << citizen.id << ","
             << citizen.name << ","
             << citizen.age << ","
             << citizen.cnic << ","
             << citizen.phone << ","
             << citizen.address << "\n";
    }
    
    file.close();
    cout << "Saved " << sorted.size() << " records to file.\n";
}

// ============================================
// CRUD OPERATIONS
// ============================================

void addCitizen(Citizen c) {
    // Check if ID already exists
    if (citizenHashTable.search(c.id) != nullptr) {
        cout << "Error: Citizen ID " << c.id << " already exists!\n";
        return;
    }
    
    citizenBST.insert(c);
    citizenHashTable.insert(c.id, c);
    citizenArray.push_back(c);
    
    cout << "Citizen added successfully!\n";
    saveCitizensToFile();
}

void searchCitizen(int id) {
    // O(log n) search in BST
    Citizen* result = citizenBST.search(id);
    
    if (result != nullptr) {
        cout << "\n=== Citizen Found (BST Search) ===\n";
        cout << "ID      : " << result->id << "\n";
        cout << "Name    : " << result->name << "\n";
        cout << "Age     : " << result->age << "\n";
        cout << "CNIC    : " << result->cnic << "\n";
        cout << "Phone   : " << result->phone << "\n";
        cout << "Address : " << result->address << "\n";
    } else {
        // O(1) search in Hash Table
        Citizen* hashResult = citizenHashTable.search(id);
        if (hashResult != nullptr) {
            cout << "\n=== Citizen Found (Hash Table Search) ===\n";
            cout << "ID      : " << hashResult->id << "\n";
            cout << "Name    : " << hashResult->name << "\n";
            cout << "Age     : " << hashResult->age << "\n";
            cout << "CNIC    : " << hashResult->cnic << "\n";
            cout << "Phone   : " << hashResult->phone << "\n";
            cout << "Address : " << hashResult->address << "\n";
        } else {
            cout << "Citizen with ID " << id << " not found!\n";
        }
    }
}

void deleteCitizen(int id) {
    Citizen* found = citizenHashTable.search(id);
    if (found == nullptr) {
        cout << "Citizen with ID " << id << " not found!\n";
        return;
    }
    
    citizenBST.remove(id);
    citizenHashTable.remove(id);
    citizenArray.erase(
        remove_if(citizenArray.begin(), citizenArray.end(),
            [id](Citizen c) { return c.id == id; }),
        citizenArray.end()
    );
    
    cout << "Citizen deleted successfully!\n";
    saveCitizensToFile();
}

// ============================================
// DISPLAY OPERATIONS
// ============================================

void displayAllCitizens() {
    if (citizenBST.isEmpty()) {
        cout << "No citizen records available.\n";
        return;
    }
    
    vector<Citizen> sorted = citizenBST.inOrderTraversal();
    
    cout << "\n=== ALL CITIZEN RECORDS (Sorted by ID - BST In-Order) ===\n";
    cout << setw(5) << "ID" << setw(20) << "Name" << setw(8) << "Age"
         << setw(15) << "CNIC" << setw(15) << "Phone" << setw(25) << "Address\n";
    cout << string(88, '-') << "\n";
    
    for (const auto& citizen : sorted) {
        cout << setw(5) << citizen.id
             << setw(20) << citizen.name
             << setw(8) << citizen.age
             << setw(15) << citizen.cnic
             << setw(15) << citizen.phone
             << setw(25) << citizen.address << "\n";
    }
    
    cout << "\nTotal Records: " << sorted.size() << "\n";
    cout << "BST Height: " << citizenBST.getHeight() << "\n";
}

void displaySortedByName() {
    if (citizenArray.empty()) {
        cout << "No records to sort.\n";
        return;
    }
    
    vector<Citizen> sorted = citizenArray;
    
    // Using Quick Sort
    SortingAlgorithms::quickSort(sorted, 0, sorted.size() - 1,
        [](Citizen a, Citizen b) { return a.name < b.name; });
    
    cout << "\n=== CITIZENS SORTED BY NAME (Quick Sort) ===\n";
    cout << setw(5) << "ID" << setw(20) << "Name" << setw(8) << "Age"
         << setw(15) << "CNIC" << setw(15) << "Phone\n";
    cout << string(63, '-') << "\n";
    
    for (const auto& citizen : sorted) {
        cout << setw(5) << citizen.id
             << setw(20) << citizen.name
             << setw(8) << citizen.age
             << setw(15) << citizen.cnic
             << setw(15) << citizen.phone << "\n";
    }
}

void displaySortedByAge() {
    if (citizenArray.empty()) {
        cout << "No records to sort.\n";
        return;
    }
    
    vector<Citizen> sorted = citizenArray;
    
    // Using Merge Sort
    SortingAlgorithms::mergeSort(sorted, 0, sorted.size() - 1,
        [](Citizen a, Citizen b) { return a.age < b.age; });
    
    cout << "\n=== CITIZENS SORTED BY AGE (Merge Sort) ===\n";
    cout << setw(5) << "ID" << setw(20) << "Name" << setw(8) << "Age"
         << setw(15) << "CNIC" << setw(15) << "Phone\n";
    cout << string(63, '-') << "\n";
    
    for (const auto& citizen : sorted) {
        cout << setw(5) << citizen.id
             << setw(20) << citizen.name
             << setw(8) << citizen.age
             << setw(15) << citizen.cnic
             << setw(15) << citizen.phone << "\n";
    }
}

// ============================================
// STATISTICS
// ============================================

void displayStatistics() {
    if (citizenArray.empty()) {
        cout << "No data available for statistics.\n";
        return;
    }
    
    int total = citizenArray.size();
    int sumAge = 0;
    int minAge = INT_MAX, maxAge = 0;
    
    for (const auto& citizen : citizenArray) {
        sumAge += citizen.age;
        minAge = min(minAge, citizen.age);
        maxAge = max(maxAge, citizen.age);
    }
    
    double avgAge = (double)sumAge / total;
    
    cout << "\n=== CITIZEN STATISTICS ===\n";
    cout << "Total Citizens    : " << total << "\n";
    cout << "Average Age       : " << fixed << setprecision(2) << avgAge << "\n";
    cout << "Minimum Age       : " << minAge << "\n";
    cout << "Maximum Age       : " << maxAge << "\n";
    cout << "BST Height        : " << citizenBST.getHeight() << "\n";
    cout << "Data Structures   : BST, Hash Table, Array\n";
}

// ============================================
// MAIN MENU
// ============================================

void displayMenu() {
    cout << "\n========================================\n";
    cout << "   SMART CITY - CITIZEN MANAGEMENT\n";
    cout << "   Advanced Data Structures System\n";
    cout << "========================================\n";
    cout << "1. Add New Citizen\n";
    cout << "2. Search Citizen (BST/Hash Table)\n";
    cout << "3. Delete Citizen\n";
    cout << "4. Display All (BST In-Order)\n";
    cout << "5. Display Sorted by Name (Quick Sort)\n";
    cout << "6. Display Sorted by Age (Merge Sort)\n";
    cout << "7. Display Statistics\n";
    cout << "8. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

int main() {
    loadCitizensFromFile();
    
    int choice;
    Citizen newCitizen;
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                cout << "\nEnter Citizen ID: ";
                cin >> newCitizen.id;
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, newCitizen.name);
                cout << "Enter Age: ";
                cin >> newCitizen.age;
                cin.ignore();
                cout << "Enter CNIC: ";
                getline(cin, newCitizen.cnic);
                cout << "Enter Phone: ";
                getline(cin, newCitizen.phone);
                cout << "Enter Address: ";
                getline(cin, newCitizen.address);
                addCitizen(newCitizen);
                break;
                
            case 2:
                cout << "\nEnter Citizen ID to search: ";
                cin >> choice;
                searchCitizen(choice);
                break;
                
            case 3:
                cout << "\nEnter Citizen ID to delete: ";
                cin >> choice;
                deleteCitizen(choice);
                break;
                
            case 4:
                displayAllCitizens();
                break;
                
            case 5:
                displaySortedByName();
                break;
                
            case 6:
                displaySortedByAge();
                break;
                
            case 7:
                displayStatistics();
                break;
                
            case 8:
                saveCitizensToFile();
                cout << "Exiting... Goodbye!\n";
                return 0;
                
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
    
    return 0;
}

