#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* ==========================
   STRUCT + LINKED LIST NODE
========================== */
struct Hospital
{
    int hospitalId;
    int patientId;
    string patientName;
    string doctorName;
    string disease;
    int billAmount;
    Hospital *next;
};

Hospital *head = NULL;

/* ==========================
   INSERT AT END (LINKED LIST)
========================== */
void insertRecord(Hospital temp)
{
    Hospital *newNode = new Hospital;
    *newNode = temp;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        Hospital *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

/* ==========================
   LOAD FILE → LINKED LIST
========================== */
void loadHospitalFromFile()
{
    ifstream file("Hospital_Record.txt");

    if (!file)
    {
        cout << "Hospital record file not found.\n";
        return;
    }

    string line;
    Hospital temp;

    while (getline(file, line))
    {

        if (line.find("Hospital ID") != string::npos)
        {
            temp.hospitalId = stoi(line.substr(line.find(":") + 1));
        }
        else if (line.find("Patient ID") != string::npos)
        {
            temp.patientId = stoi(line.substr(line.find(":") + 1));
        }
        else if (line.find("Patient Name") != string::npos)
        {
            temp.patientName = line.substr(line.find(":") + 1);
        }
        else if (line.find("Doctor Name") != string::npos)
        {
            temp.doctorName = line.substr(line.find(":") + 1);
        }
        else if (line.find("Disease") != string::npos)
        {
            temp.disease = line.substr(line.find(":") + 1);
        }
        else if (line.find("Bill Amount") != string::npos)
        {
            temp.billAmount = stoi(line.substr(line.find(":") + 1));
            insertRecord(temp); // COMPLETE RECORD → LINKED LIST
        }
    }

    file.close();
}

/* ==========================
   DISPLAY LINKED LIST
========================== */
void displayHospitalRecords()
{
    if (head == NULL)
    {
        cout << "No hospital records available.\n";
        return;
    }

    Hospital *current = head;

    cout << "\n===== HOSPITAL PATIENT RECORDS =====\n";

    while (current != NULL)
    {
        cout << "\nHospital ID   : " << current->hospitalId;
        cout << "\nPatient ID    : " << current->patientId;
        cout << "\nPatient Name  : " << current->patientName;
        cout << "\nDoctor Name   : " << current->doctorName;
        cout << "\nDisease       : " << current->disease;
        cout << "\nBill Amount   : " << current->billAmount;
        cout << "\n-----------------------------------\n";

        current = current->next;
    }
}

/* ==========================
   MAIN
========================== */
int main()
{
    loadHospitalFromFile();
    displayHospitalRecords();
    return 0;
}
