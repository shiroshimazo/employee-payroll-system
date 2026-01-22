#include <iostream>
#include <cstdlib>
using namespace std;

void adminLogin(), staffLogin(), employeeLogin(), userAuthentication();
void addEmployee(), updateEmployee(), viewEmployee(), deleteEmployee();
void clrscrn();

int main() {
    userAuthentication();
    return 0;
}

void addEmployee() {

}

void updateEmployee() {

}

void viewEmployee() {

}

void deleteEmployee() {

}

void adminLogin() {

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