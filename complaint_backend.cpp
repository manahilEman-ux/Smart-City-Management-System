#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* ==========================
   STRUCT (Complaint)
========================== */
struct Complaint
{
    int complaintId;
    string citizenName;
    string complaintType;
    string area;
    string description;
};

/* ==========================
   QUEUE IMPLEMENTATION
========================== */
Complaint queueArr[50];
int front = 0, rear = -1;

/* ==========================
   ENQUEUE
========================== */
void enqueue(Complaint c)
{
    if (rear == 49)
    {
        cout << "Queue Overflow\n";
        return;
    }
    queueArr[++rear] = c;
}

/* ==========================
   LOAD FILE → QUEUE
========================== */
void loadComplaintsFromFile()
{
    ifstream file("Complaint_Record.txt");

    if (!file)
    {
        cout << "Complaint record file not found.\n";
        return;
    }

    string line;
    Complaint temp;

    while (getline(file, line))
    {

        if (line.find("Complaint ID") != string::npos)
        {
            temp.complaintId = stoi(line.substr(line.find(":") + 1));
        }
        else if (line.find("Citizen Name") != string::npos)
        {
            temp.citizenName = line.substr(line.find(":") + 1);
        }
        else if (line.find("Complaint Type") != string::npos)
        {
            temp.complaintType = line.substr(line.find(":") + 1);
        }
        else if (line.find("Area / Location") != string::npos)
        {
            temp.area = line.substr(line.find(":") + 1);
        }
        else if (line.find("Description") != string::npos)
        {
            temp.description = line.substr(line.find(":") + 1);
            enqueue(temp); // COMPLETE RECORD → QUEUE
        }
    }

    file.close();
}

/* ==========================
   DISPLAY QUEUE (FIFO)
========================== */
void displayQueue()
{
    if (front > rear)
    {
        cout << "No complaints available.\n";
        return;
    }

    cout << "\n===== COMPLAINT QUEUE (FIRST COME FIRST SERVE) =====\n";

    for (int i = front; i <= rear; i++)
    {
        cout << "\nComplaint ID    : " << queueArr[i].complaintId;
        cout << "\nCitizen Name    : " << queueArr[i].citizenName;
        cout << "\nComplaint Type  : " << queueArr[i].complaintType;
        cout << "\nArea            : " << queueArr[i].area;
        cout << "\nDescription     : " << queueArr[i].description;
        cout << "\n-----------------------------------------------\n";
    }
}

/* ==========================
   MAIN
========================== */
int main()
{
    loadComplaintsFromFile();
    displayQueue();
    return 0;
}
