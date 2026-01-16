#include "data_structures.h"
#include <sstream>

// Global Data Structures - Stack
stack<Traffic> trafficStack;
vector<Traffic> trafficArray;

// ============================================
// STACK OPERATIONS
// ============================================

void pushViolation(Traffic t) {
    trafficStack.push(t);
    trafficArray.push_back(t);
    cout << "Violation record added to stack!\n";
}

Traffic popViolation() {
    if (trafficStack.empty()) {
        throw runtime_error("Stack is empty!");
    }
    
    Traffic top = trafficStack.top();
    trafficStack.pop();
    
    // Remove from array
    trafficArray.erase(
        remove_if(trafficArray.begin(), trafficArray.end(),
            [top](Traffic t) { return t.violationId == top.violationId; }),
        trafficArray.end()
    );
    
    return top;
}

Traffic peekViolation() {
    if (trafficStack.empty()) {
        throw runtime_error("Stack is empty!");
    }
    return trafficStack.top();
}

// ============================================
// FILE OPERATIONS
// ============================================

void loadTrafficFromFile() {
    ifstream file("../SmartCity_Data/traffic.txt");
    
    if (!file) {
        cout << "Traffic file not found. Creating new file.\n";
        return;
    }
    
    string line;
    Traffic temp;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        if (line.find("Violation ID") != string::npos) {
            temp.violationId = stoi(line.substr(line.find(":") + 2));
        } else if (line.find("Vehicle Number") != string::npos) {
            temp.vehicleNumber = line.substr(line.find(":") + 2);
        } else if (line.find("Driver Name") != string::npos) {
            temp.driverName = line.substr(line.find(":") + 2);
        } else if (line.find("Violation Type") != string::npos) {
            temp.violationType = line.substr(line.find(":") + 2);
        } else if (line.find("Fine Amount") != string::npos) {
            temp.fineAmount = stoi(line.substr(line.find(":") + 2));
            pushViolation(temp);
        }
    }
    
    file.close();
    cout << "Loaded " << trafficArray.size() << " traffic violation records.\n";
}

void saveTrafficToFile() {
    ofstream file("../SmartCity_Data/traffic.txt");
    
    // Save in reverse order (stack order)
    stack<Traffic> tempStack = trafficStack;
    vector<Traffic> reverseOrder;
    
    while (!tempStack.empty()) {
        reverseOrder.push_back(tempStack.top());
        tempStack.pop();
    }
    
    reverse(reverseOrder.begin(), reverseOrder.end());
    
    for (const auto& violation : reverseOrder) {
        file << "Violation ID   : " << violation.violationId << "\n";
        file << "Vehicle Number : " << violation.vehicleNumber << "\n";
        file << "Driver Name    : " << violation.driverName << "\n";
        file << "Violation Type : " << violation.violationType << "\n";
        file << "Fine Amount    : " << violation.fineAmount << "\n";
        file << "----------------------------------------\n";
    }
    
    file.close();
    cout << "Saved " << trafficArray.size() << " records to file.\n";
}

// ============================================
// DISPLAY OPERATIONS
// ============================================

void displayStack() {
    if (trafficStack.empty()) {
        cout << "Stack is empty!\n";
        return;
    }
    
    cout << "\n=== TRAFFIC VIOLATIONS STACK (LIFO - Latest First) ===\n";
    stack<Traffic> tempStack = trafficStack;
    int index = 1;
    
    while (!tempStack.empty()) {
        Traffic t = tempStack.top();
        tempStack.pop();
        cout << "\n[" << index++ << "] TOP OF STACK\n";
        cout << "Violation ID   : " << t.violationId << "\n";
        cout << "Vehicle Number : " << t.vehicleNumber << "\n";
        cout << "Driver Name    : " << t.driverName << "\n";
        cout << "Violation Type : " << t.violationType << "\n";
        cout << "Fine Amount    : " << t.fineAmount << "\n";
        cout << "----------------------------------------\n";
    }
}

void displayAllViolations() {
    if (trafficArray.empty()) {
        cout << "No violations available.\n";
        return;
    }
    
    cout << "\n=== ALL TRAFFIC VIOLATIONS ===\n";
    cout << setw(5) << "VID" << setw(15) << "Vehicle No" 
         << setw(20) << "Driver Name" << setw(20) << "Violation Type" << setw(12) << "Fine\n";
    cout << string(72, '-') << "\n";
    
    for (const auto& violation : trafficArray) {
        cout << setw(5) << violation.violationId
             << setw(15) << violation.vehicleNumber
             << setw(20) << violation.driverName
             << setw(20) << violation.violationType
             << setw(12) << violation.fineAmount << "\n";
    }
    
    cout << "\nTotal Violations: " << trafficArray.size() << "\n";
}

void displaySortedByFine() {
    if (trafficArray.empty()) {
        cout << "No violations to sort.\n";
        return;
    }
    
    vector<Traffic> sorted = trafficArray;
    SortingAlgorithms::quickSort(sorted, 0, sorted.size() - 1,
        [](Traffic a, Traffic b) { return a.fineAmount > b.fineAmount; });
    
    cout << "\n=== VIOLATIONS SORTED BY FINE (Descending - Quick Sort) ===\n";
    cout << setw(5) << "VID" << setw(15) << "Vehicle No" 
         << setw(20) << "Driver Name" << setw(20) << "Violation Type" << setw(12) << "Fine\n";
    cout << string(72, '-') << "\n";
    
    for (const auto& violation : sorted) {
        cout << setw(5) << violation.violationId
             << setw(15) << violation.vehicleNumber
             << setw(20) << violation.driverName
             << setw(20) << violation.violationType
             << setw(12) << violation.fineAmount << "\n";
    }
}

// ============================================
// STATISTICS
// ============================================

void displayStatistics() {
    if (trafficArray.empty()) {
        cout << "No data available for statistics.\n";
        return;
    }
    
    int total = trafficArray.size();
    int totalFine = 0;
    int minFine = INT_MAX, maxFine = 0;
    
    for (const auto& violation : trafficArray) {
        totalFine += violation.fineAmount;
        minFine = min(minFine, violation.fineAmount);
        maxFine = max(maxFine, violation.fineAmount);
    }
    
    double avgFine = (double)totalFine / total;
    
    cout << "\n=== TRAFFIC STATISTICS ===\n";
    cout << "Total Violations    : " << total << "\n";
    cout << "Total Fine Amount   : " << totalFine << "\n";
    cout << "Average Fine        : " << fixed << setprecision(2) << avgFine << "\n";
    cout << "Minimum Fine        : " << minFine << "\n";
    cout << "Maximum Fine        : " << maxFine << "\n";
    cout << "Stack Size          : " << trafficStack.size() << "\n";
    cout << "Data Structure      : Stack (LIFO)\n";
}

// ============================================
// MAIN MENU
// ============================================

void displayMenu() {
    cout << "\n========================================\n";
    cout << "   SMART CITY - TRAFFIC MANAGEMENT\n";
    cout << "   Stack Data Structure (LIFO)\n";
    cout << "========================================\n";
    cout << "1. Add New Violation (Push)\n";
    cout << "2. Remove Latest Violation (Pop)\n";
    cout << "3. View Latest Violation (Peek)\n";
    cout << "4. Display Stack (LIFO)\n";
    cout << "5. Display All Violations\n";
    cout << "6. Display Sorted by Fine (Quick Sort)\n";
    cout << "7. Display Statistics\n";
    cout << "8. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

int main() {
    loadTrafficFromFile();
    
    int choice;
    Traffic newViolation;
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                cout << "\nEnter Violation ID: ";
                cin >> newViolation.violationId;
                cin.ignore();
                cout << "Enter Vehicle Number: ";
                getline(cin, newViolation.vehicleNumber);
                cout << "Enter Driver Name: ";
                getline(cin, newViolation.driverName);
                cout << "Enter Violation Type: ";
                getline(cin, newViolation.violationType);
                cout << "Enter Fine Amount: ";
                cin >> newViolation.fineAmount;
                pushViolation(newViolation);
                saveTrafficToFile();
                break;
                
            case 2:
                try {
                    Traffic removed = popViolation();
                    cout << "\n=== Removed Violation (Popped from Stack) ===\n";
                    cout << "Violation ID   : " << removed.violationId << "\n";
                    cout << "Vehicle Number : " << removed.vehicleNumber << "\n";
                    cout << "Driver Name    : " << removed.driverName << "\n";
                    cout << "Violation Type : " << removed.violationType << "\n";
                    cout << "Fine Amount    : " << removed.fineAmount << "\n";
                    saveTrafficToFile();
                } catch (exception& e) {
                    cout << e.what() << "\n";
                }
                break;
                
            case 3:
                try {
                    Traffic top = peekViolation();
                    cout << "\n=== Latest Violation (Top of Stack) ===\n";
                    cout << "Violation ID   : " << top.violationId << "\n";
                    cout << "Vehicle Number : " << top.vehicleNumber << "\n";
                    cout << "Driver Name    : " << top.driverName << "\n";
                    cout << "Violation Type : " << top.violationType << "\n";
                    cout << "Fine Amount    : " << top.fineAmount << "\n";
                } catch (exception& e) {
                    cout << e.what() << "\n";
                }
                break;
                
            case 4:
                displayStack();
                break;
                
            case 5:
                displayAllViolations();
                break;
                
            case 6:
                displaySortedByFine();
                break;
                
            case 7:
                displayStatistics();
                break;
                
            case 8:
                saveTrafficToFile();
                cout << "Exiting... Goodbye!\n";
                return 0;
                
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
    
    return 0;
}

