#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

void adminLogin(), staffLogin(), employeeLogin(), userAuthentication();
void employeeRec(), addEmployee(), updateEmployee(), viewEmployee(), deleteEmployee();
void clrscrn();

struct Employee {
    int id;
    string fullName;
    string cityAddr;
    string department;
    string position;
    double rate;
};

Employee employees[100];
int employeeCount = 0;

int main() {
    userAuthentication();
    return 0;
}

void employeeRec() {
    cout << "\n\t----- Employee Records Management ------" << endl;
    cout << "\n\t[1] Add Employee" << endl;
    cout << "\t[2] Update Employee" << endl;
    cout << "\t[3] View Employee" << endl;
    cout << "\t[4] Delete Employee" << endl;
    cout << "\t[0] Back" << endl;
    cout << "\n\tChoice: ";
    char choice;
    cin >> choice;

    clrscrn();

    switch(choice) {
        case '1':
            addEmployee();
            break;
        case '2':
            updateEmployee();
            break;
        case '3':
            viewEmployee();
            break;
        case '4':
            deleteEmployee();
            break;
        case '0':
            adminLogin();
            break;
        default:
            cout << "\n\tInvalid Choice! Please Try Again." << endl;
            employeeRec();
            break;
    }
}

void addEmployee() {
    ofstream file("employees.txt", ios::app);
    cout << "\n\t----- Add New Employee ------" << endl;
    Employee newEmp;
    cout << "\n\tEnter Employee ID: ";
    cin >> newEmp.id;

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == newEmp.id) {
            cout << "\n\tEmployee ID already exists! Please try again." << endl;
            employeeRec();
            return;
        }
    }

    cout << "\n\tEnter Full Name: ";
    cin.ignore();
    getline(cin, newEmp.fullName);
    cout << "\n\tEnter City Address: ";
    getline(cin, newEmp.cityAddr);
    cout << "\n\tEnter Department: ";
    getline(cin, newEmp.department);
    cout << "\n\tEnter Position: ";
    getline(cin, newEmp.position);
    cout << "\n\tEnter Rate: ";
    cin >> newEmp.rate;

    employees[employeeCount] = newEmp;
    employeeCount++;

    cout << "\n\tEmployee Added Successfully!" << endl;

    file << employeeCount << endl;
    for (int i = 0; i < employeeCount; i++) {
        file << employees[i].id << endl;
        file << employees[i].fullName << endl;
        file << employees[i].cityAddr << endl;
        file << employees[i].department << endl;
        file << employees[i].position << endl;
        file << employees[i].rate << endl;
        file.close();
    }
    

    employeeRec();
}

void updateEmployee() {

}

void viewEmployee() {

}

void deleteEmployee() {

}

void adminLogin() {
    cout << "\n\t----- Admin Dashboard ------" << endl;
    cout << "\n\t[1] Manage Employee Records" << endl;
    cout << "\t[2] Manage Staff Accounts" << endl;
    cout << "\t[3] Payroll Reports" << endl;
    cout << "\t[0] Logout" << endl;
    cout << "\n\tChoice: ";
    char choice;
    cin >> choice;

    clrscrn();

    switch(choice) {
        case '1':
            employeeRec();
            break;
        case '2':
            
            break;
        case '3':
            
            break;
        case '0':
            char confirm;
            while(true) {
                cout << "\n\tAre you sure you want to logout? (y/n): ";
                cin >> confirm;
                if(confirm == 'y' || confirm == 'Y') {
                    cout << "\n\tLogging out..." << endl;
                    userAuthentication();
                    break;
                } else if(confirm == 'n' || confirm == 'N') {
                    adminLogin();
                    break;
                } else {
                    cout << "\n\tInvalid input! Please Try Again." << endl;
                }
            }
            break;
        default:
            cout << "\n\tInvalid Choice! Please Try Again." << endl;
            adminLogin();
            break;
    }
}

void staffLogin() {

}

void employeeLogin() {

}


void userAuthentication() {
    int attempt = 3;
    while(attempt != 0) {
        string username, password;

        cout << "\n\t----- Login Dashboard ------" << endl;
        cout << "\n\tEnter Username: ";
        cin >> username;
        cout << "\n\tEnter Password: ";
        cin >> password;

        clrscrn();

        if(username == "admin" && password == "admin123") {
            cout << "\n\tLogin Successful! Welcome Admin." << endl;
            adminLogin();
            break;
        } else if(username == "staff" && password == "staff123") {
            cout << "\n\tLogin Successful! Welcome Staff." << endl;
            staffLogin();
            break;
        } else if(username == "employee" && password == "emp123") {
            cout << "\n\tLogin Successful! Welcome Employee." << endl;
            employeeLogin();
            break;
        } else {
            cout << "\n\tInvalid Credentials! Please try again." << endl;
            attempt--;
            cout << "\n\tRemaining Attempts: " << attempt << endl;
        }
    }

}

void clrscrn() {
    system("clear");
}