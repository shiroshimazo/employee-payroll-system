#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

void adminMenu(), staffMenu(), employeeMenu(), userAuthentication();
void readDataEmployees(), employeeRec(), addEmployee(), updateEmployee(), viewEmployee(), deleteEmployee();
void readDataStaffs(), staffsRec(), addStaff(), updateStaff(), viewStaff(), deleteStaff();
void clrscrn();

struct Employee {
    int id;
    string fullName;
    string cityAddr;
    string department;
    string position;
    double rate;
};

struct Staff {
    int id;
    string username;
    string password;
    string fullName;
    string cityAddr;
    string role;
    double rate;
};

Employee employees[100];
Staff staffs[100];
int employeeCount = 0;
int staffCount = 0;

int main() {
    userAuthentication();
    return 0;
}

void readDataEmployees() {
    ifstream readEmp("employees.txt");
    employeeCount = 0;
    string line;
    while(getline(readEmp, line)) {
        employees[employeeCount].id = stoi(line);
        getline(readEmp, employees[employeeCount].fullName);
        getline(readEmp, employees[employeeCount].cityAddr);
        getline(readEmp, employees[employeeCount].department);
        getline(readEmp, employees[employeeCount].position);
        getline(readEmp, line);
        employees[employeeCount].rate = stod(line);
        employeeCount++;
    }
    readEmp.close(); 
}

void readDataStaff() {
    ifstream readStaff("staffs.txt");
    staffCount = 0;
    string line;
    while (getline(readStaff, line)) {
        staffs[staffCount].id = stoi(line);
        getline(readStaff, staffs[staffCount].username);
        getline(readStaff, staffs[staffCount].password);
        getline(readStaff, staffs[staffCount].fullName);
        getline(readStaff, staffs[staffCount].cityAddr);
        getline(readStaff, staffs[staffCount].role);
        getline(readStaff, line);
        staffs[staffCount].rate = stod(line);
        staffCount++;
    }
    readStaff.close();
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

    switch (choice) {
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
            adminMenu();
            break;
        default:
            cout << "\n\tInvalid Choice! Please Try Again." << endl;
            employeeRec();
            break;
    }
}

void addEmployee() {
    readDataEmployees();
    fstream empRec;
    empRec.open("employees.txt", ios::app);
    bool idExists;
    cout << "\n\t----- Add New Employee ------" << endl;
    Employee newEmp;

    do {
        idExists = false;
        cout << "\n\tEnter Employee ID: ";
        cin >> newEmp.id;

        for (int i = 0; i < employeeCount; i++) {
            if (employees[i].id == newEmp.id) {
                cout << "\n\tEmployee ID already exists! Please try again." << endl;
                idExists = true;
                break;
            }
        }
    } while (idExists);

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

    empRec << newEmp.id << endl;
    empRec << newEmp.fullName << endl;
    empRec << newEmp.cityAddr << endl;
    empRec << newEmp.department << endl;
    empRec << newEmp.position << endl;
    empRec << newEmp.rate << endl;
    empRec.close();
    employeeRec();
}

void updateEmployee() {
    cout << "\n\t----- Update Employee ------" << endl;
    readDataEmployees();
    int updId;
    cout << "\n\tEnter Employee ID to Update: ";
    cin >> updId;
    clrscrn();
    bool found = false;
    int idx = -1;
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == updId) {
            found = true;
            idx = i;
            break;
        }
    }
    if (!found) {
        cout << "\n\tEmployee ID not found!" << endl;
        employeeRec();
        return;
    }
    cout << "\n\tEmployee to Update:" << endl;
    cout << "\n\t+-----+---------------+---------------+--------------------+---------------+--------+" << endl;
    cout << "\t| " << left << setw(3) << "ID" << " | " << setw(13) << "Name" << " | " << setw(13) << "City" << " | " << setw(18) << "Department" << " | " << setw(13) << "Position" << " | " << setw(6) << "Rate" << " |" << endl;
    cout << "\t+-----+---------------+---------------+--------------------+---------------+--------+" << endl;
    cout << "\t| " << left << setw(3) << employees[idx].id << " | " << setw(13) << employees[idx].fullName << " | " << setw(13) << employees[idx].cityAddr << " | " << setw(18) << employees[idx].department << " | " << setw(13) << employees[idx].position << " | " << setw(6) << fixed << setprecision(2) << employees[idx].rate << " |" << endl;
    cout << "\t+-----+---------------+---------------+--------------------+---------------+--------+" << endl;
    cout << "\n\tWhat do you want to change?" << endl;
    cout << "\t[1] Change Name" << endl;
    cout << "\t[2] Change City" << endl;
    cout << "\t[3] Change Department" << endl;
    cout << "\t[4] Change Position" << endl;
    cout << "\t[5] Change Rate" << endl;
    cout << "\tChoice: ";
    char choice;
    cin >> choice;
    clrscrn();
    switch (choice) {
        case '1': {
            cout << "\n\tEnter new Name: ";
            cin.ignore();
            getline(cin, employees[idx].fullName);
            cout << "\n\tName updated successfully!" << endl;
            break;
        }
        case '2': {
            cout << "\n\tEnter new City: ";
            cin.ignore();
            getline(cin, employees[idx].cityAddr);
            cout << "\n\tCity updated successfully!" << endl;
            break;
        }
        case '3': {
            cout << "\n\tEnter new Department: ";
            cin.ignore();
            getline(cin, employees[idx].department);
            cout << "\n\tDepartment updated successfully!" << endl;
            break;
        }
        case '4': {
            cout << "\n\tEnter new Position: ";
            cin.ignore();
            getline(cin, employees[idx].position);
            cout << "\n\tPosition updated successfully!" << endl;
            break;
        }
        case '5': {
            cout << "\n\tEnter new Rate: ";
            cin >> employees[idx].rate;
            cout << "\n\tRate updated successfully!" << endl;
            break;
        }
        default:
            cout << "\n\tInvalid Choice! Please Try Again." << endl;
            employeeRec();
            return;
    }
    ofstream outRec("employees.txt");
    for (int i = 0; i < employeeCount; i++) {
        outRec << employees[i].id << endl;
        outRec << employees[i].fullName << endl;
        outRec << employees[i].cityAddr << endl;
        outRec << employees[i].department << endl;
        outRec << employees[i].position << endl;
        outRec << employees[i].rate << endl;
    }
    
    outRec.close();
    cout << "\n\tUpdated Employee Data:" << endl;
    cout << "\n\t+-----+---------------+---------------+--------------------+---------------+--------+" << endl;
    cout << "\t| " << left << setw(3) << "ID" << " | " << setw(13) << "Name" << " | " << setw(13) << "City" << " | " << setw(18) << "Department" << " | " << setw(13) << "Position" << " | " << setw(6) << "Rate" << " |" << endl;
    cout << "\t+-----+---------------+---------------+--------------------+---------------+--------+" << endl;
    cout << "\t| " << left << setw(3) << employees[idx].id << " | " << setw(13) << employees[idx].fullName << " | " << setw(13) << employees[idx].cityAddr << " | " << setw(18) << employees[idx].department << " | " << setw(13) << employees[idx].position << " | " << setw(6) << fixed << setprecision(2) << employees[idx].rate << " |" << endl;
    cout << "\t+-----+---------------+---------------+--------------------+---------------+--------+" << endl;
    employeeRec();
}

void viewEmployee() {
    readDataEmployees();
    char choice;
    cout << "\n\t----- View Employee ------" << endl;
    cout << "\n\t[1] View All Employees" << endl;
    cout << "\t[2] Search Employee by ID" << endl;
    cout << "\t[0] Back" << endl;
    cout << "\n\tChoice: ";
    cin >> choice;
    clrscrn();
    
    switch(choice) {
        case '1':
            cout << "\n\t----- All Employees ------" << endl;
            if (employeeCount == 0) {
                cout << "\n\tNo employees found!" << endl;
            } else {
                cout << "\n\t+-----+---------------+---------------+--------------------+---------------+--------+" << endl;
                cout << "\t| " << left << setw(3) << "ID" << " | " << setw(13) << "Name" << " | " << setw(13) << "City" << " | " << setw(18) << "Department" << " | " << setw(13) << "Position" << " | " << setw(6) << "Rate" << " |" << endl;
                cout << "\t+-----+---------------+---------------+--------------------+---------------+--------+" << endl;
                for (int i = 0; i < employeeCount; i++) {
                    cout << "\t| " << left << setw(3) << employees[i].id << " | " << setw(13) << employees[i].fullName << " | " << setw(13) << employees[i].cityAddr << " | " << setw(18) << employees[i].department << " | " << setw(13) << employees[i].position << " | " << setw(6) << fixed << setprecision(2) << employees[i].rate << " |" << endl;
                }
                cout << "\t+-----+---------------+---------------+--------------------+---------------+--------+" << endl;
            }
            viewEmployee();
            break;
        case '2':
            int searchId;
            cout << "\n\tEnter Employee ID to Search: ";
            cin >> searchId;
            clrscrn();
            {
                bool found = false;
                for (int i = 0; i < employeeCount; i++) {
                    if (employees[i].id == searchId) {
                        cout << "\n\t----- Employee Details ------" << endl;
                        cout << "\n\t+-----+---------------+---------------+--------------------+---------------+--------+" << endl;
                        cout << "\t| " << left << setw(3) << "ID" << " | " << setw(13) << "Name" << " | " << setw(13) << "City" << " | " << setw(18) << "Department" << " | " << setw(13) << "Position" << " | " << setw(6) << "Rate" << " |" << endl;
                        cout << "\t+-----+---------------+---------------+--------------------+---------------+--------+" << endl;
                        cout << "\t| " << left << setw(3) << employees[i].id << " | " << setw(13) << employees[i].fullName << " | " << setw(13) << employees[i].cityAddr << " | " << setw(18) << employees[i].department << " | " << setw(13) << employees[i].position << " | " << setw(6) << fixed << setprecision(2) << employees[i].rate << " |" << endl;
                        cout << "\t+-----+---------------+---------------+--------------------+---------------+--------+" << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "\n\tEmployee ID not found!" << endl;
                }
            }
            viewEmployee();
            break;
        case '0':
            employeeRec();
            break;
        default:
            cout << "\n\tInvalid Choice! Please Try Again." << endl;
            viewEmployee();
            break;
    }
}

void deleteEmployee() {
    cout << "\n\t----- Delete Employee ------" << endl;
    readDataEmployees();
    int delId;
    cout << "\n\tEnter Employee ID to Delete: ";
    cin >> delId;
    clrscrn();
    bool found = false;
    int idx = -1;
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == delId) {
            found = true;
            idx = i;
            break;
        }
    }
    if (!found) {
        cout << "\n\tEmployee ID not found!" << endl;
        employeeRec();
        return;
    }
    cout << "\n\tEmployee to Delete:" << endl;
    cout << "\n\t+-----+---------------+---------------+--------------------+---------------+--------+" << endl;
    cout << "\t| " << left << setw(3) << "ID" << " | " << setw(13) << "Name" << " | " << setw(13) << "City" << " | " << setw(18) << "Department" << " | " << setw(13) << "Position" << " | " << setw(6) << "Rate" << " |" << endl;
    cout << "\t+-----+---------------+---------------+--------------------+---------------+--------+" << endl;
    cout << "\t| " << left << setw(3) << employees[idx].id << " | " << setw(13) << employees[idx].fullName << " | " << setw(13) << employees[idx].cityAddr << " | " << setw(18) << employees[idx].department << " | " << setw(13) << employees[idx].position << " | " << setw(6) << fixed << setprecision(2) << employees[idx].rate << " |" << endl;
    cout << "\t+-----+---------------+---------------+--------------------+---------------+--------+" << endl;
    cout << "\n\tAre you sure?" << endl;
    cout << "\t[1] Delete Row of Data" << endl;
    cout << "\t[2] Cancel" << endl;
    cout << "\tChoice: ";
    char choice;
    cin >> choice;
    clrscrn();
    if (choice == '1') {
        for (int i = idx; i < employeeCount - 1; i++) {
            employees[i] = employees[i + 1];
        }
        employeeCount--;
        ofstream outRec("employees.txt");
        for (int i = 0; i < employeeCount; i++) {
            outRec << employees[i].id << endl;
            outRec << employees[i].fullName << endl;
            outRec << employees[i].cityAddr << endl;
            outRec << employees[i].department << endl;
            outRec << employees[i].position << endl;
            outRec << employees[i].rate << endl;
        }
        outRec.close();
        cout << "\n\tEmployee deleted successfully!" << endl;
    } else {
        cout << "\n\tDeletion cancelled." << endl;
    }
    employeeRec();
}

void staffsRec() {
    cout << "\n\t----- Staff Records Management ------" << endl;
    cout << "\n\t[1] Add Staff" << endl;
    cout << "\t[2] Update Staff" << endl;
    cout << "\t[3] View Staff" << endl;
    cout << "\t[4] Delete Staff" << endl;
    cout << "\t[0] Back" << endl;
    cout << "\n\tChoice: ";
    char choice;
    cin >> choice;

    clrscrn();

    switch(choice) {
        case '1':
            addStaff();
            break;
        case '2':
            updateStaff();
            break;
        case '3':
            viewStaff();
            break;
        case '4':
            deleteStaff();
            break;
        case '0':
            adminMenu();
            break;
        default:
            cout << "\n\tInvalid Choice! Please Try Again." << endl;
            staffsRec();
            break;
    }
}

void addStaff() {
    readDataStaff();
    fstream staffRec;
    staffRec.open("staffs.txt", ios::app);
    bool idExists;
    cout << "\n\t----- Add New Staff ------" << endl;
    Staff newStaff;
    do {
        idExists = false;
        cout << "\n\tEnter Staff ID: ";
        cin >> newStaff.id;

        for (int i = 0; i < staffCount; i++) {
            if (staffs[i].id == newStaff.id) {
                cout << "\n\tStaff ID already exists! Please try again." << endl;
                idExists = true;
                break;
            }
        }
    } while (idExists);

    cout << "\n\tEnter Username: ";
    cin.ignore();
    getline(cin, newStaff.username);
    cout << "\n\tEnter Password: ";
    getline(cin, newStaff.password);
    cout << "\n\tEnter Full Name: ";
    getline(cin, newStaff.fullName);
    cout << "\n\tEnter City Address: ";
    getline(cin, newStaff.cityAddr);
    cout << "\n\tEnter Role: ";
    getline(cin, newStaff.role);
    cout << "\n\tEnter Rate: ";
    cin >> newStaff.rate;

    staffs[staffCount] = newStaff;
    staffCount++;

    cout << "\n\tEmployee Added Successfully!" << endl;

    staffRec << newStaff.id << endl;
    staffRec << newStaff.username << endl;
    staffRec << newStaff.password << endl;
    staffRec << newStaff.fullName << endl;
    staffRec << newStaff.cityAddr << endl;
    staffRec << newStaff.role << endl;
    staffRec << newStaff.rate << endl;
    staffRec.close();
    staffsRec();
}

void viewStaff() {
    readDataStaff();
    char choice;
    cout << "\n\t----- View Staff ------" << endl;
    cout << "\n\t[1] View All Staffs" << endl;
    cout << "\t[2] Search Staffs by ID" << endl;
    cout << "\t[0] Back" << endl;
    cout << "\n\tChoice: ";
    cin >> choice;
    clrscrn();
    
    switch(choice) {
        case '1':
            cout << "\n\t----- All Staffs ------" << endl;
            if (staffCount == 0) {
                cout << "\n\tNo staffs found!" << endl;
            } else {
                cout << "\n\t+-----+---------------+---------------+----------------------+---------------+------------+--------+" << endl;
                cout << "\t| " << left << setw(3) << "ID" << " | " << setw(13) << "Username" << " | " << setw(13) << "Password" << " | " << setw(20) << "Full Name" << " | " << setw(13) << "City" << " | " << setw(10) << "Role" << " | " << setw(6) << "Rate" << " |" << endl;
                cout << "\t+-----+---------------+---------------+----------------------+---------------+------------+--------+" << endl;
                for (int i = 0; i < staffCount; i++) {
                    cout << "\t| " << left << setw(3) << staffs[i].id << " | " << setw(13) << staffs[i].username << " | " << setw(13) << staffs[i].password << " | " << setw(20) << staffs[i].fullName << " | " << setw(13) << staffs[i].cityAddr << " | " << setw(10) << staffs[i].role << " | " << setw(6) << fixed << setprecision(2) << staffs[i].rate << " |" << endl;
                }
                cout << "\t+-----+---------------+---------------+----------------------+---------------+------------+--------+" << endl;
            }
            viewStaff();
            break;
        case '2':
            int searchId;
            cout << "\n\tEnter Staff ID to Search: ";
            cin >> searchId;
            clrscrn();
            {
                bool found = false;
                for (int i = 0; i < staffCount; i++) {
                    if (staffs[i].id == searchId) {
                        cout << "\n\t----- Staff Details ------" << endl;
                        cout << "\n\t+-----+---------------+---------------+----------------------+---------------+-----------------+--------+" << endl;
                        cout << "\t| " << left << setw(3) << "ID" << " | " << setw(13) << "Username" << " | " << setw(13) << "Password" << " | " << setw(20) << "Full Name" << " | " << setw(13) << "City" << " | " << setw(15) << "Role" << " | " << setw(6) << "Rate" << " |" << endl;
                        cout << "\t+-----+---------------+---------------+----------------------+---------------+-----------------+--------+" << endl;
                        cout << "\t| " << left << setw(3) << staffs[i].id << " | " << setw(13) << staffs[i].username << " | " << setw(13) << staffs[i].password << " | " << setw(20) << staffs[i].fullName << " | " << setw(13) << staffs[i].cityAddr << " | " << setw(15) << staffs[i].role << " | " << setw(6) << fixed << setprecision(2) << staffs[i].rate << " |" << endl;
                        cout << "\t+-----+---------------+---------------+----------------------+---------------+-----------------+--------+" << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "\n\tStaff ID not found!" << endl;
                }
            }
            viewStaff();
            break;
        case '0':
            staffsRec();
            break;
        default:
            cout << "\n\tInvalid Choice! Please Try Again." << endl;
            viewStaff();
            break;
    }
}

void updateStaff() {
    cout << "\n\t----- Update Staff ------" << endl;
    readDataStaff();
    int updId;
    cout << "\n\tEnter Staff ID to Update: ";
    cin >> updId;
    clrscrn();
    bool found = false;
    int idx = -1;
    for (int i = 0; i < staffCount; i++) {
        if (staffs[i].id == updId) {
            found = true;
            idx = i;
            break;
        }
    }
    if (!found) {
        cout << "\n\tStaff ID not found!" << endl;
        updateStaff();
        return;
    }
    bool showError = false;
    while (true) {
        clrscrn();
        cout << "\n\tEmployee to Update:" << endl;
        cout << "\n\t+-----+---------------+---------------+----------------------+---------------+-----------------+--------+" << endl;
        cout << "\t| " << left << setw(3) << "ID" << " | " << setw(13) << "Username" << " | " << setw(13) << "Password" << " | " << setw(20) << "Full Name" << " | " << setw(13) << "City" << " | " << setw(15) << "Role" << " | " << setw(6) << "Rate" << " |" << endl;
        cout << "\t+-----+---------------+---------------+----------------------+---------------+-----------------+--------+" << endl;
        cout << "\t| " << left << setw(3) << staffs[idx].id << " | " << setw(13) << staffs[idx].username << " | " << setw(13) << staffs[idx].password << " | " << setw(20) << staffs[idx].fullName << " | " << setw(13) << staffs[idx].cityAddr << " | " << setw(15) << staffs[idx].role << " | " << setw(6) << fixed << setprecision(2) << staffs[idx].rate << " |" << endl;
        cout << "\t+-----+---------------+---------------+----------------------+---------------+-----------------+--------+" << endl;
        if (showError) {
            cout << "\n\t>> Invalid Choice! Please Try Again." << endl;
            showError = false;
        }
        cout << "\n\tWhat do you want to change?" << endl;
        cout << "\t[1] change Username" << endl;
        cout << "\t[2] change Password" << endl;
        cout << "\t[3] change Full Name" << endl;
        cout << "\t[4] change City" << endl;
        cout << "\t[5] change Role" << endl;
        cout << "\t[6] change Rate" << endl;
        cout << "\t[0] Back" << endl;
        cout << "\n\tChoice: ";
        char choice;
        cin >> choice;

        bool validUpdate = false;

        switch(choice) {
            case '1':
                cout << "\n\tEnter New Username: ";
                cin >> staffs[idx].username;
                cout << "\n\tUsername updated successfully!" << endl;
                validUpdate = true;
                break;
            case '2':
                cout << "\n\tEnter New Password: ";
                cin >> staffs[idx].password;
                cout << "\n\tPassword updated successfully!" << endl;
                validUpdate = true;
                break;
            case '3':
                cout << "\n\tEnter New Full Name: ";
                cin.ignore();
                getline(cin, staffs[idx].fullName); 
                cout << "\n\tFull Name updated successfully!" << endl;
                validUpdate = true;
                break;
            case '4':
                cout << "\n\tEnter New City: ";
                cin.ignore();
                getline(cin, staffs[idx].cityAddr);
                cout << "\n\tCity updated successfully!" << endl;
                validUpdate = true;
                break;
            case '5':
                cout << "\n\tEnter New Role: ";
                cin.ignore();
                getline(cin, staffs[idx].role);
                cout << "\n\tRole updated successfully!" << endl;
                validUpdate = true;
                break;
            case '6':
                cout << "\n\tEnter New Rate: ";
                cin >> staffs[idx].rate;
                cout << "\n\tRate updated successfully!" << endl;
                validUpdate = true;
                break;
            case '0':
                clrscrn();
                staffsRec();
                return;
            default:
                // Kapag mali, set lang natin yung error flag to true
                showError = true;
                // Hindi na kailangan ng pause o cin.ignore dito kung char ang input
                // Babalik siya sa taas ng loop -> mag ki-clear screen -> re-print table -> print error
                continue; 
        }

        if(validUpdate) {
            break; // Break loop to save data
        }
    }
    ofstream outStaff("staffs.txt");
    for(int i = 0; i < staffCount; i++) {
        outStaff << staffs[i].id << "\n";
        outStaff << staffs[i].username << "\n";
        outStaff << staffs[i].password << "\n";
        outStaff << staffs[i].fullName << "\n";
        outStaff << staffs[i].cityAddr << "\n";
        outStaff << staffs[i].role << "\n";
        outStaff << staffs[i].rate << "\n";
    }

    outStaff.close();
    cout << "\n\tUpdated Staff Data:" << endl;
    cout << "\n\t+-----+---------------+---------------+----------------------+---------------+--------+" << endl;
    cout << "\t| " << left << setw(3) << "ID" << " | " << setw(13) << "Name" << " | " << setw(13) << "City" << " | " << setw(20) << "Role" << " | " << setw(6) << "Rate" << " |" << endl;
    cout << "\t+-----+---------------+---------------+--------------------+---------------+--------+" << endl;
    cout << "\t| " << left << setw(3) << staffs[idx].id << " | " << setw(13) << staffs[idx].fullName << " | " << setw(13) << staffs[idx].cityAddr << " | " << setw(20) << staffs[idx].role << " | " << setw(6) << fixed << setprecision(2) << staffs[idx].rate << " |" << endl;
    cout << "\t+-----+---------------+---------------+--------------------+---------------+--------+" << endl;
    updateStaff();
}

void deleteStaff() {
    
}

void adminMenu() {
    cout << "\n\t+--------------------------------+\n";
    cout << "\t|  A D M I N   D A S H B O A R D |\n";
    cout << "\t+--------------------------------+\n";
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
            staffsRec();
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
                    adminMenu();
                    break;
                } else {
                    cout << "\n\tInvalid input! Please Try Again." << endl;
                }
            }
            break;
        default:
            cout << "\n\tInvalid Choice! Please Try Again." << endl;
            adminMenu();
            break;
    }
}

void staffMenu() {

}

void employeeMenu() {

}


void userAuthentication() {
    int attempt = 3;
    while(attempt != 0) {
        string username, password;

        cout << "\n\t------------------------------\n";
        cout << "\t|    L O G I N   P A N E L   |\n";
        cout << "\t------------------------------\n";

        cout << "\n\tEnter Username: ";
        cin >> username;
        cout << "\n\tEnter Password: ";
        cin >> password;

        clrscrn();

        if(username == "admin" && password == "admin123") {
            cout << "\n\tLogin Successful! Welcome Admin." << endl;
            adminMenu();
            break;
        } else if(username == "staff" && password == "staff123") {
            cout << "\n\tLogin Successful! Welcome Staff." << endl;
            staffMenu();
            break;
        } else if(username == "employee" && password == "emp123") {
            cout << "\n\tLogin Successful! Welcome Employee." << endl;
            employeeMenu();
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