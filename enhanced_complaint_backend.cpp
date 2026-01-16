#include "data_structures.h"
#include <sstream>

// Global Data Structures
PriorityQueue complaintQueue;
queue<Complaint> standardQueue;
stack<Complaint> complaintStack;
vector<Complaint> complaintArray;

// ============================================
// FILE OPERATIONS
// ============================================

void loadComplaintsFromFile() {
    ifstream file("../SmartCity_Data/complaint.txt");
    
    if (!file) {
        cout << "Complaint file not found. Creating new file.\n";
        return;
    }
    
    string line;
    Complaint temp;
    int lineCount = 0;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        if (line.find("Complaint ID") != string::npos) {
            temp.complaintId = stoi(line.substr(line.find(":") + 2));
        } else if (line.find("Citizen Name") != string::npos) {
            temp.citizenName = line.substr(line.find(":") + 2);
        } else if (line.find("Complaint Type") != string::npos) {
            temp.complaintType = line.substr(line.find(":") + 2);
        } else if (line.find("Area") != string::npos) {
            temp.area = line.substr(line.find(":") + 2);
        } else if (line.find("Description") != string::npos) {
            temp.description = line.substr(line.find(":") + 2);
            // Assign priority based on type
            if (temp.complaintType.find("Emergency") != string::npos) {
                temp.priority = 1;
            } else if (temp.complaintType.find("Urgent") != string::npos) {
                temp.priority = 2;
            } else {
                temp.priority = 3;
            }
            
            // Insert into all data structures
            complaintQueue.enqueue(temp);
            standardQueue.push(temp);
            complaintStack.push(temp);
            complaintArray.push_back(temp);
        }
    }
    
    file.close();
    cout << "Loaded " << complaintArray.size() << " complaint records.\n";
}

void saveComplaintsToFile() {
    ofstream file("../SmartCity_Data/complaint.txt");
    
    for (const auto& complaint : complaintArray) {
        file << "Complaint ID      : " << complaint.complaintId << "\n";
        file << "Citizen Name      : " << complaint.citizenName << "\n";
        file << "Complaint Type    : " << complaint.complaintType << "\n";
        file << "Area / Location   : " << complaint.area << "\n";
        file << "Description       : " << complaint.description << "\n";
        file << "Priority          : " << complaint.priority << "\n";
        file << "----------------------------------------\n";
    }
    
    file.close();
    cout << "Saved " << complaintArray.size() << " records to file.\n";
}

// ============================================
// QUEUE OPERATIONS
// ============================================

void addComplaint(Complaint c) {
    // Assign priority
    if (c.complaintType.find("Emergency") != string::npos) {
        c.priority = 1;
    } else if (c.complaintType.find("Urgent") != string::npos) {
        c.priority = 2;
    } else {
        c.priority = 3;
    }
    
    complaintQueue.enqueue(c);
    standardQueue.push(c);
    complaintStack.push(c);
    complaintArray.push_back(c);
    
    cout << "Complaint added successfully!\n";
    saveComplaintsToFile();
}

void processNextComplaint() {
    if (complaintQueue.isEmpty()) {
        cout << "No complaints in queue!\n";
        return;
    }
    
    Complaint next = complaintQueue.dequeue();
    cout << "\n=== Processing Next Complaint (Priority Queue) ===\n";
    cout << "Complaint ID    : " << next.complaintId << "\n";
    cout << "Citizen Name    : " << next.citizenName << "\n";
    cout << "Complaint Type  : " << next.complaintType << "\n";
    cout << "Area            : " << next.area << "\n";
    cout << "Description     : " << next.description << "\n";
    cout << "Priority        : " << next.priority << "\n";
    
    // Remove from other structures
    if (!standardQueue.empty()) standardQueue.pop();
    if (!complaintStack.empty()) complaintStack.pop();
    
    complaintArray.erase(
        remove_if(complaintArray.begin(), complaintArray.end(),
            [next](Complaint c) { return c.complaintId == next.complaintId; }),
        complaintArray.end()
    );
    
    saveComplaintsToFile();
}

// ============================================
// DISPLAY OPERATIONS
// ============================================

void displayPriorityQueue() {
    if (complaintQueue.isEmpty()) {
        cout << "Priority queue is empty.\n";
        return;
    }
    
    cout << "\n=== COMPLAINT PRIORITY QUEUE (Min Heap) ===\n";
    PriorityQueue tempQueue = complaintQueue;
    int index = 1;
    
    while (!tempQueue.isEmpty()) {
        Complaint c = tempQueue.dequeue();
        cout << "\n[" << index++ << "] Priority: " << c.priority << "\n";
        cout << "Complaint ID    : " << c.complaintId << "\n";
        cout << "Citizen Name    : " << c.citizenName << "\n";
        cout << "Complaint Type  : " << c.complaintType << "\n";
        cout << "Area            : " << c.area << "\n";
        cout << "Description     : " << c.description << "\n";
        cout << "----------------------------------------\n";
    }
}

void displayStandardQueue() {
    if (standardQueue.empty()) {
        cout << "Standard queue is empty.\n";
        return;
    }
    
    cout << "\n=== COMPLAINT STANDARD QUEUE (FIFO) ===\n";
    queue<Complaint> tempQueue = standardQueue;
    int index = 1;
    
    while (!tempQueue.empty()) {
        Complaint c = tempQueue.front();
        tempQueue.pop();
        cout << "\n[" << index++ << "]\n";
        cout << "Complaint ID    : " << c.complaintId << "\n";
        cout << "Citizen Name    : " << c.citizenName << "\n";
        cout << "Complaint Type  : " << c.complaintType << "\n";
        cout << "Area            : " << c.area << "\n";
        cout << "Description     : " << c.description << "\n";
        cout << "----------------------------------------\n";
    }
}

void displayStack() {
    if (complaintStack.empty()) {
        cout << "Stack is empty.\n";
        return;
    }
    
    cout << "\n=== COMPLAINT STACK (LIFO - Latest First) ===\n";
    stack<Complaint> tempStack = complaintStack;
    int index = 1;
    
    while (!tempStack.empty()) {
        Complaint c = tempStack.top();
        tempStack.pop();
        cout << "\n[" << index++ << "]\n";
        cout << "Complaint ID    : " << c.complaintId << "\n";
        cout << "Citizen Name    : " << c.citizenName << "\n";
        cout << "Complaint Type  : " << c.complaintType << "\n";
        cout << "Area            : " << c.area << "\n";
        cout << "Description     : " << c.description << "\n";
        cout << "----------------------------------------\n";
    }
}

void displayAllComplaints() {
    if (complaintArray.empty()) {
        cout << "No complaints available.\n";
        return;
    }
    
    cout << "\n=== ALL COMPLAINTS ===\n";
    cout << setw(5) << "ID" << setw(20) << "Citizen Name" 
         << setw(20) << "Type" << setw(15) << "Area" << setw(5) << "Priority\n";
    cout << string(65, '-') << "\n";
    
    for (const auto& complaint : complaintArray) {
        cout << setw(5) << complaint.complaintId
             << setw(20) << complaint.citizenName
             << setw(20) << complaint.complaintType
             << setw(15) << complaint.area
             << setw(5) << complaint.priority << "\n";
    }
    
    cout << "\nTotal Complaints: " << complaintArray.size() << "\n";
}

// ============================================
// STATISTICS
// ============================================

void displayStatistics() {
    if (complaintArray.empty()) {
        cout << "No data available for statistics.\n";
        return;
    }
    
    int total = complaintArray.size();
    int emergency = 0, urgent = 0, normal = 0;
    
    for (const auto& complaint : complaintArray) {
        if (complaint.priority == 1) emergency++;
        else if (complaint.priority == 2) urgent++;
        else normal++;
    }
    
    cout << "\n=== COMPLAINT STATISTICS ===\n";
    cout << "Total Complaints     : " << total << "\n";
    cout << "Emergency (Priority 1): " << emergency << "\n";
    cout << "Urgent (Priority 2)   : " << urgent << "\n";
    cout << "Normal (Priority 3)   : " << normal << "\n";
    cout << "Data Structures       : Priority Queue, Queue, Stack\n";
}

// ============================================
// MAIN MENU
// ============================================

void displayMenu() {
    cout << "\n========================================\n";
    cout << "   SMART CITY - COMPLAINT MANAGEMENT\n";
    cout << "   Queue & Priority Queue System\n";
    cout << "========================================\n";
    cout << "1. Add New Complaint\n";
    cout << "2. Process Next Complaint (Priority Queue)\n";
    cout << "3. Display Priority Queue\n";
    cout << "4. Display Standard Queue (FIFO)\n";
    cout << "5. Display Stack (LIFO)\n";
    cout << "6. Display All Complaints\n";
    cout << "7. Display Statistics\n";
    cout << "8. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

int main() {
    loadComplaintsFromFile();
    
    int choice;
    Complaint newComplaint;
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                cout << "\nEnter Complaint ID: ";
                cin >> newComplaint.complaintId;
                cin.ignore();
                cout << "Enter Citizen Name: ";
                getline(cin, newComplaint.citizenName);
                cout << "Enter Complaint Type (Emergency/Urgent/Normal): ";
                getline(cin, newComplaint.complaintType);
                cout << "Enter Area/Location: ";
                getline(cin, newComplaint.area);
                cout << "Enter Description: ";
                getline(cin, newComplaint.description);
                addComplaint(newComplaint);
                break;
                
            case 2:
                processNextComplaint();
                break;
                
            case 3:
                displayPriorityQueue();
                break;
                
            case 4:
                displayStandardQueue();
                break;
                
            case 5:
                displayStack();
                break;
                
            case 6:
                displayAllComplaints();
                break;
                
            case 7:
                displayStatistics();
                break;
                
            case 8:
                saveComplaintsToFile();
                cout << "Exiting... Goodbye!\n";
                return 0;
                
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
    
    return 0;
}

