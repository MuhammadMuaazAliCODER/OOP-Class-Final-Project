# University Transport Management and Billing System

## Project Overview

This C++ project implements a University Transport Management and Billing System. It supports student registration, admin management, route and vehicle administration, transport applications, approvals, billing, and reporting. The design demonstrates object-oriented programming concepts such as inheritance, polymorphism, abstraction, encapsulation, templates, file handling, and dynamic memory management.

## Authors

- Muhammad Muaaz Ali (2025-CS-708)
- Maham Shahzadi (2025-CS-693)

## Project Structure

```
UniversityTransportManagementSystem/
  main.cpp
  README.md
  include/
    Admin.h
    Bill.h
    Bus.h
    Route.h
    Student.h
    TemplateStorage.h
    TransportManager.h
    TransportPass.h
    User.h
    Van.h
    Vehicle.h
  src/
    Admin.cpp
    Bill.cpp
    Bus.cpp
    Route.cpp
    Student.cpp
    TransportManager.cpp
    TransportPass.cpp
    User.cpp
    Van.cpp
    Vehicle.cpp
  data/
    bills.txt
    registrations.txt
    routes.txt
    users.txt
    vehicles.txt
  .git/
  .vscode/
```

## Key Features

- Admin and Student user roles
- Add, edit, and remove vehicles
- Add routes and assign vehicles to routes
- Student transport applications
- Approve or reject transport requests
- Generate transport bills and apply late fees
- Route and revenue reporting
- Persistent data storage in `data/` text files
- `using namespace std;` is used in header files for simplified type names

## Build Instructions

From the project root, compile with the `include/` folder on the include path and all sources in `src/`.

```bash
cd "c:/Users/DELL/Downloads/UniversityTransportManagementSystem/UniversityTransportManagementSystem"
g++ -Iinclude main.cpp src/*.cpp -std=c++17 -o UniversityTransportManagementSystem
```

## Run Instructions

```bash
./UniversityTransportManagementSystem
```

## Default Admin Account

- ID: `admin`
- Password: `admin123`

## Data Files

The application stores and loads runtime data from the `data/` folder:

- `data/users.txt`
- `data/vehicles.txt`
- `data/routes.txt`
- `data/registrations.txt`
- `data/bills.txt`

## Notes

- Keep `main.cpp` in the project root.
- Keep header files in `include/` and source files in `src/`.
- Keep data files in `data/` so the application can read and write them correctly.
- If compiling on Windows, use the same `-Iinclude` option and update the executable path accordingly.
