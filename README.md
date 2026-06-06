<div align="center">

# 🚌 University Transport Management & Billing System

### A Comprehensive C++ Transport Administration Solution for Universities

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![OOP](https://img.shields.io/badge/Paradigm-OOP-green)
![Build](https://img.shields.io/badge/Build-GCC-orange)
![Storage](https://img.shields.io/badge/Database-File%20System-yellow)
![Status](https://img.shields.io/badge/Status-Completed-success)

</div>

---

## 📖 Project Overview

The **University Transport Management & Billing System** is a C++ Object-Oriented Programming project designed to automate university transportation operations. The system manages students, administrators, routes, vehicles, transport applications, approvals, billing processes, and reporting through a structured and scalable architecture.

The project demonstrates advanced OOP concepts along with real-world system design principles and persistent data management.

---

## ✨ Key Features

### 👨‍🎓 Student Management

- Student registration
- Transport service applications
- Transport pass management
- Application status tracking

### 👨‍💼 Admin Management

- Secure administrator login
- User management
- Application approvals and rejections

### 🚍 Vehicle Management

- Add new vehicles
- Update vehicle information
- Remove vehicles
- Support for multiple vehicle types:
  - Bus
  - Van

### 🛣️ Route Management

- Create transport routes
- Assign vehicles to routes
- Manage route information

### 💳 Billing System

- Generate transport bills
- Track student payments
- Apply late fee penalties
- Billing history management

### 📊 Reporting Module

- Route reports
- Vehicle utilization reports
- Revenue reports
- Registration statistics

### 💾 Persistent Storage

- File-based data management
- Automatic loading and saving of records

---

## 👨‍💻 Authors

| Name               | Registration Number |
| ------------------ | ------------------- |
| Muhammad Muaaz Ali | 2025-CS-708         |
| Maham Shahzadi     | 2025-CS-693         |

---

## 🛠️ Technologies Used

| Component    | Technology                  |
| ------------ | --------------------------- |
| Language     | C++                         |
| Standard     | C++17                       |
| Architecture | Object-Oriented Programming |
| Data Storage | Text Files                  |
| Compiler     | GCC / G++                   |
| Build Method | Command Line                |

---

## 🏗️ OOP Concepts Implemented

This project demonstrates:

- ✅ Classes & Objects
- ✅ Encapsulation
- ✅ Inheritance
- ✅ Polymorphism
- ✅ Abstraction
- ✅ Templates
- ✅ Dynamic Memory Allocation
- ✅ File Handling
- ✅ Modular Programming

---

## 📁 Project Structure

```text
UniversityTransportManagementSystem/
│
├── main.cpp
├── README.md
│
├── include/
│   ├── User.h
│   ├── Student.h
│   ├── Admin.h
│   ├── Vehicle.h
│   ├── Bus.h
│   ├── Van.h
│   ├── Route.h
│   ├── Bill.h
│   ├── TransportPass.h
│   ├── TemplateStorage.h
│   └── TransportManager.h
│
├── src/
│   ├── User.cpp
│   ├── Student.cpp
│   ├── Admin.cpp
│   ├── Vehicle.cpp
│   ├── Bus.cpp
│   ├── Van.cpp
│   ├── Route.cpp
│   ├── Bill.cpp
│   ├── TransportPass.cpp
│   └── TransportManager.cpp
│
└── data/
    ├── users.txt
    ├── vehicles.txt
    ├── routes.txt
    ├── registrations.txt
    └── bills.txt
```

---

## 🚀 Building the Project

### Compile Using G++

```bash
g++ -Iinclude main.cpp src/*.cpp -std=c++17 -o UniversityTransportManagementSystem
```

---

## ▶️ Running the Application

### Linux / macOS

```bash
./UniversityTransportManagementSystem
```

### Windows

```bash
UniversityTransportManagementSystem.exe
```

---

## 🔑 Default Administrator Account

Use the following credentials to access the administrator panel:

| Field    | Value      |
| -------- | ---------- |
| ID       | `admin`    |
| Password | `admin123` |

---

## 💾 Data Storage Files

The system stores runtime data inside the `data/` directory.

| File                | Purpose                   |
| ------------------- | ------------------------- |
| `users.txt`         | Student and admin records |
| `vehicles.txt`      | Vehicle information       |
| `routes.txt`        | Route information         |
| `registrations.txt` | Transport applications    |
| `bills.txt`         | Billing records           |

---

## 🏛️ System Modules

### 👤 User Module

Handles authentication and user management.

### 🎓 Student Module

Manages student registrations and transport requests.

### 👨‍💼 Admin Module

Provides administrative controls and approvals.

### 🚍 Vehicle Module

Maintains buses and vans assigned to routes.

### 🛣️ Route Module

Stores route details and transport assignments.

### 💳 Billing Module

Generates bills and calculates late fees.

### 🎫 Transport Pass Module

Issues and manages transport passes.

### 📈 Reporting Module

Generates operational and financial reports.

---

## 📌 Important Notes

- Keep all header files inside the `include/` directory.
- Keep all implementation files inside the `src/` directory.
- Keep all data files inside the `data/` directory.
- Runtime information is automatically loaded when the system starts.
- Changes are saved back to the data files during execution.
- Ensure all required data files exist before running the application.

---

## 🎯 Learning Outcomes

Through this project, the following software engineering concepts are demonstrated:

- Real-World System Modeling
- Transport Management Workflows
- Billing System Design
- Data Persistence Techniques
- Object-Oriented Design Patterns
- Scalable Modular Architecture
- File-Based Database Management

---

## 🎓 Academic Project

Developed as a university Object-Oriented Programming project to demonstrate the practical implementation of transportation management, billing automation, and software engineering principles using C++.

---

<div align="center">

### 🚌 University Transport Management & Billing System

Efficient • Organized • Scalable • Object-Oriented

⭐ If you found this project useful, consider giving it a star!

</div>
