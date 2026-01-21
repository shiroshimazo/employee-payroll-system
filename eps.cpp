#include <iostream>
#include <cstdlib>
using namespace std;

void adminLogin();
void staffLogin();
void employeeLogin();
void mainMenu();
void clrscrn();

int main() {
    mainMenu();
    return 0;
}

void adminLogin() {

}

void staffLogin() {

}

void employeeLogin() {

}

void mainMenu() {
    char choice;
    cout << "\n\t-------- Login Dashboard --------\n";
    cout << "\t[1] Admin/Manager" << endl;
    cout << "\t[2] Staff" << endl;
    cout << "\t[3] Employee" << endl;
    cout << "\t[4] Exit" << endl;
    cout << "\tEnter your choice: ";
    cin >> choice;

    switch(choice) {
        case '1':
            adminLogin();
            break;
        case '2':
            staffLogin();
            break;
        case '3':
            employeeLogin();
            break;
        case '4':
            cout << "\n\tThank you for using the Employee Payroll System." << endl;
            exit(0);
        default:
            cout << "\n\tInvalid choice. Please try again.\n";
            mainMenu();
            break;
    }
}

void clrscrn() {
    system("clear");
}