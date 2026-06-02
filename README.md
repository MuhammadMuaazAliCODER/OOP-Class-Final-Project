# University Transport Management and Billing System

## Project Overview
This C++ project implements a University Transport Management and Billing System for a second-semester OOP assignment. The system supports student registration, admin management, route and vehicle administration, transport applications, approvals, billing, and reporting. It uses standard C++ libraries and demonstrates object-oriented design features including inheritance, polymorphism, abstraction, encapsulation, templates, file handling, and dynamic memory management.

## Authors
- Muhammad Muaaz Ali (2025-CS-708)
- Maham Shahzadi (2025-CS-693)

## Project Structure
```
UniversityTransportManagementSystem/
  main.cpp
  User.h
  User.cpp
  Student.h
  Student.cpp
  Admin.h
  Admin.cpp
  Vehicle.h
  Vehicle.cpp
  Bus.h
  Bus.cpp
  Van.h
  Van.cpp
  Route.h
  Route.cpp
  Bill.h
  Bill.cpp
  TransportPass.h
  TransportPass.cpp
  TemplateStorage.h
  TransportManager.h
  TransportManager.cpp
  users.txt
  vehicles.txt
  routes.txt
  registrations.txt
  bills.txt
  README.md
```

## Key Features
- Admin and Student user roles
- Add, edit, and remove vehicles
- Add routes and assign vehicles to routes
- Student transport applications
- Approve or reject transport requests
- Generate transport bills and apply late fees
- Route-wise and revenue reports
- Persistent file storage for users, vehicles, routes, registrations, and bills
- Uses `using namespace std;` consistently across all files

## UML Diagram
```
[User]<>--(abstract)
  id: string
  name: string
  email: string
  password: string
  +authenticate()
  +getRole()
  +display()

[Student]--|> [User]
  year: int
  transportPass: TransportPass*
  +hasTransportPass()
  +getTransportPass()

[Admin]--|> [User]

[Vehicle]<>--(abstract)
  id: string
  model: string
  capacity: int
  assignedRouteId: string
  +getType()
  +display()

[Bus]--|> [Vehicle]
  hasAC: bool

[Van]--|> [Vehicle]
  hasLuggageSpace: bool

[Route]
  id: string
  name: string
  distance: double
  assignedVehicleId: string
  usageCount: int

[TransportPass]
  passId: string
  studentId: string
  routeId: string
  status: string
  bill: Bill
  +approve()
  +reject()
  +cancel()

[Bill]
  billId: string
  studentId: string
  routeId: string
  issueDate: string
  dueDate: string
  status: string
  amount: double
  lateFine: double
  totalAmount: double
  +calculateFee()
  +applyLateFine()
  << operator<< >>

[Storage<T>] (template)
  items: vector<T>
  +add()
  +remove()
  +getAt()

[TransportManager]
  users: vector<User*>
  vehicles: Storage<Vehicle*>
  routes: Storage<Route*>
  registrations: vector<TransportPass*>
  bills: vector<Bill*>
  +loadAllData()
  +saveAllData()
  +runMainMenu()
```

A `draw.io` version of this UML diagram is included in `UniversityTransportManagementSystem.drawio`.

## Build Instructions
Use a C++11-compatible compiler such as `g++`.

```bash
cd '/home/muhammad-muaaz-ali/Desktop/University/Semeter 2/OOP Class/FInal Project/CODE/UniversityTransportManagementSystem'
g++ -std=c++11 main.cpp User.cpp Student.cpp Admin.cpp Vehicle.cpp Bus.cpp Van.cpp Route.cpp Bill.cpp TransportPass.cpp TransportManager.cpp -o UniversityTransportManagementSystem
```

## Run Instructions

```bash
./UniversityTransportManagementSystem
```

## Default Admin Account
- ID: `admin`
- Password: `admin123`

## Sample Data Files
The project uses the following files to load and save application data:
- `users.txt`
- `vehicles.txt`
- `routes.txt`
- `registrations.txt`
- `bills.txt`

## Notes
- The system loads data from sample files at startup.
- Admin users can save data anytime and all changes are saved on exit.
- Students can apply for transport and view registration and bill details.
