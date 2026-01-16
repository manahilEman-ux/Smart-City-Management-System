#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* ==========================
   STRUCT (Traffic Record)
========================== */
struct Traffic
{
    int violationId;
    string vehicleNumber;
    string driverName;
    string violationType;
    int fineAmount;
};

/* ==========================
   STACK IMPLEMENTATION
========================== */
Traffic stack[50];
int top = -1;

/* ==========================
   PUSH INTO STACK
========================== */
void push(Traffic t)
{
    if (top == 49)
    {
        cout << "Stack Overflow\n";
        return;
    }
    stack[++top] = t;
}

/* ==========================
   READ FILE & LOAD STACK
========================== */
void loadTrafficFromFile()
{
    ifstream file("Traffic_Record.txt");

    if (!file)
    {
        cout << "Traffic record file not found.\n";
        return;
    }

    string line;
    Traffic temp;

    while (getline(file, line))
    {

        if (line.find("Violation ID") != string::npos)
        {
            temp.violationId = stoi(line.substr(line.find(":") + 1));
        }
        else if (line.find("Vehicle Number") != string::npos)
        {
            temp.vehicleNumber = line.substr(line.find(":") + 1);
        }
        else if (line.find("Driver Name") != string::npos)
        {
            temp.driverName = line.substr(line.find(":") + 1);
        }
        else if (line.find("Violation Type") != string::npos)
        {
            temp.violationType = line.substr(line.find(":") + 1);
        }
        else if (line.find("Fine Amount") != string::npos)
        {
            temp.fineAmount = stoi(line.substr(line.find(":") + 1));
            push(temp); // COMPLETE RECORD → STACK
        }
    }

    file.close();
}

/* ==========================
   DISPLAY STACK (LIFO)
========================== */
void displayTrafficStack()
{
    if (top == -1)
    {
        cout << "No traffic violations found.\n";
        return;
    }

    cout << "\n===== TRAFFIC VIOLATIONS (LATEST FIRST) =====\n";

    for (int i = top; i >= 0; i--)
    {
        cout << "\nViolation ID   : " << stack[i].violationId;
        cout << "\nVehicle Number : " << stack[i].vehicleNumber;
        cout << "\nDriver Name    : " << stack[i].driverName;
        cout << "\nViolation Type : " << stack[i].violationType;
        cout << "\nFine Amount    : " << stack[i].fineAmount;
        cout << "\n--------------------------------------------\n";
    }
}

/* ==========================
   MAIN
========================== */
int main()
{
    loadTrafficFromFile();
    displayTrafficStack();
    return 0;
}
