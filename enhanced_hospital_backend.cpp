#include "data_structures.h"
#include <sstream>

// Global Data Structures - Linked List
struct HospitalNode {
    Hospital data;
    HospitalNode* next;
    
    HospitalNode(Hospital h) {
        data = h;
        next = nullptr;
    }
};

HospitalNode* head = nullptr;
int hospitalCount = 0;

// ============================================
// LINKED LIST OPERATIONS
// ============================================

void insertAtBeginning(Hospital h) {
    HospitalNode* newNode = new HospitalNode(h);
    newNode->next = head;
    head = newNode;
    hospitalCount++;
}

void insertAtEnd(Hospital h) {
    HospitalNode* newNode = new HospitalNode(h);
    
    if (head == nullptr) {
        head = newNode;
    } else {
        HospitalNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    hospitalCount++;
}

void insertSorted(Hospital h) {
    HospitalNode* newNode = new HospitalNode(h);
    
    if (head == nullptr || head->data.patientId > h.patientId) {
        newNode->next = head;
        head = newNode;
        hospitalCount++;
        return;
    }
    
    HospitalNode* current = head;
    while (current->next != nullptr && current->next->data.patientId < h.patientId) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    hospitalCount++;
}

HospitalNode* searchByPatientId(int patientId) {
    HospitalNode* current = head;
    while (current != nullptr) {
        if (current->data.patientId == patientId) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void deleteByPatientId(int patientId) {
    if (head == nullptr) {
        cout << "List is empty!\n";
        return;
    }
    
    if (head->data.patientId == patientId) {
        HospitalNode* temp = head;
        head = head->next;
        delete temp;
        hospitalCount--;
        cout << "Record deleted successfully!\n";
        return;
    }
    
    HospitalNode* current = head;
    while (current->next != nullptr && current->next->data.patientId != patientId) {
        current = current->next;
    }
    
    if (current->next != nullptr) {
        HospitalNode* temp = current->next;
        current->next = current->next->next;
        delete temp;
        hospitalCount--;
        cout << "Record deleted successfully!\n";
    } else {
        cout << "Patient ID not found!\n";
    }
}

// ============================================
// FILE OPERATIONS
// ============================================

void loadHospitalFromFile() {
    ifstream file("../SmartCity_Data/hospital.txt");
    
    if (!file) {
        cout << "Hospital file not found. Creating new file.\n";
        return;
    }
    
    string line;
    Hospital temp;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        if (line.find("Hospital ID") != string::npos) {
            temp.hospitalId = stoi(line.substr(line.find(":") + 2));
        } else if (line.find("Patient ID") != string::npos) {
            temp.patientId = stoi(line.substr(line.find(":") + 2));
        } else if (line.find("Patient Name") != string::npos) {
            temp.patientName = line.substr(line.find(":") + 2);
        } else if (line.find("Doctor Name") != string::npos) {
            temp.doctorName = line.substr(line.find(":") + 2);
        } else if (line.find("Disease") != string::npos) {
            temp.disease = line.substr(line.find(":") + 2);
        } else if (line.find("Bill Amount") != string::npos) {
            temp.billAmount = stoi(line.substr(line.find(":") + 2));
            insertSorted(temp); // Insert in sorted order
        }
    }
    
    file.close();
    cout << "Loaded " << hospitalCount << " hospital records.\n";
}

void saveHospitalToFile() {
    ofstream file("../SmartCity_Data/hospital.txt");
    
    HospitalNode* current = head;
    while (current != nullptr) {
        file << "Hospital ID   : " << current->data.hospitalId << "\n";
        file << "Patient ID    : " << current->data.patientId << "\n";
        file << "Patient Name  : " << current->data.patientName << "\n";
        file << "Doctor Name   : " << current->data.doctorName << "\n";
        file << "Disease       : " << current->data.disease << "\n";
        file << "Bill Amount   : " << current->data.billAmount << "\n";
        file << "----------------------------------------\n";
        current = current->next;
    }
    
    file.close();
    cout << "Saved " << hospitalCount << " records to file.\n";
}

// ============================================
// DISPLAY OPERATIONS
// ============================================

void displayAllRecords() {
    if (head == nullptr) {
        cout << "No hospital records available.\n";
        return;
    }
    
    cout << "\n=== HOSPITAL PATIENT RECORDS (Linked List) ===\n";
    cout << setw(5) << "HID" << setw(5) << "PID" << setw(20) << "Patient Name"
         << setw(20) << "Doctor Name" << setw(20) << "Disease" << setw(12) << "Bill\n";
    cout << string(82, '-') << "\n";
    
    HospitalNode* current = head;
    int index = 1;
    
    while (current != nullptr) {
        cout << setw(5) << current->data.hospitalId
             << setw(5) << current->data.patientId
             << setw(20) << current->data.patientName
             << setw(20) << current->data.doctorName
             << setw(20) << current->data.disease
             << setw(12) << current->data.billAmount << "\n";
        current = current->next;
        index++;
    }
    
    cout << "\nTotal Records: " << hospitalCount << "\n";
}

void displayReverse() {
    if (head == nullptr) {
        cout << "List is empty!\n";
        return;
    }
    
    stack<Hospital> tempStack;
    HospitalNode* current = head;
    
    while (current != nullptr) {
        tempStack.push(current->data);
        current = current->next;
    }
    
    cout << "\n=== HOSPITAL RECORDS (Reversed using Stack) ===\n";
    int index = 1;
    while (!tempStack.empty()) {
        Hospital h = tempStack.top();
        tempStack.pop();
        cout << "\n[" << index++ << "]\n";
        cout << "Hospital ID   : " << h.hospitalId << "\n";
        cout << "Patient ID    : " << h.patientId << "\n";
        cout << "Patient Name  : " << h.patientName << "\n";
        cout << "Doctor Name   : " << h.doctorName << "\n";
        cout << "Disease       : " << h.disease << "\n";
        cout << "Bill Amount   : " << h.billAmount << "\n";
        cout << "----------------------------------------\n";
    }
}

// ============================================
// STATISTICS
// ============================================

void displayStatistics() {
    if (head == nullptr) {
        cout << "No data available for statistics.\n";
        return;
    }
    
    int totalBill = 0;
    int minBill = INT_MAX, maxBill = 0;
    int recordCount = 0;
    
    HospitalNode* current = head;
    while (current != nullptr) {
        totalBill += current->data.billAmount;
        minBill = min(minBill, current->data.billAmount);
        maxBill = max(maxBill, current->data.billAmount);
        recordCount++;
        current = current->next;
    }
    
    double avgBill = (double)totalBill / recordCount;
    
    cout << "\n=== HOSPITAL STATISTICS ===\n";
    cout << "Total Records      : " << recordCount << "\n";
    cout << "Total Bill Amount  : " << totalBill << "\n";
    cout << "Average Bill       : " << fixed << setprecision(2) << avgBill << "\n";
    cout << "Minimum Bill       : " << minBill << "\n";
    cout << "Maximum Bill       : " << maxBill << "\n";
    cout << "Data Structure     : Singly Linked List\n";
}

// ============================================
// MAIN MENU
// ============================================

void displayMenu() {
    cout << "\n========================================\n";
    cout << "   SMART CITY - HOSPITAL MANAGEMENT\n";
    cout << "   Linked List Data Structure\n";
    cout << "========================================\n";
    cout << "1. Add New Patient Record\n";
    cout << "2. Search Patient by ID\n";
    cout << "3. Delete Patient Record\n";
    cout << "4. Display All Records\n";
    cout << "5. Display Records (Reversed)\n";
    cout << "6. Display Statistics\n";
    cout << "7. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

int main() {
    loadHospitalFromFile();
    
    int choice;
    Hospital newHospital;
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                cout << "\nEnter Hospital ID: ";
                cin >> newHospital.hospitalId;
                cout << "Enter Patient ID: ";
                cin >> newHospital.patientId;
                cin.ignore();
                cout << "Enter Patient Name: ";
                getline(cin, newHospital.patientName);
                cout << "Enter Doctor Name: ";
                getline(cin, newHospital.doctorName);
                cout << "Enter Disease: ";
                getline(cin, newHospital.disease);
                cout << "Enter Bill Amount: ";
                cin >> newHospital.billAmount;
                insertSorted(newHospital);
                saveHospitalToFile();
                cout << "Record added successfully!\n";
                break;
                
            case 2:
                cout << "\nEnter Patient ID to search: ";
                cin >> choice;
                {
                    HospitalNode* found = searchByPatientId(choice);
                    if (found != nullptr) {
                        cout << "\n=== Patient Found ===\n";
                        cout << "Hospital ID   : " << found->data.hospitalId << "\n";
                        cout << "Patient ID    : " << found->data.patientId << "\n";
                        cout << "Patient Name  : " << found->data.patientName << "\n";
                        cout << "Doctor Name   : " << found->data.doctorName << "\n";
                        cout << "Disease       : " << found->data.disease << "\n";
                        cout << "Bill Amount   : " << found->data.billAmount << "\n";
                    } else {
                        cout << "Patient ID not found!\n";
                    }
                }
                break;
                
            case 3:
                cout << "\nEnter Patient ID to delete: ";
                cin >> choice;
                deleteByPatientId(choice);
                saveHospitalToFile();
                break;
                
            case 4:
                displayAllRecords();
                break;
                
            case 5:
                displayReverse();
                break;
                
            case 6:
                displayStatistics();
                break;
                
            case 7:
                saveHospitalToFile();
                cout << "Exiting... Goodbye!\n";
                return 0;
                
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
    
    return 0;
}

