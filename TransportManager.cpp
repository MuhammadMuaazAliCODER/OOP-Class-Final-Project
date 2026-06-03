#include "TransportManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

TransportManager::TransportManager()
    : usersFile("users.txt"),
      vehiclesFile("vehicles.txt"),
      routesFile("routes.txt"),
      registrationsFile("registrations.txt"),
      billsFile("bills.txt") {
    loadAllData();
}

TransportManager::~TransportManager() {
    for (User* user : users) {
        delete user;
    }
    for (Vehicle* vehicle : vehicles.getAll()) {
        delete vehicle;
    }
    for (Route* route : routes.getAll()) {
        delete route;
    }
    for (TransportPass* pass : registrations) {
        delete pass;
    }
    for (Bill* bill : bills) {
        delete bill;
    }
}

void TransportManager::loadAllData() {
    loadUsers();
    loadVehicles();
    loadRoutes();
    loadRegistrations();
    loadBills();
    attachTransportPasses();
}

void TransportManager::saveAllData() {
    saveUsers();
    saveVehicles();
    saveRoutes();
    saveRegistrations();
    saveBills();
}

void TransportManager::loadUsers() {
    ifstream file(usersFile);
    if (!file.is_open()) {
        createDefaultAdmin();
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> tokens = splitLine(line, ',');
        if (tokens.size() < 5) {
            continue;
        }

        string type = tokens[0];
        if (type == "Admin") {
            Admin* admin = new Admin(tokens[1], tokens[2], tokens[3], tokens[4]);
            users.push_back(admin);
        } else if (type == "Student" && tokens.size() >= 6) {
            int year = stoi(tokens[5]);
            Student* student = new Student(tokens[1], tokens[2], tokens[3], tokens[4], year);
            users.push_back(student);
        }
    }

    if (findAdminById("admin") == nullptr) {
        createDefaultAdmin();
    }
}

void TransportManager::loadVehicles() {
    ifstream file(vehiclesFile);
    if (!file.is_open()) {
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> tokens = splitLine(line, ',');
        if (tokens.size() < 6) {
            continue;
        }

        string type = tokens[0];
        string id = tokens[1];
        string model = tokens[2];
        int capacity = stoi(tokens[3]);
        bool feature = tokens[4] == "1";
        string assignedRoute = tokens[5];

        Vehicle* vehicle = nullptr;
        if (type == "Bus") {
            vehicle = new Bus(id, model, capacity, feature);
        } else if (type == "Van") {
            vehicle = new Van(id, model, capacity, feature);
        }
        if (vehicle != nullptr) {
            if (!assignedRoute.empty()) {
                vehicle->setAssignedRouteId(assignedRoute);
            }
            vehicles.add(vehicle);
        }
    }
}

void TransportManager::loadRoutes() {
    ifstream file(routesFile);
    if (!file.is_open()) {
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> tokens = splitLine(line, ',');
        if (tokens.size() < 4) {
            continue;
        }

        string id = tokens[0];
        string name = tokens[1];
        double distance = stod(tokens[2]);
        string assignedVehicle = tokens[3];
        int usageCount = 0;
        if (tokens.size() >= 5) {
            usageCount = stoi(tokens[4]);
        }

        Route* route = new Route(id, name, distance);
        if (!assignedVehicle.empty()) {
            route->setAssignedVehicleId(assignedVehicle);
        }
        for (int idx = 0; idx < usageCount; idx++) {
            route->incrementUsage();
        }
        routes.add(route);
    }
}

void TransportManager::loadRegistrations() {
    ifstream file(registrationsFile);
    if (!file.is_open()) {
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> tokens = splitLine(line, ',');
        if (tokens.size() < 4) {
            continue;
        }

        TransportPass* pass = new TransportPass(tokens[0], tokens[1], tokens[2], tokens[3]);
        registrations.push_back(pass);
    }
}

void TransportManager::loadBills() {
    ifstream file(billsFile);
    if (!file.is_open()) {
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> tokens = splitLine(line, ',');
        if (tokens.size() < 9) {
            continue;
        }

        Bill* bill = new Bill(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], stod(tokens[6]), stod(tokens[7]), stod(tokens[8]));
        bills.push_back(bill);

        TransportPass* pass = findRegistrationByStudentId(tokens[1]);
        if (pass != nullptr && pass->getRouteId() == tokens[2]) {
            pass->assignBill(*bill);
        }
    }
}

void TransportManager::attachTransportPasses() {
    for (TransportPass* pass : registrations) {
        Student* student = findStudentById(pass->getStudentId());
        if (student != nullptr) {
            student->setTransportPass(pass);
        }
    }
}

void TransportManager::createDefaultAdmin() {
    if (findAdminById("admin") == nullptr) {
        Admin* admin = new Admin("admin", "System Admin", "admin@example.com", "admin123");
        users.push_back(admin);
    }
}

void TransportManager::saveUsers() {
    ofstream file(usersFile);
    if (!file.is_open()) {
        cout << "Unable to save users.txt" << endl;
        return;
    }

    for (User* user : users) {
        if (Admin* admin = dynamic_cast<Admin*>(user)) {
            file << "Admin," << admin->getId() << "," << admin->getName() << "," << admin->getEmail() << ",";
            file << admin->getPassword() << '\n';
        } else if (Student* student = dynamic_cast<Student*>(user)) {
            file << "Student," << student->getId() << "," << student->getName() << "," << student->getEmail() << ",";
            file << student->getPassword() << "," << student->getYear() << '\n';
        }
    }
}

void TransportManager::saveVehicles() {
    ofstream file(vehiclesFile);
    if (!file.is_open()) {
        cout << "Unable to save vehicles.txt" << endl;
        return;
    }

    for (Vehicle* vehicle : vehicles.getAll()) {
        string type = vehicle->getType();
        string feature = "0";
        if (Bus* bus = dynamic_cast<Bus*>(vehicle)) {
            feature = bus->getHasAC() ? "1" : "0";
        } else if (Van* van = dynamic_cast<Van*>(vehicle)) {
            feature = van->getHasLuggageSpace() ? "1" : "0";
        }
        file << type << "," << vehicle->getId() << "," << vehicle->getModel() << "," << vehicle->getCapacity() << ",";
        file << feature << "," << vehicle->getAssignedRouteId() << '\n';
    }
}

void TransportManager::saveRoutes() {
    ofstream file(routesFile);
    if (!file.is_open()) {
        cout << "Unable to save routes.txt" << endl;
        return;
    }

    for (Route* route : routes.getAll()) {
        file << route->getId() << "," << route->getName() << "," << route->getDistance() << "," << route->getAssignedVehicleId() << "," << route->getUsageCount() << '\n';
    }
}

void TransportManager::saveRegistrations() {
    ofstream file(registrationsFile);
    if (!file.is_open()) {
        cout << "Unable to save registrations.txt" << endl;
        return;
    }

    for (TransportPass* pass : registrations) {
        file << pass->getPassId() << "," << pass->getStudentId() << "," << pass->getRouteId() << "," << pass->getStatus() << '\n';
    }
}

void TransportManager::saveBills() {
    ofstream file(billsFile);
    if (!file.is_open()) {
        cout << "Unable to save bills.txt" << endl;
        return;
    }

    for (Bill* bill : bills) {
        file << bill->getBillId() << "," << bill->getStudentId() << "," << bill->getRouteId() << "," << bill->getIssueDate() << "," << bill->getDueDate() << "," << bill->getStatus() << ",";
        file << bill->getAmount() << "," << bill->getLateFine() << "," << bill->getTotalAmount() << '\n';
    }
}

User* TransportManager::findUserById(const string& id) const {
    for (User* user : users) {
        if (user->getId() == id) {
            return user;
        }
    }
    return nullptr;
}

Student* TransportManager::findStudentById(const string& id) const {
    for (User* user : users) {
        Student* student = dynamic_cast<Student*>(user);
        if (student != nullptr && student->getId() == id) {
            return student;
        }
    }
    return nullptr;
}

Admin* TransportManager::findAdminById(const string& id) const {
    for (User* user : users) {
        Admin* admin = dynamic_cast<Admin*>(user);
        if (admin != nullptr && admin->getId() == id) {
            return admin;
        }
    }
    return nullptr;
}

Vehicle* TransportManager::findVehicleById(const string& id) const {
    for (Vehicle* vehicle : vehicles.getAll()) {
        if (vehicle->getId() == id) {
            return vehicle;
        }
    }
    return nullptr;
}

Route* TransportManager::findRouteById(const string& id) const {
    for (Route* route : routes.getAll()) {
        if (route->getId() == id) {
            return route;
        }
    }
    return nullptr;
}

TransportPass* TransportManager::findRegistrationByPassId(const string& passId) const {
    for (TransportPass* pass : registrations) {
        if (pass->getPassId() == passId) {
            return pass;
        }
    }
    return nullptr;
}

TransportPass* TransportManager::findRegistrationByStudentId(const string& studentId) const {
    for (TransportPass* pass : registrations) {
        if (pass->getStudentId() == studentId) {
            return pass;
        }
    }
    return nullptr;
}

int TransportManager::countApprovedBookings(const string& routeId) const {
    int count = 0;
    for (TransportPass* pass : registrations) {
        if (pass->getRouteId() == routeId && pass->getStatus() == "Approved") {
            count++;
        }
    }
    return count;
}

void TransportManager::updateRouteUsage(const string& routeId) {
    Route* route = findRouteById(routeId);
    if (route != nullptr) {
        route->incrementUsage();
    }
}

vector<string> TransportManager::splitLine(const string& line, char delimiter) const {
    vector<string> tokens;
    stringstream reader(line);
    string value;
    while (getline(reader, value, delimiter)) {
        tokens.push_back(value);
    }
    return tokens;
}

string TransportManager::generatePassId() const {
    return "P" + to_string(registrations.size() + 1);
}

string TransportManager::generateBillId() const {
    return "B" + to_string(bills.size() + 1);
}

void TransportManager::displayRoutes() const {
    cout << "\nAvailable Routes:" << endl;
    for (Route* route : routes.getAll()) {
        cout << "Route ID: " << route->getId() << " | Name: " << route->getName()
                  << " | Distance: " << route->getDistance() << " km | Assigned Vehicle: "
                  << (route->getAssignedVehicleId().empty() ? "None" : route->getAssignedVehicleId())
                  << " | Usage: " << route->getUsageCount() << endl;
    }
}

void TransportManager::displayVehicles() const {
    cout << "\nRegistered Vehicles:" << endl;
    for (Vehicle* vehicle : vehicles.getAll()) {
        vehicle->display();
    }
}

void TransportManager::displayApplications() const {
    cout << "\nTransport Applications:" << endl;
    for (TransportPass* pass : registrations) {
        if (pass->getStatus() == "Pending") {
            cout << "Pass ID: " << pass->getPassId() << " | Student ID: " << pass->getStudentId()
                      << " | Route ID: " << pass->getRouteId() << " | Status: " << pass->getStatus() << endl;
        }
    }
}

void TransportManager::displayReports() const {
    double totalRevenue = 0.0;
    for (Bill* bill : bills) {
        totalRevenue += bill->getTotalAmount();
    }

    cout << "\n---- Revenue Report ----" << endl;
    cout << "Total Revenue: " << totalRevenue << " currency units" << endl;

    cout << "\n---- Route Usage Report ----" << endl;
    for (Route* route : routes.getAll()) {
        cout << "Route " << route->getId() << " (" << route->getName() << "): " << route->getUsageCount() << " bookings" << endl;
    }

    cout << "\n---- Vehicle Usage Report ----" << endl;
    for (Vehicle* vehicle : vehicles.getAll()) {
        int routeBookings = 0;
        string routeId = vehicle->getAssignedRouteId();
        if (!routeId.empty()) {
            routeBookings = countApprovedBookings(routeId);
        }
        cout << vehicle->getType() << " " << vehicle->getId() << " assigned to "
                  << (routeId.empty() ? "None" : routeId) << " has " << routeBookings << " approved bookings" << endl;
    }
}

void TransportManager::adminAddVehicle() {
    string type;
    cout << "Enter vehicle type (Bus/Van): ";
    getline(cin, type);
    string id, model;
    int capacity;
    cout << "Enter vehicle ID: ";
    getline(cin, id);
    cout << "Enter model name: ";
    getline(cin, model);
    cout << "Enter capacity: ";
    cin >> capacity;
    cin.ignore();

    if (findVehicleById(id) != nullptr) {
        cout << "A vehicle with this ID already exists." << endl;
        return;
    }

    if (type == "Bus") {
        char acOption;
        cout << "Does the bus have AC? (Y/N): ";
        cin >> acOption;
        cin.ignore();
        bool hasAC = (acOption == 'Y' || acOption == 'y');
        vehicles.add(new Bus(id, model, capacity, hasAC));
        cout << "Bus added successfully." << endl;
    } else if (type == "Van") {
        char luggageOption;
        cout << "Does the van have luggage space? (Y/N): ";
        cin >> luggageOption;
        cin.ignore();
        bool luggage = (luggageOption == 'Y' || luggageOption == 'y');
        vehicles.add(new Van(id, model, capacity, luggage));
        cout << "Van added successfully." << endl;
    } else {
        cout << "Invalid vehicle type." << endl;
    }
}

void TransportManager::adminEditVehicle() {
    string id;
    cout << "Enter vehicle ID to edit: ";
    getline(cin, id);
    Vehicle* vehicle = findVehicleById(id);
    if (vehicle == nullptr) {
        cout << "Vehicle not found." << endl;
        return;
    }

    string model;
    int capacity;
    cout << "Enter new model name: ";
    getline(cin, model);
    cout << "Enter new capacity: ";
    cin >> capacity;
    cin.ignore();

    vehicle->setModel(model);
    vehicle->setCapacity(capacity);
    cout << "Vehicle updated successfully." << endl;
}

void TransportManager::adminRemoveVehicle() {
    string id;
    cout << "Enter vehicle ID to remove: ";
    getline(cin, id);
    Vehicle* vehicle = findVehicleById(id);
    if (vehicle == nullptr) {
        cout << "Vehicle not found." << endl;
        return;
    }

    if (!vehicle->getAssignedRouteId().empty()) {
        cout << "Cannot remove a vehicle assigned to a route." << endl;
        return;
    }

    vehicles.remove(vehicle);
    delete vehicle;
    cout << "Vehicle removed." << endl;
}

void TransportManager::adminAddRoute() {
    string id, name;
    double distance;
    cout << "Enter route ID: ";
    getline(cin, id);
    if (findRouteById(id) != nullptr) {
        cout << "A route with this ID already exists." << endl;
        return;
    }

    cout << "Enter route name: ";
    getline(cin, name);
    cout << "Enter distance in km: ";
    cin >> distance;
    cin.ignore();

    routes.add(new Route(id, name, distance));
    cout << "Route created successfully." << endl;
}

void TransportManager::adminAssignVehicle() {
    string vehicleId;
    cout << "Enter vehicle ID to assign: ";
    getline(cin, vehicleId);
    Vehicle* vehicle = findVehicleById(vehicleId);
    if (vehicle == nullptr) {
        cout << "Vehicle not found." << endl;
        return;
    }

    string routeId;
    cout << "Enter route ID to assign to: ";
    getline(cin, routeId);
    Route* route = findRouteById(routeId);
    if (route == nullptr) {
        cout << "Route not found." << endl;
        return;
    }

    if (!vehicle->getAssignedRouteId().empty()) {
        cout << "Vehicle is already assigned to another route." << endl;
        return;
    }
    if (!route->getAssignedVehicleId().empty()) {
        cout << "Route already has a vehicle assigned." << endl;
        return;
    }

    vehicle->setAssignedRouteId(routeId);
    route->setAssignedVehicleId(vehicleId);
    cout << "Vehicle assigned to route successfully." << endl;
}

void TransportManager::adminViewApplications() {
    displayApplications();
}

void TransportManager::adminApproveRequest() {
    string passId;
    cout << "Enter pass ID to approve: ";
    getline(cin, passId);
    TransportPass* pass = findRegistrationByPassId(passId);
    if (pass == nullptr) {
        cout << "Transport request not found." << endl;
        return;
    }
    if (pass->getStatus() != "Pending") {
        cout << "Only pending requests may be approved." << endl;
        return;
    }

    Route* route = findRouteById(pass->getRouteId());
    if (route == nullptr || route->getAssignedVehicleId().empty()) {
        cout << "Route is not valid or does not have an assigned vehicle." << endl;
        return;
    }

    Vehicle* vehicle = findVehicleById(route->getAssignedVehicleId());
    if (vehicle == nullptr) {
        cout << "Assigned vehicle not found." << endl;
        return;
    }

    int approvedCount = countApprovedBookings(route->getId());
    if (approvedCount >= vehicle->getCapacity()) {
        cout << "Cannot approve this request. The assigned vehicle is full." << endl;
        return;
    }

    pass->approve();
    updateRouteUsage(route->getId());

    Bill* newBill = new Bill(generateBillId(), pass->getStudentId(), pass->getRouteId(), "2026-06-01", "2026-06-10", "Unpaid", 0.0, 0.0, 0.0);
    newBill->calculateFee(route->getDistance());
    newBill->applyLateFine(0);
    pass->assignBill(*newBill);
    bills.push_back(newBill);

    cout << "Request approved and bill generated." << endl;
}

void TransportManager::adminRejectRequest() {
    string passId;
    cout << "Enter pass ID to reject: ";
    getline(cin, passId);
    TransportPass* pass = findRegistrationByPassId(passId);
    if (pass == nullptr) {
        cout << "Transport request not found." << endl;
        return;
    }
    if (pass->getStatus() != "Pending") {
        cout << "Only pending requests may be rejected." << endl;
        return;
    }

    pass->reject();
    cout << "Request rejected." << endl;
}

void TransportManager::adminGenerateReports() {
    displayReports();
}

void TransportManager::adminSaveData() {
    saveAllData();
    cout << "All data saved successfully." << endl;
}

void TransportManager::studentViewRoutes(Student* student) const {
    displayRoutes();
}

void TransportManager::studentApplyForTransport(Student* student) {
    if (student->hasTransportPass()) {
        cout << "You already have an application or registration." << endl;
        return;
    }

    string routeId;
    cout << "Enter route ID to apply for: ";
    getline(cin, routeId);
    Route* route = findRouteById(routeId);
    if (route == nullptr) {
        cout << "Route not found." << endl;
        return;
    }
    if (route->getAssignedVehicleId().empty()) {
        cout << "This route does not have a vehicle assigned yet." << endl;
        return;
    }

    Vehicle* vehicle = findVehicleById(route->getAssignedVehicleId());
    if (vehicle == nullptr) {
        cout << "Assigned vehicle not found." << endl;
        return;
    }

    int approvedCount = countApprovedBookings(routeId);
    if (approvedCount >= vehicle->getCapacity()) {
        cout << "Cannot apply. The route is fully booked." << endl;
        return;
    }

    TransportPass* pass = new TransportPass(generatePassId(), student->getId(), routeId, "Pending");
    registrations.push_back(pass);
    student->setTransportPass(pass);
    cout << "Application submitted successfully. Pass ID: " << pass->getPassId() << endl;
}

void TransportManager::studentViewRegistration(Student* student) const {
    if (!student->hasTransportPass()) {
        cout << "You have not applied for transport yet." << endl;
        return;
    }
    TransportPass* pass = student->getTransportPass();
    cout << "Registration Status: " << pass->getStatus() << endl;
    cout << "Pass ID: " << pass->getPassId() << " | Route ID: " << pass->getRouteId() << endl;
    if (pass->hasBill()) {
        Bill bill = pass->getBill();
        cout << bill;
    }
}

void TransportManager::studentCancelRegistration(Student* student) {
    if (!student->hasTransportPass()) {
        cout << "You do not have a registration to cancel." << endl;
        return;
    }
    TransportPass* pass = student->getTransportPass();
    if (pass->getStatus() == "Approved" || pass->getStatus() == "Pending") {
        pass->cancel();
        student->clearTransportPass();
        cout << "Your registration has been cancelled." << endl;
    } else {
        cout << "This registration cannot be cancelled." << endl;
    }
}

void TransportManager::runMainMenu() {
    bool finished = false;
    while (!finished) {
        cout << "\n=== University Transport Management System ===" << endl;
        cout << "1. Register User" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Select an option: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string id, name, email, password;
                int year;
                cout << "Enter student ID: ";
                getline(cin, id);
                if (findUserById(id) != nullptr) {
                    cout << "User ID already exists." << endl;
                    break;
                }
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter email: ";
                getline(cin, email);
                cout << "Enter password: ";
                getline(cin, password);
                cout << "Enter year of study: ";
                cin >> year;
                cin.ignore();

                Student* student = new Student(id, name, email, password, year);
                users.push_back(student);
                cout << "Student registered successfully." << endl;
                break;
            }
            case 2: {
                string id, password;
                cout << "Enter user ID: ";
                getline(cin, id);
                cout << "Enter password: ";
                getline(cin, password);
                User* user = findUserById(id);
                if (user == nullptr || !user->authenticate(password)) {
                    cout << "Invalid ID or password." << endl;
                    break;
                }
                if (dynamic_cast<Student*>(user)) {
                    bool loggedOut = false;
                    while (!loggedOut) {
                        cout << "\n--- Student Menu ---" << endl;
                        cout << "1. View Routes" << endl;
                        cout << "2. Apply For Transport" << endl;
                        cout << "3. View Registration" << endl;
                        cout << "4. Cancel Registration" << endl;
                        cout << "5. Logout" << endl;
                        cout << "Select an option: ";
                        int studentChoice;
                        cin >> studentChoice;
                        cin.ignore();
                        Student* student = dynamic_cast<Student*>(user);
                        switch (studentChoice) {
                            case 1:
                                studentViewRoutes(student);
                                break;
                            case 2:
                                studentApplyForTransport(student);
                                break;
                            case 3:
                                studentViewRegistration(student);
                                break;
                            case 4:
                                studentCancelRegistration(student);
                                break;
                            case 5:
                                loggedOut = true;
                                break;
                            default:
                                cout << "Invalid choice." << endl;
                        }
                    }
                } else if (dynamic_cast<Admin*>(user)) {
                    bool loggedOut = false;
                    while (!loggedOut) {
                        cout << "\n--- Admin Menu ---" << endl;
                        cout << "1. Add Vehicle" << endl;
                        cout << "2. Edit Vehicle" << endl;
                        cout << "3. Remove Vehicle" << endl;
                        cout << "4. Add Route" << endl;
                        cout << "5. Assign Vehicle" << endl;
                        cout << "6. View Applications" << endl;
                        cout << "7. Approve Request" << endl;
                        cout << "8. Reject Request" << endl;
                        cout << "9. Generate Reports" << endl;
                        cout << "10. Save Data" << endl;
                        cout << "11. Logout" << endl;
                        cout << "Select an option: ";
                        int adminChoice;
                        cin >> adminChoice;
                        cin.ignore();
                        switch (adminChoice) {
                            case 1:
                                adminAddVehicle();
                                break;
                            case 2:
                                adminEditVehicle();
                                break;
                            case 3:
                                adminRemoveVehicle();
                                break;
                            case 4:
                                adminAddRoute();
                                break;
                            case 5:
                                adminAssignVehicle();
                                break;
                            case 6:
                                adminViewApplications();
                                break;
                            case 7:
                                adminApproveRequest();
                                break;
                            case 8:
                                adminRejectRequest();
                                break;
                            case 9:
                                adminGenerateReports();
                                break;
                            case 10:
                                adminSaveData();
                                break;
                            case 11:
                                loggedOut = true;
                                break;
                            default:
                                cout << "Invalid choice." << endl;
                        }
                    }
                }
                break;
            }
            case 3:
                saveAllData();
                cout << "Exiting system. Data saved." << endl;
                finished = true;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    }
}
