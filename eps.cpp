#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

void adminMenu(), staffMenu(), employeeMenu(), userAuthentication();
void readDataEmployees(), employeeRec(), addEmployee(), updateEmployee(), viewEmployee(), deleteEmployee();
void readDataStaff(), staffsRec(), addStaff(), updateStaff(), viewStaff(), deleteStaff(), changePassword();
void viewSalaryInfo(), printPayslip(), updatePersonalInfo(), employeeSecurity();
void clrscrn();
bool authenticateEmployee(string username, string password);
void employeeMenu(string loggedInUser);
void updatePersonalInfo(string loggedInUser);

struct Employee {
    int id;
    string username;
    string password;
    string fullName;
    string gender;
    string contactNumber;
    string emailAddress;
    string cityAddr;
    string position;
    string sssNumber;
    string philhealthNumber;
    string pagibigNumber;
    double rate;
};

struct Staff {
    int id;
    string username;
    string password;
    string fullName;
    string role;
};

Employee employees[100];
Staff staffs[100];
int employeeCount = 0;
int staffCount = 0;
string loggedInUser = "";

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
        getline(readEmp, employees[employeeCount].username);
        getline(readEmp, employees[employeeCount].password);
        getline(readEmp, employees[employeeCount].fullName);
        getline(readEmp, employees[employeeCount].gender);
        getline(readEmp, employees[employeeCount].contactNumber);
        getline(readEmp, employees[employeeCount].emailAddress);
        getline(readEmp, employees[employeeCount].cityAddr);
        getline(readEmp, employees[employeeCount].position);
        getline(readEmp, employees[employeeCount].sssNumber);
        getline(readEmp, employees[employeeCount].philhealthNumber);
        getline(readEmp, employees[employeeCount].pagibigNumber);
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
        getline(readStaff, staffs[staffCount].role);
        staffCount++;
    }
    readStaff.close();
}

void employeeRec() {
    cout << "\n\t--------------------------------------" << endl;
    cout << "\t|   E M P L O Y E E   R E C O R D S  |" << endl;
    cout << "\t--------------------------------------" << endl;
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
    cout << "\n\t-----------------------------\n";
    cout << "\t|   A D D  E M P L O Y E E  |\n";
    cout << "\t-----------------------------\n";
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

    cout << "\n\tEnter Username: ";
    cin.ignore();
    getline(cin, newEmp.username);
    cout << "\n\tEnter Password: ";
    getline(cin, newEmp.password);
    cout << "\n\tEnter Full Name: ";
    getline(cin, newEmp.fullName);
    cout << "\n\tEnter Gender: ";
    getline(cin, newEmp.gender);
    cout << "\n\tEnter Contact Number: ";
    getline(cin, newEmp.contactNumber);
    cout << "\n\tEnter Email Address: ";
    getline(cin, newEmp.emailAddress);
    cout << "\n\tEnter City Address: ";
    getline(cin, newEmp.cityAddr);
    cout << "\n\tEnter Position: ";
    getline(cin, newEmp.position);
    cout << "\n\tEnter SSS Number: ";
    getline(cin, newEmp.sssNumber);
    cout << "\n\tEnter PhilHealth Number: ";
    getline(cin, newEmp.philhealthNumber);
    cout << "\n\tEnter Pag-IBIG Number: ";
    getline(cin, newEmp.pagibigNumber);
    cout << "\n\tEnter Rate: ";
    cin >> newEmp.rate;

    employees[employeeCount] = newEmp;
    employeeCount++;

    cout << "\n\tEmployee Added Successfully!" << endl;

    empRec << newEmp.id << endl;
    empRec << newEmp.username << endl;
    empRec << newEmp.password << endl;
    empRec << newEmp.fullName << endl;
    empRec << newEmp.gender << endl;
    empRec << newEmp.contactNumber << endl;
    empRec << newEmp.emailAddress << endl;
    empRec << newEmp.cityAddr << endl;
    empRec << newEmp.position << endl;
    empRec << newEmp.sssNumber << endl;
    empRec << newEmp.philhealthNumber << endl;
    empRec << newEmp.pagibigNumber << endl;
    empRec << newEmp.rate << endl;
    empRec.close();
    employeeRec();
}

void updateEmployee() {
    cout << "\n\t-------------------------------------\n";
    cout << "\t|   U P D A T E   E M P L O Y E E   |\n";
    cout << "\t-------------------------------------\n";
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
        updateEmployee();
        return;
    }
    bool showError = false;
    while (true) {
        clrscrn();
        cout << "\n\tEmployee to Update:" << endl;
        cout << "\n\t+-----+------------+------------+------------------+--------+-------------+----------------------+------------------+------------+------------------+----------------+------------------+----------+" << endl;
        cout << "\t| " << left << setw(3) << "ID" << " | " << setw(10) << "Username" << " | " << setw(10) << "Password" << " | " << setw(16) << "Full Name" << " | " << setw(6) << "Gender" << " | " << setw(11) << "Contact No." << " | " << setw(20) << "Email Address" << " | " << setw(16) << "City Address" << " | " << setw(10) << "Position" << " | " << setw(16) << "SSS No." << " | " << setw(14) << "PhilHealth No." << " | " << setw(16) << "Pag-IBIG No." << " | " << setw(8) << "Rate" << " |" << endl;
        cout << "\t+-----+------------+------------+------------------+--------+-------------+----------------------+------------------+------------+------------------+----------------+------------------+----------+" << endl;
        cout << "\t| " << left << setw(3) << employees[idx].id << " | " << setw(10) << employees[idx].username << " | " << setw(10) << employees[idx].password << " | " << setw(16) << employees[idx].fullName << " | " << setw(6) << employees[idx].gender << " | " << setw(11) << employees[idx].contactNumber << " | " << setw(20) << employees[idx].emailAddress << " | " << setw(16) << employees[idx].cityAddr << " | " << setw(10) << employees[idx].position << " | " << setw(16) << employees[idx].sssNumber << " | " << setw(14) << employees[idx].philhealthNumber << " | " << setw(16) << employees[idx].pagibigNumber << " | " << setw(8) << fixed << setprecision(2) << employees[idx].rate << " |" << endl;
        cout << "\t+-----+------------+------------+------------------+--------+-------------+----------------------+------------------+------------+------------------+----------------+------------------+----------+" << endl;
        if (showError) {
            cout << "\n\tInvalid Choice! Please Try Again." << endl;
            showError = false;
        }
        cout << "\n\tWhat do you want to change?" << endl;
        cout << "\t[1] Change Username" << endl;
        cout << "\t[2] Change Password" << endl;
        cout << "\t[3] Change Full Name" << endl;
        cout << "\t[4] Change Gender" << endl;
        cout << "\t[5] Change Contact Number" << endl;
        cout << "\t[6] Change Email Address" << endl;
        cout << "\t[7] Change City Address" << endl;
        cout << "\t[8] Change Position" << endl;
        cout << "\t[9] Change SSS Number" << endl;
        cout << "\t[10] Change PhilHealth Number" << endl;
        cout << "\t[11] Change Pag-IBIG Number" << endl;
        cout << "\t[12] Change Rate" << endl;
        cout << "\t[0] Back" << endl;
        cout << "\tChoice: ";
        int choice;
        cin >> choice;
        bool validUpdate = false;

        clrscrn();
        
        switch (choice) {
            case 1:
            cout << "\n\tEnter new Username: ";
            cin.ignore();
            getline(cin, employees[idx].username);
            cout << "\n\tUsername updated successfully!" << endl;
            validUpdate = true;
            break;
        case 2:
            cout << "\n\tEnter new Password: ";
            cin.ignore();
            getline(cin, employees[idx].password);
            cout << "\n\tPassword updated successfully!" << endl;
            validUpdate = true;
            break;
        case 3:
            cout << "\n\tEnter new Full Name: ";
            cin.ignore();
            getline(cin, employees[idx].fullName);
            cout << "\n\tFull Name updated successfully!" << endl;
            validUpdate = true;
            break;
        case 4:
            cout << "\n\tEnter new Gender: ";
            cin.ignore();
            getline(cin, employees[idx].gender);
            cout << "\n\tGender updated successfully!" << endl;
            validUpdate = true;
            break;
        case 5:
            cout << "\n\tEnter new Contact Number: ";
            cin.ignore();
            getline(cin, employees[idx].contactNumber);
            cout << "\n\tContact Number updated successfully!" << endl;
            validUpdate = true;
            break;
        case 6:
            cout << "\n\tEnter new Email Address: ";
            cin.ignore();
            getline(cin, employees[idx].emailAddress);
            cout << "\n\tEmail Address updated successfully!" << endl;
            validUpdate = true;
            break;
        case 7:
            cout << "\n\tEnter new City Address: ";
            cin.ignore();
            getline(cin, employees[idx].cityAddr);
            cout << "\n\tCity Address updated successfully!" << endl;
            validUpdate = true; 
            break;
        case 8: 
            cout << "\n\tEnter new Position: ";
            cin.ignore();
            getline(cin, employees[idx].position);
            cout << "\n\tPosition updated successfully!" << endl;
            validUpdate = true;
            break;
        case 9:
            cout << "\n\tEnter new SSS Number: ";
            cin.ignore();
            getline(cin, employees[idx].sssNumber);
            cout << "\n\tSSS Number updated successfully!" << endl;
            validUpdate = true;
            break;
        case 10:
            cout << "\n\tEnter new PhilHealth Number: ";
            cin.ignore();
            getline(cin, employees[idx].philhealthNumber);
            cout << "\n\tPhilHealth Number updated successfully!" << endl;
            validUpdate = true;
            break;
        case 11:
            cout << "\n\tEnter new Pag-IBIG Number: ";
            cin.ignore();
            getline(cin, employees[idx].pagibigNumber);
            cout << "\n\tPag-IBIG Number updated successfully!" << endl;
            validUpdate = true;
            break;
        case 12: 
            cout << "\n\tEnter new Rate: ";
            cin >> employees[idx].rate;
            cout << "\n\tRate updated successfully!" << endl;
            validUpdate = true;
            break;
        case 0:
            clrscrn();
            employeeRec();
            return;
        default:
            showError = true;
            continue;
        }
        if (validUpdate) {
            break;
        }
    }
    ofstream outRec("employees.txt");
    for (int i = 0; i < employeeCount; i++) {
        outRec << employees[i].id << endl;
        outRec << employees[i].username << endl;
        outRec << employees[i].password << endl;
        outRec << employees[i].fullName << endl;
        outRec << employees[i].gender << endl;
        outRec << employees[i].contactNumber << endl;
        outRec << employees[i].emailAddress << endl;
        outRec << employees[i].cityAddr << endl;
        outRec << employees[i].position << endl;
        outRec << employees[i].sssNumber << endl;
        outRec << employees[i].philhealthNumber << endl;
        outRec << employees[i].pagibigNumber << endl;
        outRec << employees[i].rate << endl;
    }
    outRec.close();
    cout << "\n\t+-----+------------+------------+----------------------+--------+--------------+--------------------------+----------------------+----------------------+--------------------+----------------+--------------------+----------+" << endl;
    cout << "\t| " << left << setw(3)  << "ID"
         << " | " << setw(10) << "Username"
         << " | " << setw(10) << "Password"
         << " | " << setw(20) << "Full Name"
         << " | " << setw(6)  << "Gender"
         << " | " << setw(12) << "Contact No."
         << " | " << setw(24) << "Email Address"
         << " | " << setw(20) << "City Address"
         << " | " << setw(20) << "Position"
         << " | " << setw(18) << "SSS No."
         << " | " << setw(14) << "PhilHealth No."
         << " | " << setw(18) << "Pag-IBIG No."
         << " | " << setw(8)  << "Rate"
         << " |" << endl;
    cout << "\t+-----+------------+------------+----------------------+--------+--------------+--------------------------+----------------------+----------------------+--------------------+----------------+--------------------+----------+" << endl;
    cout << "\t| " << left << setw(3)  << employees[idx].id
         << " | " << setw(10) << employees[idx].username
         << " | " << setw(10) << employees[idx].password
         << " | " << setw(20) << employees[idx].fullName
         << " | " << setw(6)  << employees[idx].gender
         << " | " << setw(12) << employees[idx].contactNumber
         << " | " << setw(24) << employees[idx].emailAddress
         << " | " << setw(20) << employees[idx].cityAddr
         << " | " << setw(20) << employees[idx].position
         << " | " << setw(18) << employees[idx].sssNumber
         << " | " << setw(14) << employees[idx].philhealthNumber
         << " | " << setw(18) << employees[idx].pagibigNumber
         << " | " << setw(8)  << fixed << setprecision(2) << employees[idx].rate
         << " |" << endl;
    cout << "\t+-----+------------+------------+----------------------+--------+--------------+--------------------------+----------------------+----------------------+--------------------+----------------+--------------------+----------+" << endl;
    employeeRec();
}

void viewEmployee() {
    readDataEmployees();
    char choice;
    cout << "\n\t--------------------------------\n";
    cout << "\t|   V I E W   E M P L O Y E E  |\n";
    cout << "\t--------------------------------\n";
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
                cout << "\n\t+-----+------------+------------+----------------------+--------+--------------+--------------------------+----------------------+----------------------+--------------------+----------------+--------------------+----------+" << endl;
                cout << "\t| " << left << setw(3)  << "ID"
                     << " | " << setw(10) << "Username"
                     << " | " << setw(10) << "Password"
                     << " | " << setw(20) << "Full Name"
                     << " | " << setw(6)  << "Gender"
                     << " | " << setw(12) << "Contact No."
                     << " | " << setw(24) << "Email Address"
                     << " | " << setw(20) << "City Address"
                     << " | " << setw(20) << "Position"
                     << " | " << setw(18) << "SSS No."
                     << " | " << setw(14) << "PhilHealth No."
                     << " | " << setw(18) << "Pag-IBIG No."
                     << " | " << setw(8)  << "Rate"
                     << " |" << endl;
                cout << "\t+-----+------------+------------+----------------------+--------+--------------+--------------------------+----------------------+----------------------+--------------------+----------------+--------------------+----------+" << endl;
                for (int i = 0; i < employeeCount; i++) {
                    cout << "\t| " << left << setw(3)  << employees[i].id
                         << " | " << setw(10) << employees[i].username
                         << " | " << setw(10) << employees[i].password
                         << " | " << setw(20) << employees[i].fullName
                         << " | " << setw(6)  << employees[i].gender
                         << " | " << setw(12) << employees[i].contactNumber
                         << " | " << setw(24) << employees[i].emailAddress
                         << " | " << setw(20) << employees[i].cityAddr
                         << " | " << setw(20) << employees[i].position
                         << " | " << setw(18) << employees[i].sssNumber
                         << " | " << setw(14) << employees[i].philhealthNumber
                         << " | " << setw(18) << employees[i].pagibigNumber
                         << " | " << setw(8)  << fixed << setprecision(2) << employees[i].rate
                         << " |" << endl;
                }
                cout << "\t+-----+------------+------------+----------------------+--------+--------------+--------------------------+----------------------+----------------------+--------------------+----------------+--------------------+----------+" << endl;
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
                        cout << "\n\t+-----+------------+------------+----------------------+--------+--------------+--------------------------+----------------------+----------------------+--------------------+----------------+--------------------+----------+" << endl;
                        cout << "\t| " << left << setw(3)  << "ID"
                             << " | " << setw(10) << "Username"
                             << " | " << setw(10) << "Password"
                             << " | " << setw(20) << "Full Name"
                             << " | " << setw(6)  << "Gender"
                             << " | " << setw(12) << "Contact No."
                             << " | " << setw(24) << "Email Address"
                             << " | " << setw(20) << "City Address"
                             << " | " << setw(20) << "Position"
                             << " | " << setw(18) << "SSS No."
                             << " | " << setw(14) << "PhilHealth No."
                             << " | " << setw(18) << "Pag-IBIG No."
                             << " | " << setw(8)  << "Rate"
                             << " |" << endl;
                        cout << "\t+-----+------------+------------+----------------------+--------+--------------+--------------------------+----------------------+----------------------+--------------------+----------------+--------------------+----------+" << endl;
                        cout << "\t| " << left << setw(3)  << employees[i].id
                             << " | " << setw(10) << employees[i].username
                             << " | " << setw(10) << employees[i].password
                             << " | " << setw(20) << employees[i].fullName
                             << " | " << setw(6)  << employees[i].gender
                             << " | " << setw(12) << employees[i].contactNumber
                             << " | " << setw(24) << employees[i].emailAddress
                             << " | " << setw(20) << employees[i].cityAddr
                             << " | " << setw(20) << employees[i].position
                             << " | " << setw(18) << employees[i].sssNumber
                             << " | " << setw(14) << employees[i].philhealthNumber
                             << " | " << setw(18) << employees[i].pagibigNumber
                             << " | " << setw(8)  << fixed << setprecision(2) << employees[i].rate
                             << " |" << endl;
                        cout << "\t+-----+------------+------------+----------------------+--------+--------------+--------------------------+----------------------+----------------------+--------------------+----------------+--------------------+----------+" << endl;
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
    cout << "\n\t------------------------------------\n";
    cout << "\t|   D E L E T E   E M P L O Y E E  |\n";
    cout << "\t------------------------------------\n";
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
    cout << "\n\t+-----+------------+------------+------------------+--------+-------------+----------------------+------------------+----------------------+--------------------+----------------+--------------------+----------+" << endl;
    cout << "\t| " << left << setw(3) << "ID" << " | " << setw(10) << "Username" << " | " << setw(10) << "Password" << " | " << setw(16) << "Full Name" << " | " << setw(6) << "Gender" << " | " << setw(11) << "Contact No." << " | " << setw(20) << "Email Address" << " | " << setw(16) << "City Address" << " | " << setw(20) << "Position" << " | " << setw(16) << "SSS No." << " | " << setw(14) << "PhilHealth No." << " | " << setw(16) << "Pag-IBIG No." <<(" | ") << setw(8) << fixed << setprecision(2) << employees[idx].rate << " |" << endl;
    cout << "\t+-----+------------+------------+------------------+--------+-------------+----------------------+------------------+----------------------+--------------------+----------------+--------------------+----------+" << endl;
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
            outRec << employees[i].username << endl;
            outRec << employees[i].password << endl;
            outRec << employees[i].fullName << endl;
            outRec << employees[i].gender << endl;
            outRec << employees[i].contactNumber << endl;
            outRec << employees[i].emailAddress << endl;
            outRec << employees[i].cityAddr << endl;
            outRec << employees[i].position << endl;
            outRec << employees[i].sssNumber << endl;
            outRec << employees[i].philhealthNumber << endl;
            outRec << employees[i].pagibigNumber << endl;
            outRec << employees[i].rate << endl;
        }
        outRec.close();
        cout << "\n\tEmployee deleted successfully!" << endl;
    } else {
        cout << "\n\tDeletion cancelled!" << endl;
    }
    employeeRec();
}

void staffsRec() {
    cout << "\n\t-------------------------------------------------------\n";
    cout << "\t|   S T A F F   R E C O R D S   M A N A G E M E N T   |\n";
    cout << "\t-------------------------------------------------------\n";
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
    cout << "\n\t---------------------------------\n";
    cout << "\t|   A D D   N E W   S T A F F   |\n";
    cout << "\t---------------------------------\n";
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
    cout << "\n\tEnter Role: ";
    getline(cin, newStaff.role);

    staffs[staffCount] = newStaff;
    staffCount++;

    cout << "\n\tEmployee Added Successfully!" << endl;

    staffRec << newStaff.id << endl;
    staffRec << newStaff.username << endl;
    staffRec << newStaff.password << endl;
    staffRec << newStaff.fullName << endl;
    staffRec << newStaff.role << endl;
    staffRec.close();
    staffsRec();
}

void viewStaff() {
    readDataStaff();
    char choice;
    cout << "\n\t---------------------------\n";
    cout << "\t|   V I E W   S T A F F   |\n";
    cout << "\t---------------------------\n";
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
                cout << "\n\t+-----+---------------+---------------+----------------------+------------+" << endl;
                cout << "\t| " << left << setw(3) << "ID" << " | " << setw(13) << "Username" << " | " << setw(13) << "Password" << " | " << setw(20) << "Full Name" << " | " << setw(10) << "Role" << " |" << endl;
                cout << "\t+-----+---------------+---------------+----------------------+------------+" << endl;
                for (int i = 0; i < staffCount; i++) {
                    cout << "\t| " << left << setw(3) << staffs[i].id << " | " << setw(13) << staffs[i].username << " | " << setw(13) << staffs[i].password << " | " << setw(20) << staffs[i].fullName << " | " << setw(10) << staffs[i].role << " |" << endl;
                }
                cout << "\t+-----+---------------+---------------+----------------------+------------+" << endl;
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
                        cout << "\n\t+-----+---------------+---------------+----------------------+-----------------+" << endl;
                        cout << "\t| " << left << setw(3) << "ID" << " | " << setw(13) << "Username" << " | " << setw(13) << "Password" << " | " << setw(20) << "Full Name" << " | " << setw(15) << "Role" << " |" << endl;
                        cout << "\t+-----+---------------+---------------+----------------------+-----------------+" << endl;
                        cout << "\t| " << left << setw(3) << staffs[i].id << " | " << setw(13) << staffs[i].username << " | " << setw(13) << staffs[i].password << " | " << setw(20) << staffs[i].fullName << " | " << setw(15) << staffs[i].role << " |" << endl;
                        cout << "\t+-----+---------------+---------------+----------------------+-----------------+" << endl;
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
    cout << "\n\t------------------------------\n";
    cout << "\t|   U P D A T E  S T A F F   |\n";
    cout << "\t------------------------------\n";
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
        cout << "\n\tStaff to Update:" << endl;
        cout << "\n\t+-----+---------------+---------------+----------------------+-----------------+" << endl;
        cout << "\t| " << left << setw(3) << "ID" << " | " << setw(13) << "Username" << " | " << setw(13) << "Password" << " | " << setw(20) << "Full Name" << " | " << setw(15) << "Role" << " |" << endl;
        cout << "\t+-----+---------------+---------------+----------------------+-----------------+" << endl;
        cout << "\t| " << left << setw(3) << staffs[idx].id << " | " << setw(13) << staffs[idx].username << " | " << setw(13) << staffs[idx].password << " | " << setw(20) << staffs[idx].fullName << " | " << setw(15) << staffs[idx].role << " |" << endl;
        cout << "\t+-----+---------------+---------------+----------------------+-----------------+" << endl;
        if (showError) {
            cout << "\n\t>> Invalid Choice! Please Try Again." << endl;
            showError = false;
        }
        cout << "\n\tWhat do you want to change?" << endl;
        cout << "\t[1] change Username" << endl;
        cout << "\t[2] change Password" << endl;
        cout << "\t[3] change Full Name" << endl;
        cout << "\t[4] change Role" << endl;
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
                cout << "\n\tEnter New Role: ";
                cin.ignore();
                getline(cin, staffs[idx].role);
                cout << "\n\tRole updated successfully!" << endl;
                validUpdate = true;
                break;
            case '0':
                clrscrn();
                staffsRec();
                return;
            default:
                showError = true;
                continue; 
        }
        if(validUpdate) {
            break;
        }
    }
    ofstream outStaff("staffs.txt");
    for(int i = 0; i < staffCount; i++) {
        outStaff << staffs[i].id << "\n";
        outStaff << staffs[i].username << "\n";
        outStaff << staffs[i].password << "\n";
        outStaff << staffs[i].fullName << "\n";
        outStaff << staffs[i].role << "\n";
    }

    outStaff.close();
    cout << "\n\tUpdated Staff Data:" << endl;
    cout << "\n\t+-----+---------------+---------------+----------------------+-----------------+" << endl;
    cout << "\t| " << left << setw(3) << "ID" << " | " << setw(13) << "Username" << " | " << setw(13) << "Password" << " | " << setw(20) << "Full Name" << " | " << setw(15) << "Role" << " |" << endl;
    cout << "\t+-----+---------------+---------------+----------------------+-----------------+" << endl;
    cout << "\t| " << left << setw(3) << staffs[idx].id << " | " << setw(13) << staffs[idx].username << " | " << setw(13) << staffs[idx].password << " | " << setw(20) << staffs[idx].fullName << " | " << setw(15) << staffs[idx].role << " |" << endl;
    cout << "\t+-----+---------------+---------------+----------------------+-----------------+" << endl;
    updateStaff();
}

void deleteStaff() {
    cout << "\n\t-------------------------------\n";
    cout << "\t|   D E L E T E   S T A F F   |\n";
    cout << "\t-------------------------------\n";
    readDataStaff();
    int delId;
    cout << "\n\tEnter ID to delete: ";
    cin >> delId;
    clrscrn();
    bool found = false;
    int idx = -1;
    for(int i = 0; i < staffCount; i++) {
        if(staffs[i].id == delId) {
            found = true;
            idx = i;
            break;
        }
    }
    if(!found) {
        cout << "\n\tStaff not found!" << endl;
        return;
    }
    cout << "\n\tStaff to delete:" << endl;
    cout << "\n\t+-----+---------------+---------------+----------------------+-----------------+" << endl;
    cout << "\t| " << left << setw(3) << "ID" << " | " << setw(13) << "Username" << " | " << setw(13) << "Password" << " | " << setw(20) << "Full Name" << " | " << setw(15) << "Role" << " |" << endl;
    cout << "\t+-----+---------------+---------------+----------------------+-----------------+" << endl;
    cout << "\t| " << left << setw(3) << staffs[idx].id << " | " << setw(13) << staffs[idx].username << " | " << setw(13) << staffs[idx].password << " | " << setw(20) << staffs[idx].fullName << " | " << setw(15) << staffs[idx].role << " |" << endl;
    cout << "\t+-----+---------------+---------------+----------------------+-----------------+" << endl;
    cout << "\n\tAre you sure?" << endl;
    cout << "\t[1] Delete Row of Data" << endl;
    cout << "\t[2] Cancel" << endl;
    cout << "\tChoice: ";
    char choice;
    cin >> choice;
    clrscrn();
    if (choice == '1') {
        for (int i = idx; i < staffCount - 1; i++) {
            staffs[i] = staffs[i + 1];
        }
        staffCount--;
        ofstream outStaff("staffs.txt");
        for(int i = 0; i < staffCount; i++) {
            outStaff << staffs[i].id << "\n";
            outStaff << staffs[i].username << "\n";
            outStaff << staffs[i].password << "\n";
            outStaff << staffs[i].fullName << "\n";
            outStaff << staffs[i].role << "\n";
        }
        outStaff.close();
        cout << "\n\tStaff deleted successfully!" << endl;
    } else {
        cout << "\n\tDeletion cancelled!" << endl;
    }
    deleteStaff();
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
    cout << "\n\t+--------------------------------------+\n";
    cout << "\t|  E M P L O Y E E   D A S H B O A R D |\n";
    cout << "\t+--------------------------------------+\n";
    cout << "\n\t[1] View Salary Information" << endl;
    cout << "\t[2] Print Payslip" << endl;
    cout << "\t[4] Security" << endl;
    cout << "\t[0] Logout" << endl;
    cout << "\n\tChoice: ";
    char choice;
    cin >> choice;

    clrscrn();

    switch(choice) {
        case '1':
            viewSalaryInfo();
            break;
        case '2':
            printPayslip();
            break;
        case '3':
            employeeSecurity();
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
                    employeeMenu();
                    break;
                } else {
                    cout << "\n\tInvalid input! Please Try Again." << endl;
                }
            }
            break;
        default:
            cout << "\n\tInvalid Choice! Please Try Again." << endl;
            employeeMenu();
            break;
    }
}

void viewSalaryInfo() {

}

void printPayslip() {

}


void employeeSecurity() {
    cout << "\n\t+--------------------+\n";
    cout << "\t|   S E C U R I T Y   |\n";
    cout << "\t+---------------------+\n";
    cout << "\n\t[1] Change Password" << endl;
    cout << "\t[0] Back" << endl;
    cout << "\n\tChoice: ";
    char choice;
    cin >> choice;
    
    clrscrn();
    
    switch(choice) {
        case '1':
            changePassword();
            break;
        case '0':
            employeeMenu();
            break;
        default:
            cout << "\n\tInvalid Choice! Please Try Again." << endl;
            employeeSecurity();
            break;
    }
}

void changePassword() {
    string username, oldPassword, newPassword;
    cout << "\n\tEnter Username: ";
    cin >> username;
    cout << "\n\tEnter Old Password: ";
    cin >> oldPassword;

    if(authenticateEmployee(username, oldPassword)) {
        cout << "\n\tEnter New Password: ";
        cin >> newPassword;

        for(int i = 0; i < employeeCount; i++) {
            if(employees[i].username == username) {
                employees[i].password = newPassword;
                break;
            }
        }

        ofstream outRec("employees.txt");
        for (int i = 0; i < employeeCount; i++) {
            outRec << employees[i].id << endl;
            outRec << employees[i].username << endl;
            outRec << employees[i].password << endl;
            outRec << employees[i].fullName << endl;
            outRec << employees[i].gender << endl;
            outRec << employees[i].contactNumber << endl;
            outRec << employees[i].emailAddress << endl;
            outRec << employees[i].cityAddr << endl;
            outRec << employees[i].position << endl;
            outRec << employees[i].sssNumber << endl;
            outRec << employees[i].philhealthNumber << endl;
            outRec << employees[i].pagibigNumber << endl;
            outRec << employees[i].rate << endl;
        }
        outRec.close();
        cout << "\n\tPassword changed successfully!" << endl;
    } else {
        cout << "\n\tInvalid Username or Old Password!" << endl;
    }
    employeeSecurity();
}


bool authenticateStaff(string username, string password) {
    readDataStaff();
    for(int i = 0; i < staffCount; i++) {
        if(staffs[i].username == username && staffs[i].password == password) {
            return true;
        }
    }
    return false;
}

bool authenticateEmployee(string username, string password) {
    readDataEmployees();
    for(int i = 0; i < employeeCount; i++) {
        if(employees[i].username == username && employees[i].password == password) {
            return true;
        }
    }
    return false;
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
        } else if(authenticateStaff(username, password)) {
            cout << "\n\tLogin Successful! Welcome Staff." << endl;
            staffMenu();
            break;
        } else if(authenticateEmployee(username, password)) {
            cout << "\n\tLogin Successful! Welcome Employee." << endl;
            loggedInUser = username;
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
    system("cls");
}
