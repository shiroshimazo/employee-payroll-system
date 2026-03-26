#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

void adminMenu(), staffMenu(), employeeMenu(), userAuthentication();
void readDataEmployees(), employeeRec(), addEmployee(), updateEmployee(), viewEmployee(), deleteEmployee();
void readDataStaff(), staffsRec(), addStaff(), updateStaff(), viewStaff(), deleteStaff(), changePassword();
void viewSalaryInfo(), printPayslip(), updatePersonalInfo(), employeeSecurity();
void clrscrn();
bool authenticateEmployee(string username, string password);
void employeeMenu(string loggedInUser);
void updatePersonalInfo(string loggedInUser);
void inputAttendance(), computeSalary(), staffGeneratePayslip();
void readDataAttendance(), readDataPayroll();
void payrollReports(), viewAllPayrolls(), viewPayrollByEmployee(), payrollSummaryReport(), deductionSummaryReport(), payrollByDateReport();

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

struct Attendance {
    int employeeId;
    string employeeName;
    double hoursWorked;
    double overtimeHours;
    string date;
};

struct Payroll {
    int employeeId;
    string employeeName;
    string position;
    double rate;
    double hoursWorked;
    double overtimeHours;
    double overtimePay;
    double grossPay;
    double sssDeduction;
    double philhealthDeduction;
    double pagibigDeduction;
    double loanDeduction;
    double advanceFee;
    double totalDeductions;
    double netPay;
    string date;
};

Attendance attendances[100];
Payroll payrolls[100];
int attendanceCount = 0;
int payrollCount = 0;

Employee employees[100];
Staff staffs[100];
int employeeCount = 0;
int staffCount = 0;
string loggedInUser = "";

int main() {
    userAuthentication();
    return 0;
}

void readDataAttendance() {
    ifstream readAtt("attendance.txt");
    attendanceCount = 0;
    string line;
    while(getline(readAtt, line)) {
        if(line.empty()) continue;
        try {
            attendances[attendanceCount].employeeId = stoi(line);
        } catch(...) {
            continue;
        }
        getline(readAtt, attendances[attendanceCount].employeeName);
        getline(readAtt, line);
        if(line.empty()) continue;
        try {
            attendances[attendanceCount].hoursWorked = stod(line);
        } catch(...) {
            continue;
        }
        getline(readAtt, line);
        if(line.empty()) continue;
        try {
            attendances[attendanceCount].overtimeHours = stod(line);
        } catch(...) {
            continue;
        }
        getline(readAtt, attendances[attendanceCount].date);
        attendanceCount++;
    }
    readAtt.close();
}

void readDataPayroll() {
    ifstream readPay("payroll.txt");
    payrollCount = 0;
    string line;
    while(getline(readPay, line)) {
        if(line.empty()) continue;
        
        try {
            payrolls[payrollCount].employeeId = stoi(line);
        } catch(...) {
            continue;
        }
        
        getline(readPay, payrolls[payrollCount].employeeName);
        getline(readPay, payrolls[payrollCount].position);
        
        getline(readPay, line);
        if(line.empty()) continue;
        try {
            payrolls[payrollCount].rate = stod(line);
        } catch(...) {
            continue;
        }
        
        getline(readPay, line);
        if(line.empty()) continue;
        try {
            payrolls[payrollCount].hoursWorked = stod(line);
        } catch(...) {
            continue;
        }
        
        getline(readPay, line);
        if(line.empty()) continue;
        try {
            payrolls[payrollCount].overtimeHours = stod(line);
        } catch(...) {
            continue;
        }
        
        getline(readPay, line);
        if(line.empty()) continue;
        try {
            payrolls[payrollCount].overtimePay = stod(line);
        } catch(...) {
            continue;
        }
        
        getline(readPay, line);
        if(line.empty()) continue;
        try {
            payrolls[payrollCount].grossPay = stod(line);
        } catch(...) {
            continue;
        }
        
        getline(readPay, line);
        if(line.empty()) continue;
        try {
            payrolls[payrollCount].sssDeduction = stod(line);
        } catch(...) {
            continue;
        }
        
        getline(readPay, line);
        if(line.empty()) continue;
        try {
            payrolls[payrollCount].philhealthDeduction = stod(line);
        } catch(...) {
            continue;
        }
        
        getline(readPay, line);
        if(line.empty()) continue;
        try {
            payrolls[payrollCount].pagibigDeduction = stod(line);
        } catch(...) {
            continue;
        }
        
        getline(readPay, line);
        if(line.empty()) continue;
        try {
            payrolls[payrollCount].loanDeduction = stod(line);
        } catch(...) {
            continue;
        }
        
        getline(readPay, line);
        if(line.empty()) continue;
        try {
            payrolls[payrollCount].advanceFee = stod(line);
        } catch(...) {
            continue;
        }
        
        getline(readPay, line);
        if(line.empty()) continue;
        try {
            payrolls[payrollCount].totalDeductions = stod(line);
        } catch(...) {
            continue;
        }
        
        getline(readPay, line);
        if(line.empty()) continue;
        try {
            payrolls[payrollCount].netPay = stod(line);
        } catch(...) {
            continue;
        }
        
        getline(readPay, payrolls[payrollCount].date);
        payrollCount++;
    }
    readPay.close();
}

void readDataEmployees() {
    ifstream readEmp("employees.txt");
    employeeCount = 0;
    string line;
    while(getline(readEmp, line)) {
        if(line.empty()) continue;
        try {
            employees[employeeCount].id = stoi(line);
        } catch(...) {
            continue;
        }
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
        if(line.empty()) continue;
        try {
            employees[employeeCount].rate = stod(line);
        } catch(...) {
            continue;
        }
        employeeCount++;
    }
    readEmp.close(); 
}

void readDataStaff() {
    ifstream readStaff("staffs.txt");
    staffCount = 0;
    string line;
    while (getline(readStaff, line)) {
        if(line.empty()) continue;
        try {
            staffs[staffCount].id = stoi(line);
        } catch(...) {
            continue;
        }
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

    cout << "\n\tStaff Added Successfully!" << endl;

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
        staffsRec();
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
    staffsRec();
}

void payrollReports();

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
            payrollReports();
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

void payrollReports() {
    cout << "\n\t+----------------------------------+\n";
    cout << "\t|   P A Y R O L L   R E P O R T S  |\n";
    cout << "\t+----------------------------------+\n";
    cout << "\n\t[1] View All Payrolls" << endl;
    cout << "\t[2] View Payroll by Employee" << endl;
    cout << "\t[3] Payroll Summary Report" << endl;
    cout << "\t[4] Deduction Summary Report" << endl;
    cout << "\t[5] Payroll by Date/Month" << endl;
    cout << "\t[0] Back" << endl;
    cout << "\n\tChoice: ";
    char choice;
    cin >> choice;

    clrscrn();

    switch(choice) {
        case '1':
            viewAllPayrolls();
            break;
        case '2':
            viewPayrollByEmployee();
            break;
        case '3':
            payrollSummaryReport();
            break;
        case '4':
            deductionSummaryReport();
            break;
        case '5':
            payrollByDateReport();
            break;
        case '0':
            adminMenu();
            break;
        default:
            cout << "\n\tInvalid Choice! Please Try Again." << endl;
            payrollReports();
            break;
    }
}

void viewAllPayrolls() {
    readDataPayroll();
    
    cout << "\n\t+----------------------------------+\n";
    cout << "\t|    A L L   P A Y R O L L S       |\n";
    cout << "\t+----------------------------------+\n";
    
    if(payrollCount == 0) {
        cout << "\n\tNo payroll records found!" << endl;
        cout << "\n\tPress any key to go back...";
        cin.ignore();
        cin.get();
        clrscrn();
        payrollReports();
        return;
    }
    
    cout << "\n\t" << setfill('=') << setw(120) << "=" << setfill(' ') << endl;
    cout << "\t" << left << setw(8) << "ID" << setw(20) << "NAME" 
         << setw(15) << "POSITION" << setw(12) << "RATE"
         << setw(15) << "GROSS PAY" << setw(18) << "DEDUCTIONS" 
         << setw(15) << "NET PAY" << setw(15) << "PERIOD" << endl;
    cout << "\t" << setfill('-') << setw(120) << "-" << setfill(' ') << endl;
    
    for(int i = 0; i < payrollCount; i++) {
        cout << "\t" << left << setw(8) << payrolls[i].employeeId 
             << setw(20) << payrolls[i].employeeName
             << setw(15) << payrolls[i].position 
             << "P " << fixed << setprecision(2) << setw(10) << payrolls[i].rate
             << "P " << fixed << setprecision(2) << setw(13) << payrolls[i].grossPay
             << "P " << fixed << setprecision(2) << setw(16) << payrolls[i].totalDeductions
             << "P " << fixed << setprecision(2) << setw(13) << payrolls[i].netPay
             << payrolls[i].date << endl;
    }
    
    cout << "\t" << setfill('=') << setw(120) << "=" << setfill(' ') << endl;
    cout << "\n\tTotal Records: " << payrollCount << endl;
    
    cout << "\n\tPress any key to go back...";
    cin.ignore();
    cin.get();
    clrscrn();
    payrollReports();
}

void viewPayrollByEmployee() {
    readDataPayroll();
    readDataEmployees();
    
    cout << "\n\t+----------------------------------+\n";
    cout << "\t|  P A Y R O L L   B Y   E M P L O Y E E  |\n";
    cout << "\t+----------------------------------+\n";
    
    int empId;
    cout << "\n\tEnter Employee ID: ";
    cin >> empId;
    
    clrscrn();
    
    cout << "\n\t+----------------------------------+\n";
    cout << "\t|  PAYROLL RECORDS FOR EMPLOYEE ID: " << empId << "\n";
    cout << "\t+----------------------------------+\n";
    
    bool found = false;
    
    cout << "\n\t" << setfill('=') << setw(120) << "=" << setfill(' ') << endl;
    cout << "\t" << left << setw(8) << "ID" << setw(20) << "NAME" 
         << setw(15) << "POSITION" << setw(12) << "RATE"
         << setw(15) << "GROSS PAY" << setw(18) << "DEDUCTIONS" 
         << setw(15) << "NET PAY" << setw(15) << "PERIOD" << endl;
    cout << "\t" << setfill('-') << setw(120) << "-" << setfill(' ') << endl;
    
    for(int i = 0; i < payrollCount; i++) {
        if(payrolls[i].employeeId == empId) {
            found = true;
            cout << "\t" << left << setw(8) << payrolls[i].employeeId 
                 << setw(20) << payrolls[i].employeeName
                 << setw(15) << payrolls[i].position 
                 << "P " << fixed << setprecision(2) << setw(10) << payrolls[i].rate
                 << "P " << fixed << setprecision(2) << setw(13) << payrolls[i].grossPay
                 << "P " << fixed << setprecision(2) << setw(16) << payrolls[i].totalDeductions
                 << "P " << fixed << setprecision(2) << setw(13) << payrolls[i].netPay
                 << payrolls[i].date << endl;
        }
    }
    
    cout << "\t" << setfill('=') << setw(120) << "=" << setfill(' ') << endl;
    
    if(!found) {
        cout << "\n\tNo payroll records found for this employee!" << endl;
    }
    
    cout << "\n\tPress any key to go back...";
    cin.ignore();
    cin.get();
    clrscrn();
    payrollReports();
}

void payrollSummaryReport() {
    readDataPayroll();
    
    cout << "\n\t+----------------------------------+\n";
    cout << "\t| P A Y R O L L   S U M M A R Y    |\n";
    cout << "\t+----------------------------------+\n";
    
    if(payrollCount == 0) {
        cout << "\n\tNo payroll records found!" << endl;
        cout << "\n\tPress any key to go back...";
        cin.ignore();
        cin.get();
        clrscrn();
        payrollReports();
        return;
    }
    
    double totalGross = 0, totalDeductions = 0, totalNetPay = 0;
    double totalSSS = 0, totalPhilhealth = 0, totalPagibig = 0;
    double totalLoan = 0, totalAdvance = 0;
    
    for(int i = 0; i < payrollCount; i++) {
        totalGross += payrolls[i].grossPay;
        totalDeductions += payrolls[i].totalDeductions;
        totalNetPay += payrolls[i].netPay;
        totalSSS += payrolls[i].sssDeduction;
        totalPhilhealth += payrolls[i].philhealthDeduction;
        totalPagibig += payrolls[i].pagibigDeduction;
        totalLoan += payrolls[i].loanDeduction;
        totalAdvance += payrolls[i].advanceFee;
    }
    
    cout << "\n\t" << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
    cout << "\n\tPayroll Summary Report" << endl;
    cout << "\tTotal Employees: " << payrollCount << endl;
    
    cout << "\n\t" << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
    cout << "\n\tGROSS PAYROLL:" << endl;
    cout << "\t  Total Gross Pay: P " << fixed << setprecision(2) << totalGross << endl;
    cout << "\t  Average Per Employee: P " << fixed << setprecision(2) << (totalGross / payrollCount) << endl;
    
    cout << "\n\t" << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
    cout << "\n\tDEDUCTIONS BREAKDOWN:" << endl;
    cout << "\t  SSS: P " << fixed << setprecision(2) << totalSSS << endl;
    cout << "\t  PhilHealth: P " << fixed << setprecision(2) << totalPhilhealth << endl;
    cout << "\t  PagIBIG: P " << fixed << setprecision(2) << totalPagibig << endl;
    cout << "\t  Loan: P " << fixed << setprecision(2) << totalLoan << endl;
    cout << "\t  Advance: P " << fixed << setprecision(2) << totalAdvance << endl;
    cout << "\t  Total Deductions: P " << fixed << setprecision(2) << totalDeductions << endl;
    
    cout << "\n\t" << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
    cout << "\n\tTOTAL NET PAY: P " << fixed << setprecision(2) << totalNetPay << endl;
    cout << "\t" << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
    
    cout << "\n\tPress any key to go back...";
    cin.ignore();
    cin.get();
    clrscrn();
    payrollReports();
}

void deductionSummaryReport() {
    readDataPayroll();
    
    cout << "\n\t+----------------------------------+\n";
    cout << "\t| D E D U C T I O N   S U M M A R Y |\n";
    cout << "\t+----------------------------------+\n";
    
    if(payrollCount == 0) {
        cout << "\n\tNo payroll records found!" << endl;
        cout << "\n\tPress any key to go back...";
        cin.ignore();
        cin.get();
        clrscrn();
        payrollReports();
        return;
    }
    
    cout << "\n\t" << setfill('=') << setw(110) << "=" << setfill(' ') << endl;
    cout << "\t" << left << setw(8) << "ID" << setw(20) << "NAME" 
         << setw(15) << "SSS" << setw(15) << "PHILHEALTH"
         << setw(12) << "PAGIBIG" << setw(12) << "LOAN" 
         << setw(12) << "ADVANCE" << setw(15) << "TOTAL" << endl;
    cout << "\t" << setfill('-') << setw(110) << "-" << setfill(' ') << endl;
    
    double totalAllDeductions = 0;
    
    for(int i = 0; i < payrollCount; i++) {
        cout << "\t" << left << setw(8) << payrolls[i].employeeId 
             << setw(20) << payrolls[i].employeeName
             << "P " << fixed << setprecision(2) << setw(12) << payrolls[i].sssDeduction
             << "P " << fixed << setprecision(2) << setw(13) << payrolls[i].philhealthDeduction
             << "P " << fixed << setprecision(2) << setw(10) << payrolls[i].pagibigDeduction
             << "P " << fixed << setprecision(2) << setw(10) << payrolls[i].loanDeduction
             << "P " << fixed << setprecision(2) << setw(10) << payrolls[i].advanceFee
             << "P " << fixed << setprecision(2) << setw(13) << payrolls[i].totalDeductions << endl;
        totalAllDeductions += payrolls[i].totalDeductions;
    }
    
    cout << "\t" << setfill('=') << setw(110) << "=" << setfill(' ') << endl;
    cout << "\tTOTAL DEDUCTIONS: P " << fixed << setprecision(2) << totalAllDeductions << endl;
    cout << "\t" << setfill('=') << setw(110) << "=" << setfill(' ') << endl;
    
    cout << "\n\tPress any key to go back...";
    cin.ignore();
    cin.get();
    clrscrn();
    payrollReports();
}

void payrollByDateReport() {
    readDataPayroll();
    
    cout << "\n\t+----------------------------------+\n";
    cout << "\t|  PAYROLL BY DATE/MONTH REPORT    |\n";
    cout << "\t+----------------------------------+\n";
    
    if(payrollCount == 0) {
        cout << "\n\tNo payroll records found!" << endl;
        cout << "\n\tPress any key to go back...";
        cin.ignore();
        cin.get();
        clrscrn();
        payrollReports();
        return;
    }
    
    cout << "\n\tEnter Month Name (e.g., January, February, March...): ";
    cin.ignore();
    string searchMonth;
    getline(cin, searchMonth);
    
    // Convert to lowercase for case-insensitive search
    for(int i = 0; i < searchMonth.length(); i++) {
        searchMonth[i] = tolower(searchMonth[i]);
    }
    
    clrscrn();
    
    cout << "\n\t+----------------------------------+\n";
    cout << "\t|  PAYROLL FOR " << searchMonth << endl;
    cout << "\t+----------------------------------+\n";
    
    vector<int> matchingIndices;
    for(int i = 0; i < payrollCount; i++) {
        string dateStr = payrolls[i].date;
        // Convert date string to lowercase for comparison
        for(int j = 0; j < dateStr.length(); j++) {
            dateStr[j] = tolower(dateStr[j]);
        }
        // Check if the search month is in the date
        if(dateStr.find(searchMonth) != string::npos) {
            matchingIndices.push_back(i);
        }
    }
    
    if(matchingIndices.size() == 0) {
        cout << "\n\tNo payroll records found for " << searchMonth << "!" << endl;
        cout << "\n\tPress any key to go back...";
        cin.ignore();
        cin.get();
        clrscrn();
        payrollReports();
        return;
    }
    
    cout << "\n\t" << setfill('=') << setw(120) << "=" << setfill(' ') << endl;
    cout << "\t" << left << setw(8) << "ID" << setw(20) << "NAME" 
         << setw(15) << "POSITION" << setw(12) << "RATE"
         << setw(15) << "GROSS PAY" << setw(18) << "DEDUCTIONS" 
         << setw(15) << "NET PAY" << setw(15) << "PERIOD" << endl;
    cout << "\t" << setfill('-') << setw(120) << "-" << setfill(' ') << endl;
    
    double totalGross = 0, totalDeductions = 0, totalNetPay = 0;
    
    for(int idx : matchingIndices) {
        cout << "\t" << left << setw(8) << payrolls[idx].employeeId 
             << setw(20) << payrolls[idx].employeeName
             << setw(15) << payrolls[idx].position 
             << "P " << fixed << setprecision(2) << setw(10) << payrolls[idx].rate
             << "P " << fixed << setprecision(2) << setw(13) << payrolls[idx].grossPay
             << "P " << fixed << setprecision(2) << setw(16) << payrolls[idx].totalDeductions
             << "P " << fixed << setprecision(2) << setw(13) << payrolls[idx].netPay
             << payrolls[idx].date << endl;
        
        totalGross += payrolls[idx].grossPay;
        totalDeductions += payrolls[idx].totalDeductions;
        totalNetPay += payrolls[idx].netPay;
    }
    
    cout << "\t" << setfill('=') << setw(120) << "=" << setfill(' ') << endl;
    cout << "\n\tSummary for " << searchMonth << ":" << endl;
    cout << "\tTotal Records: " << matchingIndices.size() << endl;
    cout << "\tTotal Gross Pay: P " << fixed << setprecision(2) << totalGross << endl;
    cout << "\tTotal Deductions: P " << fixed << setprecision(2) << totalDeductions << endl;
    cout << "\tTotal Net Pay: P " << fixed << setprecision(2) << totalNetPay << endl;
    cout << "\t" << setfill('=') << setw(120) << "=" << setfill(' ') << endl;
    
    cout << "\n\tPress any key to go back...";
    cin.ignore();
    cin.get();
    clrscrn();
    payrollReports();
}

void staffMenu() {
    cout << "\n\t+----------------------------------+\n";
    cout << "\t|  S T A F F   D A S H B O A R D   |\n";
    cout << "\t+----------------------------------+\n";
    cout << "\n\t[1] Input Employee Attendance" << endl;
    cout << "\t[2] Compute Salary" << endl;
    cout << "\t[3] Generate Payslip" << endl;
    cout << "\t[0] Logout" << endl;
    cout << "\n\tChoice: ";
    char choice;
    cin >> choice;
    clrscrn();

    switch(choice) {
        case '1':
            inputAttendance();
            break;
        case '2':
            computeSalary();
            break;
        case '3':
            staffGeneratePayslip();
            break;
        case '0':
            char confirm;
            while(true) {
                cout << "\n\tAre you sure you want to logout? (y/n): ";
                cin >> confirm;
                if(confirm == 'y' || confirm == 'Y') {
                    cout << "\n\tLogging out..." << endl;
                    loggedInUser = "";
                    userAuthentication();
                    break;
                } else if(confirm == 'n' || confirm == 'N') {
                    staffMenu();
                    break;
                } else {
                    cout << "\n\tInvalid input! Please Try Again." << endl;
                }
            }
            break;
        default:
            cout << "\n\tInvalid Choice! Please Try Again." << endl;
            staffMenu();
            break;
    }
}


void inputAttendance() {
    readDataEmployees();
    cout << "\n\t-------------------------------------------\n";
    cout << "\t|   I N P U T   A T T E N D A N C E       |\n";
    cout << "\t-------------------------------------------\n";

    int empId;
    cout << "\n\tEnter Employee ID: ";
    cin >> empId;

    // Find the employee
    bool found = false;
    int idx = -1;
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == empId) {
            found = true;
            idx = i;
            break;
        }
    }

    if (!found) {
        cout << "\n\tEmployee ID not found!" << endl;
        staffMenu();
        return;
    }

    clrscrn();
    cout << "\n\tEmployee Found: " << employees[idx].fullName << endl;
    cout << "\tPosition: " << employees[idx].position << endl;
    cout << "\tRate: P " << fixed << setprecision(2) << employees[idx].rate << "/hr" << endl;

    Attendance newAtt;
    newAtt.employeeId = employees[idx].id;
    newAtt.employeeName = employees[idx].fullName;

    // Pay period selection
    string month;
    int year;
    char period;

    cout << "\n\tEnter Month (e.g. January): ";
    cin.ignore();
    getline(cin, month);
    cout << "\n\tEnter Year (e.g. 2026): ";
    cin >> year;

    while (true) {
        cout << "\n\tSelect Pay Period:" << endl;
        cout << "\t[1] 1st - 15th" << endl;
        cout << "\t[2] 16th - 30th/31st" << endl;
        cout << "\tChoice: ";
        cin >> period;
        if (period == '1') {
            newAtt.date = month + " 1-15, " + to_string(year);
            break;
        } else if (period == '2') {
            newAtt.date = month + " 16-30, " + to_string(year);
            break;
        } else {
            cout << "\n\tInvalid input! Please Try Again." << endl;
        }
    }

    cout << "\n\tEnter Total Hours Worked (for the 15-day period): ";
    cin >> newAtt.hoursWorked;

    // Ask for overtime
    char hasOvertime;
    newAtt.overtimeHours = 0;
    while (true) {
        cout << "\n\tDoes this employee have overtime? (y/n): ";
        cin >> hasOvertime;
        if (hasOvertime == 'y' || hasOvertime == 'Y') {
            cout << "\n\tEnter Overtime Hours: ";
            cin >> newAtt.overtimeHours;
            break;
        } else if (hasOvertime == 'n' || hasOvertime == 'N') {
            break;
        } else {
            cout << "\n\tInvalid input! Please Try Again." << endl;
        }
    }

    // Save to attendance.txt
    fstream attFile;
    attFile.open("attendance.txt", ios::app);
    attFile << newAtt.employeeId << endl;
    attFile << newAtt.employeeName << endl;
    attFile << newAtt.hoursWorked << endl;
    attFile << newAtt.overtimeHours << endl;
    attFile << newAtt.date << endl;
    attFile.close();

    cout << "\n\tAttendance recorded successfully!" << endl;
    cout << "\n\t+-----+----------------------+---------------------+---------------+---------------+" << endl;
    cout << "\t| " << left << setw(3) << "ID"
         << " | " << setw(20) << "Employee Name"
         << " | " << setw(19) << "Pay Period"
         << " | " << setw(13) << "Hours Worked"
         << " | " << setw(13) << "Overtime Hrs" << " |" << endl;
    cout << "\t+-----+----------------------+---------------------+---------------+---------------+" << endl;
    cout << "\t| " << left << setw(3) << newAtt.employeeId
         << " | " << setw(20) << newAtt.employeeName
         << " | " << setw(19) << newAtt.date
         << " | " << setw(13) << fixed << setprecision(2) << newAtt.hoursWorked
         << " | " << setw(13) << fixed << setprecision(2) << newAtt.overtimeHours << " |" << endl;
    cout << "\t+-----+----------------------+---------------------+---------------+---------------+" << endl;

    staffMenu();
}

void computeSalary() {
    readDataEmployees();
    readDataAttendance();

    cout << "\n\t-----------------------------------------\n";
    cout << "\t|   C O M P U T E   S A L A R Y         |\n";
    cout << "\t-----------------------------------------\n";

    int empId;
    cout << "\n\tEnter Employee ID: ";
    cin >> empId;

    bool foundEmp = false;
    int empIdx = -1;
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == empId) {
            foundEmp = true;
            empIdx = i;
            break;
        }
    }

    if (!foundEmp) {
        cout << "\n\tEmployee ID not found!" << endl;
        staffMenu();
        return;
    }

    cout << "\n\tAttendance records for " << employees[empIdx].fullName << ":" << endl;
    cout << "\n\t+-----+---------------------+---------------+---------------+" << endl;
    cout << "\t| " << left << setw(3) << "No."
         << " | " << setw(19) << "Pay Period"
         << " | " << setw(13) << "Hours Worked"
         << " | " << setw(13) << "Overtime Hrs" << " |" << endl;
    cout << "\t+-----+---------------------+---------------+---------------+" << endl;

    int matchCount = 0;
    int matchIndexes[100];
    for (int i = 0; i < attendanceCount; i++) {
        if (attendances[i].employeeId == empId) {
            matchCount++;
            matchIndexes[matchCount - 1] = i;
            cout << "\t| " << left << setw(3) << matchCount
                 << " | " << setw(19) << attendances[i].date
                 << " | " << setw(13) << fixed << setprecision(2) << attendances[i].hoursWorked
                 << " | " << setw(13) << fixed << setprecision(2) << attendances[i].overtimeHours << " |" << endl;
        }
    }
    cout << "\t+-----+---------------------+---------------+---------------+" << endl;

    if (matchCount == 0) {
        cout << "\n\tNo attendance record found for this employee!" << endl;
        cout << "\tPlease input attendance first." << endl;
        staffMenu();
        return;
    }

    int selection;
    cout << "\n\tSelect Pay Period to compute (enter number): ";
    cin >> selection;

    if (selection < 1 || selection > matchCount) {
        cout << "\n\tInvalid selection!" << endl;
        staffMenu();
        return;
    }

    int attIdx = matchIndexes[selection - 1];

    clrscrn();

    double rate = employees[empIdx].rate;
    double hoursWorked = attendances[attIdx].hoursWorked;
    double overtimeHours = attendances[attIdx].overtimeHours;

    double overtimePay = overtimeHours * (rate * 1.25);
    double grossPay = (rate * hoursWorked) + overtimePay;

    double sssDeduction = grossPay * 0.05;
    double philhealthDeduction = grossPay * 0.025;
    double pagibigDeduction = 200.00;
    if (grossPay < 1500) {
        pagibigDeduction = grossPay * 0.01;
    }

    double loanDeduction = 0;
    double advanceFee = 0;

    cout << "\n\t====================================================" << endl;
    cout << "\t         S A L A R Y   C O M P U T A T I O N" << endl;
    cout << "\t====================================================" << endl;
    cout << "\n\tEmployee ID     : " << employees[empIdx].id << endl;
    cout << "\tEmployee Name   : " << employees[empIdx].fullName << endl;
    cout << "\tPosition        : " << employees[empIdx].position << endl;
    cout << "\tPay Period      : " << attendances[attIdx].date << endl;
    cout << "\t----------------------------------------------------" << endl;
    cout << "\tRate/Hour       : P " << fixed << setprecision(2) << rate << endl;
    cout << "\tHours Worked    : " << hoursWorked << endl;
    cout << "\tOvertime Hours  : " << overtimeHours << endl;
    cout << "\tOvertime Pay    : P " << overtimePay << endl;
    cout << "\tGross Pay       : P " << grossPay << endl;
    cout << "\t----------------------------------------------------" << endl;
    cout << "\t           D E D U C T I O N S" << endl;
    cout << "\t----------------------------------------------------" << endl;
    cout << "\tSSS        (5%) : P " << sssDeduction << endl;
    cout << "\tPhilHealth(2.5%): P " << philhealthDeduction << endl;
    cout << "\tPag-IBIG        : P " << pagibigDeduction << endl;

    char hasLoan;
    while (true) {
        cout << "\n\tDoes this employee have a loan deduction? (y/n): ";
        cin >> hasLoan;
        if (hasLoan == 'y' || hasLoan == 'Y') {
            cout << "\n\tEnter Loan Amount: P ";
            cin >> loanDeduction;
            break;
        } else if (hasLoan == 'n' || hasLoan == 'N') {
            break;
        } else {
            cout << "\n\tInvalid input! Please Try Again." << endl;
        }
    }

    char hasAdvance;
    while (true) {
        cout << "\n\tDoes this employee have a cash advance deduction? (y/n): ";
        cin >> hasAdvance;
        if (hasAdvance == 'y' || hasAdvance == 'Y') {
            cout << "\n\tEnter Cash Advance Amount: P ";
            cin >> advanceFee;
            break;
        } else if (hasAdvance == 'n' || hasAdvance == 'N') {
            break;
        } else {
            cout << "\n\tInvalid input! Please Try Again." << endl;
        }
    }

    double totalDeductions = sssDeduction + philhealthDeduction + pagibigDeduction + loanDeduction + advanceFee;
    double netPay = grossPay - totalDeductions;

    clrscrn();

    cout << "\n\t====================================================" << endl;
    cout << "\t         S A L A R Y   C O M P U T A T I O N" << endl;
    cout << "\t====================================================" << endl;
    cout << "\n\tEmployee ID     : " << employees[empIdx].id << endl;
    cout << "\tEmployee Name   : " << employees[empIdx].fullName << endl;
    cout << "\tPosition        : " << employees[empIdx].position << endl;
    cout << "\tPay Period      : " << attendances[attIdx].date << endl;
    cout << "\t----------------------------------------------------" << endl;
    cout << "\tRate/Hour       : P " << fixed << setprecision(2) << rate << endl;
    cout << "\tHours Worked    : " << hoursWorked << endl;
    cout << "\tOvertime Hours  : " << overtimeHours << endl;
    cout << "\tOvertime Pay    : P " << overtimePay << endl;
    cout << "\tGross Pay       : P " << grossPay << endl;
    cout << "\t----------------------------------------------------" << endl;
    cout << "\t           D E D U C T I O N S" << endl;
    cout << "\t----------------------------------------------------" << endl;
    cout << "\tSSS        (5%) : P " << sssDeduction << endl;
    cout << "\tPhilHealth(2.5%): P " << philhealthDeduction << endl;
    cout << "\tPag-IBIG        : P " << pagibigDeduction << endl;
    cout << "\tLoan            : P " << loanDeduction << endl;
    cout << "\tCash Advance    : P " << advanceFee << endl;
    cout << "\t----------------------------------------------------" << endl;
    cout << "\tTotal Deductions: P " << totalDeductions << endl;
    cout << "\t====================================================" << endl;
    cout << "\tNet Pay         : P " << netPay << endl;
    cout << "\t====================================================" << endl;
    cout << "\tF I N A L   P A Y M E N T : P " << netPay << endl;
    cout << "\t====================================================" << endl;

    char confirm;
    while (true) {
        cout << "\n\tSave this payroll record? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            fstream payFile;
            payFile.open("payroll.txt", ios::app);
            payFile << employees[empIdx].id << endl;
            payFile << employees[empIdx].fullName << endl;
            payFile << employees[empIdx].position << endl;
            payFile << rate << endl;
            payFile << hoursWorked << endl;
            payFile << overtimeHours << endl;
            payFile << overtimePay << endl;
            payFile << grossPay << endl;
            payFile << sssDeduction << endl;
            payFile << philhealthDeduction << endl;
            payFile << pagibigDeduction << endl;
            payFile << loanDeduction << endl;
            payFile << advanceFee << endl;
            payFile << totalDeductions << endl;
            payFile << netPay << endl;
            payFile << attendances[attIdx].date << endl;
            payFile.close();
            cout << "\n\tPayroll record saved successfully!" << endl;
            break;
        } else if (confirm == 'n' || confirm == 'N') {
            cout << "\n\tPayroll record not saved." << endl;
            break;
        } else {
            cout << "\n\tInvalid input! Please Try Again." << endl;
        }
    }

    staffMenu();
}

void staffGeneratePayslip() {
    readDataPayroll();

    cout << "\n\t-------------------------------------------\n";
    cout << "\t|   G E N E R A T E   P A Y S L I P       |\n";
    cout << "\t-------------------------------------------\n";

    int empId;
    cout << "\n\tEnter Employee ID: ";
    cin >> empId;


    bool found = false;
    int payIdx = -1;
    for (int i = payrollCount - 1; i >= 0; i--) {
        if (payrolls[i].employeeId == empId) {
            found = true;
            payIdx = i;
            break;
        }
    }

    if (!found) {
        cout << "\n\tNo payroll record found for this employee!" << endl;
        cout << "\tPlease compute salary first." << endl;
        staffMenu();
        return;
    }

    clrscrn();

    cout << "\n\t====================================================" << endl;
    cout << "\t|           E M P L O Y E E   P A Y S L I P        |" << endl;
    cout << "\t====================================================" << endl;
    cout << "\t| Employee ID     : " << payrolls[payIdx].employeeId << endl;
    cout << "\t| Employee Name   : " << payrolls[payIdx].employeeName << endl;
    cout << "\t| Position        : " << payrolls[payIdx].position << endl;
    cout << "\t| Pay Period      : " << payrolls[payIdx].date << endl;
    cout << "\t|----------------------------------------------------" << endl;
    cout << "\t|            E A R N I N G S" << endl;
    cout << "\t|----------------------------------------------------" << endl;
    cout << "\t| Rate/Hour       : P " << fixed << setprecision(2) << payrolls[payIdx].rate << endl;
    cout << "\t| Hours Worked    : " << payrolls[payIdx].hoursWorked << endl;
    cout << "\t| Overtime Hours  : " << payrolls[payIdx].overtimeHours << endl;
    cout << "\t| Overtime Pay    : P " << payrolls[payIdx].overtimePay << endl;
    cout << "\t| Gross Pay       : P " << payrolls[payIdx].grossPay << endl;
    cout << "\t|----------------------------------------------------" << endl;
    cout << "\t|            D E D U C T I O N S" << endl;
    cout << "\t|----------------------------------------------------" << endl;
    cout << "\t| SSS        (5%) : P " << payrolls[payIdx].sssDeduction << endl;
    cout << "\t| PhilHealth(2.5%): P " << payrolls[payIdx].philhealthDeduction << endl;
    cout << "\t| Pag-IBIG        : P " << payrolls[payIdx].pagibigDeduction << endl;
    cout << "\t| Loan            : P " << payrolls[payIdx].loanDeduction << endl;
    cout << "\t| Cash Advance    : P " << payrolls[payIdx].advanceFee << endl;
    cout << "\t|----------------------------------------------------" << endl;
    cout << "\t| Total Deductions: P " << payrolls[payIdx].totalDeductions << endl;
    cout << "\t|----------------------------------------------------" << endl;
    cout << "\t| Net Pay         : P " << payrolls[payIdx].netPay << endl;
    cout << "\t====================================================" << endl;
    cout << "\t| F I N A L   P A Y M E N T : P " << payrolls[payIdx].netPay << endl;
    cout << "\t====================================================" << endl;

    staffMenu();
}
void employeeMenu() {
    cout << "\n\t+--------------------------------------+\n";
    cout << "\t|  E M P L O Y E E   D A S H B O A R D |\n";
    cout << "\t+--------------------------------------+\n";
    cout << "\n\t[1] View Salary Information" << endl;
    cout << "\t[2] Print Payslip" << endl;
    cout << "\t[3] Security" << endl;
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
    readDataPayroll();
    
    cout << "\n\t+----------------------------------+\n";
    cout << "\t| V I E W  S A L A R Y  I N F O    |\n";
    cout << "\t+----------------------------------+\n";
    
    bool found = false;
    
    for(int i = 0; i < payrollCount; i++) {
        // Find payroll record matching logged-in employee
        if(payrolls[i].employeeName != "") {
            // Get employee details from employees array
            for(int j = 0; j < employeeCount; j++) {
                if(employees[j].username == loggedInUser) {
                    if(payrolls[i].employeeId == employees[j].id) {
                        found = true;
                        cout << "\n\t+-------- SALARY INFORMATION --------+\n";
                        cout << "\n\tEmployee ID: " << payrolls[i].employeeId << endl;
                        cout << "\tEmployee Name: " << payrolls[i].employeeName << endl;
                        cout << "\tPosition: " << payrolls[i].position << endl;
                        cout << "\tHourly Rate: P " << fixed << setprecision(2) << payrolls[i].rate << endl;
                        
                        cout << "\n\t+---------- WORK DETAILS -----------+\n";
                        cout << "\tHours Worked: " << payrolls[i].hoursWorked << " hours" << endl;
                        cout << "\tOvertime Hours: " << payrolls[i].overtimeHours << " hours" << endl;
                        cout << "\tOvertime Pay: P " << fixed << setprecision(2) << payrolls[i].overtimePay << endl;
                        
                        cout << "\n\t+---------- SALARY SUMMARY ---------+\n";
                        cout << "\tGross Pay: P " << fixed << setprecision(2) << payrolls[i].grossPay << endl;
                        
                        cout << "\n\t+--------- DEDUCTIONS -----------+\n";
                        cout << "\tSSS Deduction: P " << fixed << setprecision(2) << payrolls[i].sssDeduction << endl;
                        cout << "\tPhilHealth Deduction: P " << fixed << setprecision(2) << payrolls[i].philhealthDeduction << endl;
                        cout << "\tPagIBIG Deduction: P " << fixed << setprecision(2) << payrolls[i].pagibigDeduction << endl;
                        cout << "\tLoan Deduction: P " << fixed << setprecision(2) << payrolls[i].loanDeduction << endl;
                        cout << "\tAdvance Fee: P " << fixed << setprecision(2) << payrolls[i].advanceFee << endl;
                        cout << "\tTotal Deductions: P " << fixed << setprecision(2) << payrolls[i].totalDeductions << endl;
                        
                        cout << "\n\t+------------- NET PAY ----------+\n";
                        cout << "\tNet Pay: P " << fixed << setprecision(2) << payrolls[i].netPay << endl;
                        
                        cout << "\n\tPayroll Period: " << payrolls[i].date << endl;
                        cout << "\n\t+----------------------------------+\n";
                    }
                    break;
                }
            }
        }
    }
    
    if(!found) {
        cout << "\n\tNo salary information found for your account." << endl;
    }
    
    cout << "\n\tPress any key to go back...";
    cin.ignore();
    cin.get();
    clrscrn();
    employeeMenu();
}

void printPayslip() {
    readDataPayroll();
    readDataEmployees();
    
    cout << "\n\t+----------------------------------+\n";
    cout << "\t|     P R I N T  P A Y S L I P     |\n";
    cout << "\t+----------------------------------+\n";
    
    bool found = false;
    
    for(int i = 0; i < payrollCount; i++) {
        for(int j = 0; j < employeeCount; j++) {
            if(employees[j].username == loggedInUser) {
                if(payrolls[i].employeeId == employees[j].id) {
                    found = true;
                    
                    cout << "\n\t" << setfill('=') << setw(50) << "=" << setfill(' ') << endl;
                    cout << "\n\t                    P A Y S L I P" << endl;
                    cout << "\n\t" << setfill('=') << setw(50) << "=" << setfill(' ') << endl;
                    
                    cout << "\n\tEmployee ID:        " << setw(30) << left << payrolls[i].employeeId << endl;
                    cout << "\tEmployee Name:      " << setw(30) << left << payrolls[i].employeeName << endl;
                    cout << "\tPosition:           " << setw(30) << left << payrolls[i].position << endl;
                    cout << "\tPayroll Period:     " << setw(30) << left << payrolls[i].date << endl;
                    
                    cout << "\n\t" << setfill('-') << setw(50) << "-" << setfill(' ') << endl;
                    cout << "\n\tHourly Rate:        P " << fixed << setprecision(2) << setw(15) << right << payrolls[i].rate << endl;
                    cout << "\tHours Worked:       " << setw(15) << right << payrolls[i].hoursWorked << " hrs" << endl;
                    cout << "\tOvertime Hours:     " << setw(15) << right << payrolls[i].overtimeHours << " hrs" << endl;
                    cout << "\tOvertime Pay:       P " << fixed << setprecision(2) << setw(15) << right << payrolls[i].overtimePay << endl;
                    cout << "\n\t" << setfill('-') << setw(50) << "-" << setfill(' ') << endl;
                    cout << "\tGROSS PAY:          P " << fixed << setprecision(2) << setw(15) << right << payrolls[i].grossPay << endl;
                    
                    cout << "\n\t" << setfill('-') << setw(50) << "-" << setfill(' ') << endl;
                    cout << "\tDEDUCTIONS:" << endl;
                    cout << "\t  SSS:               P " << fixed << setprecision(2) << setw(15) << right << payrolls[i].sssDeduction << endl;
                    cout << "\t  PhilHealth:        P " << fixed << setprecision(2) << setw(15) << right << payrolls[i].philhealthDeduction << endl;
                    cout << "\t  PagIBIG:           P " << fixed << setprecision(2) << setw(15) << right << payrolls[i].pagibigDeduction << endl;
                    cout << "\t  Loan:              P " << fixed << setprecision(2) << setw(15) << right << payrolls[i].loanDeduction << endl;
                    cout << "\t  Advance Fee:       P " << fixed << setprecision(2) << setw(15) << right << payrolls[i].advanceFee << endl;
                    cout << "\t" << setfill('-') << setw(50) << "-" << setfill(' ') << endl;
                    cout << "\t  TOTAL DEDUCTIONS:  P " << fixed << setprecision(2) << setw(15) << right << payrolls[i].totalDeductions << endl;
                    
                    cout << "\n\t" << setfill('=') << setw(50) << "=" << setfill(' ') << endl;
                    cout << "\tNET PAY:            P " << fixed << setprecision(2) << setw(15) << right << payrolls[i].netPay << endl;
                    cout << "\t" << setfill('=') << setw(50) << "=" << setfill(' ') << endl;
                    
                    cout << "\n\tGenerated on: " << __DATE__ << " at " << __TIME__ << endl;
                    cout << "\n\t" << setfill('=') << setw(50) << "=" << setfill(' ') << endl;
                }
                break;
            }
        }
    }
    
    if(!found) {
        cout << "\n\tNo payslip found for your account." << endl;
    }
    
    cout << "\n\tPress any key to go back...";
    cin.ignore();
    cin.get();
    clrscrn();
    employeeMenu();
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

        cout << "\n\t----------------------------------\n";
        cout << "\t|      L O G I N   P A N E L      |\n";
        cout << "\t|    F U J I  F U R N I T U R E   |\n";
        cout << "\t|          C++ Version 1.0        |\n";
        cout << "\t|          Special Edition        |\n";
        cout << "\t----------------------------------\n";

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
