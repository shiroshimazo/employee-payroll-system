# Employee Payroll System

A console-based Employee Payroll System written in C++. The application manages employee records, staff accounts, attendance, timesheets, salary computation, payslips, and payroll reports using local text files as storage.

## Features

### Admin

- Manage employee records: add, update, view, and delete employees
- Manage staff accounts: add, update, view, and delete staff users
- View all employee timesheets
- View payroll reports and summaries

### Staff

- Generate attendance records from employee timesheets
- View generated attendance records
- Compute employee salary
- Generate employee payslips

### Employee

- Clock in and clock out
- Record multiple work sessions in the same day
- View personal timesheet records
- View salary information
- Print payslip
- Change account password

## Tech Stack

- C++
- File-based storage using `.txt` files
- Windows console APIs through `conio.h`

## Project Structure

```text
employee-payroll-system/
├── eps.cpp           # Main C++ source code
├── employees.txt     # Employee account and profile records
├── staffs.txt        # Staff account records
├── attendance.txt    # Generated attendance records
├── timesheet.txt     # Employee clock-in/out records
└── payroll.txt       # Payroll computation records
```

## Requirements

- Windows environment
- C++ compiler such as MinGW-w64 or MSVC

The current source uses `conio.h`, so it is intended for Windows builds.

## Build and Run

Using MinGW-w64:

```bash
g++ -std=c++17 eps.cpp -o eps.exe
./eps.exe
```

Using MSVC Developer Command Prompt:

```bat
cl /EHsc eps.cpp /Fe:eps.exe
eps.exe
```

## Demo Login Accounts

These credentials are for local testing only.

| Role | Username | Password |
| --- | --- | --- |
| Admin | `admin` | `admin123` |
| Staff | `staff` | `staff123` |
| Employee | `empp` | `emp123` |

Before publishing or using this outside a classroom/demo environment, change the default credentials.

## Data Storage

This project stores data in plain text files:

- `employees.txt`
- `staffs.txt`
- `attendance.txt`
- `timesheet.txt`
- `payroll.txt`

Each record is saved as multiple lines in a fixed order. Keep these files in the same directory as the executable so the application can read and write records correctly.

## Important Notes

- Passwords are currently stored in plaintext in the data files.
- This project is suitable for learning, demos, and school requirements, but it is not production-ready.
- Build outputs such as `eps.exe` are ignored by Git through `.gitignore`.
- If you modify data files manually, keep the existing line-based record format intact.

## License

This project is open for educational use. Add a license file if you plan to publish or distribute it publicly.
