#include "../include/TransportManager.h"
#include "../include/User.h"
#include "../include/Admin.h"
#include "../include/Student.h"
#include "../include/Vehicle.h"
#include "../include/Bus.h"
#include "../include/Van.h"
#include "../include/Route.h"
#include "../include/TransportPass.h"
#include "../include/Bill.h"
#include "../include/InputHelper.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

TransportManager::TransportManager()
    : usersFile("data/users.txt"),
      vehiclesFile("data/vehicles.txt"),
      routesFile("data/routes.txt"),
      registrationsFile("data/registrations.txt"),
      billsFile("data/bills.txt")
{
    loadAllData();
}

TransportManager::~TransportManager()
{
    for (User *user : users)
    {
        delete user;
    }
    for (Vehicle *vehicle : vehicles.getAll())
    {
        delete vehicle;
    }
    for (Route *route : routes.getAll())
    {
        delete route;
    }
    for (TransportPass *pass : registrations)
    {
        delete pass;
    }
    for (Bill *bill : bills)
    {
        delete bill;
    }
}

void TransportManager::loadAllData()
{
    loadUsers();
    loadVehicles();
    loadRoutes();
    loadRegistrations();
    loadBills();
    attachTransportPasses();
}

void TransportManager::saveAllData()
{
    saveUsers();
    saveVehicles();
    saveRoutes();
    saveRegistrations();
    saveBills();
}

void TransportManager::loadUsers()
{
    ifstream file(usersFile);
    if (!file.is_open())
    {
        createDefaultAdmin();
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string type, id, name, email, password, yearText;
        if (!getline(ss, type, ',') || !getline(ss, id, ',') || !getline(ss, name, ',') ||
            !getline(ss, email, ',') || !getline(ss, password, ','))
        {
            continue;
        }

        if (type == "Admin")
        {
            Admin *admin = new Admin(id, name, email, password);
            users.push_back(admin);
        }
        else if (type == "Student" && getline(ss, yearText, ','))
        {
            int year = stoi(yearText);
            Student *student = new Student(id, name, email, password, year);
            users.push_back(student);
        }
    }

    if (findAdminById("admin") == nullptr)
    {
        createDefaultAdmin();
    }
}

void TransportManager::loadVehicles()
{
    ifstream file(vehiclesFile);
    if (!file.is_open())
    {
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string type, id, model, capacityText, featureText, assignedRoute;
        if (!getline(ss, type, ',') || !getline(ss, id, ',') || !getline(ss, model, ',') ||
            !getline(ss, capacityText, ',') || !getline(ss, featureText, ',') ||
            !getline(ss, assignedRoute, ','))
        {
            continue;
        }

        int capacity = stoi(capacityText);
        bool feature = featureText == "1";

        Vehicle *vehicle = nullptr;
        if (type == "Bus")
        {
            vehicle = new Bus(id, model, capacity, feature);
        }
        else if (type == "Van")
        {
            vehicle = new Van(id, model, capacity, feature);
        }
        if (vehicle != nullptr)
        {
            if (!assignedRoute.empty())
            {
                vehicle->setAssignedRouteId(assignedRoute);
            }
            vehicles.add(vehicle);
        }
    }
}

void TransportManager::loadRoutes()
{
    ifstream file(routesFile);
    if (!file.is_open())
    {
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, distanceText, assignedVehicle, usageCountText;
        if (!getline(ss, id, ',') || !getline(ss, name, ',') || !getline(ss, distanceText, ',') ||
            !getline(ss, assignedVehicle, ','))
        {
            continue;
        }

        double distance = stod(distanceText);
        int usageCount = 0;
        if (getline(ss, usageCountText, ','))
        {
            usageCount = stoi(usageCountText);
        }

        Route *route = new Route(id, name, distance);
        if (!assignedVehicle.empty())
        {
            route->setAssignedVehicleId(assignedVehicle);
        }
        for (int idx = 0; idx < usageCount; idx++)
        {
            route->incrementUsage();
        }
        routes.add(route);
    }
}

void TransportManager::loadRegistrations()
{
    ifstream file(registrationsFile);
    if (!file.is_open())
    {
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string passId, studentId, routeId, status;
        if (!getline(ss, passId, ',') || !getline(ss, studentId, ',') ||
            !getline(ss, routeId, ',') || !getline(ss, status, ','))
        {
            continue;
        }

        TransportPass *pass = new TransportPass(passId, studentId, routeId, status);
        registrations.push_back(pass);
    }
}

void TransportManager::loadBills()
{
    ifstream file(billsFile);
    if (!file.is_open())
    {
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string billId, studentId, routeId, issueDate, dueDate, status, amountText, lateFineText, totalAmountText;
        if (!getline(ss, billId, ',') || !getline(ss, studentId, ',') || !getline(ss, routeId, ',') ||
            !getline(ss, issueDate, ',') || !getline(ss, dueDate, ',') || !getline(ss, status, ',') ||
            !getline(ss, amountText, ',') || !getline(ss, lateFineText, ',') ||
            !getline(ss, totalAmountText, ','))
        {
            continue;
        }

        Bill *bill = new Bill(billId, studentId, routeId, issueDate, dueDate, status,
                              stod(amountText), stod(lateFineText), stod(totalAmountText));
        bills.push_back(bill);

        TransportPass *pass = findRegistrationByStudentId(studentId);
        if (pass != nullptr && pass->getRouteId() == routeId)
        {
            pass->assignBill(*bill);
        }
    }
}

void TransportManager::attachTransportPasses()
{
    for (TransportPass *pass : registrations)
    {
        Student *student = findStudentById(pass->getStudentId());
        if (student != nullptr)
        {
            student->setTransportPass(pass);
        }
    }
}

void TransportManager::createDefaultAdmin()
{
    if (findAdminById("admin") == nullptr)
    {
        Admin *admin = new Admin("admin", "System Admin", "admin@example.com", "admin123");
        users.push_back(admin);
    }
}

void TransportManager::saveUsers()
{
    ofstream file(usersFile);
    if (!file.is_open())
    {
        cout << "Unable to save data/users.txt" << endl;
        return;
    }

    for (User *user : users)
    {
        if (Admin *admin = dynamic_cast<Admin *>(user))
        {
            file << "Admin," << admin->getId() << "," << admin->getName() << "," << admin->getEmail() << ",";
            file << admin->getPassword() << '\n';
        }
        else if (Student *student = dynamic_cast<Student *>(user))
        {
            file << "Student," << student->getId() << "," << student->getName() << "," << student->getEmail() << ",";
            file << student->getPassword() << "," << student->getYear() << '\n';
        }
    }
}

void TransportManager::saveVehicles()
{
    ofstream file(vehiclesFile);
    if (!file.is_open())
    {
        cout << "Unable to save data/vehicles.txt" << endl;
        return;
    }

    for (Vehicle *vehicle : vehicles.getAll())
    {
        string type = vehicle->getType();
        string feature = "0";
        if (Bus *bus = dynamic_cast<Bus *>(vehicle))
        {
            feature = bus->getHasAC() ? "1" : "0";
        }
        else if (Van *van = dynamic_cast<Van *>(vehicle))
        {
            feature = van->getHasLuggageSpace() ? "1" : "0";
        }
        file << type << "," << vehicle->getId() << "," << vehicle->getModel() << "," << vehicle->getCapacity() << ",";
        file << feature << "," << vehicle->getAssignedRouteId() << '\n';
    }
}

void TransportManager::saveRoutes()
{
    ofstream file(routesFile);
    if (!file.is_open())
    {
        cout << "Unable to save data/routes.txt" << endl;
        return;
    }

    for (Route *route : routes.getAll())
    {
        file << route->getId() << "," << route->getName() << "," << route->getDistance() << "," << route->getAssignedVehicleId() << "," << route->getUsageCount() << '\n';
    }
}

void TransportManager::saveRegistrations()
{
    ofstream file(registrationsFile);
    if (!file.is_open())
    {
        cout << "Unable to save data/registrations.txt" << endl;
        return;
    }

    for (TransportPass *pass : registrations)
    {
        file << pass->getPassId() << "," << pass->getStudentId() << "," << pass->getRouteId() << "," << pass->getStatus() << '\n';
    }
}

void TransportManager::saveBills()
{
    ofstream file(billsFile);
    if (!file.is_open())
    {
        cout << "Unable to save data/bills.txt" << endl;
        return;
    }

    for (Bill *bill : bills)
    {
        file << bill->getBillId() << "," << bill->getStudentId() << "," << bill->getRouteId() << "," << bill->getIssueDate() << "," << bill->getDueDate() << "," << bill->getStatus() << ",";
        file << bill->getAmount() << "," << bill->getLateFine() << "," << bill->getTotalAmount() << '\n';
    }
}

User *TransportManager::findUserById(const string &id) const
{
    for (User *user : users)
    {
        if (user->getId() == id)
        {
            return user;
        }
    }
    return nullptr;
}

Student *TransportManager::findStudentById(const string &id) const
{
    for (User *user : users)
    {
        Student *student = dynamic_cast<Student *>(user);
        if (student != nullptr && student->getId() == id)
        {
            return student;
        }
    }
    return nullptr;
}

Admin *TransportManager::findAdminById(const string &id) const
{
    for (User *user : users)
    {
        Admin *admin = dynamic_cast<Admin *>(user);
        if (admin != nullptr && admin->getId() == id)
        {
            return admin;
        }
    }
    return nullptr;
}

Vehicle *TransportManager::findVehicleById(const string &id) const
{
    for (Vehicle *vehicle : vehicles.getAll())
    {
        if (vehicle->getId() == id)
        {
            return vehicle;
        }
    }
    return nullptr;
}

Route *TransportManager::findRouteById(const string &id) const
{
    for (Route *route : routes.getAll())
    {
        if (route->getId() == id)
        {
            return route;
        }
    }
    return nullptr;
}

TransportPass *TransportManager::findRegistrationByPassId(const string &passId) const
{
    for (TransportPass *pass : registrations)
    {
        if (pass->getPassId() == passId)
        {
            return pass;
        }
    }
    return nullptr;
}

TransportPass *TransportManager::findRegistrationByStudentId(const string &studentId) const
{
    for (TransportPass *pass : registrations)
    {
        if (pass->getStudentId() == studentId)
        {
            return pass;
        }
    }
    return nullptr;
}

int TransportManager::countApprovedBookings(const string &routeId) const
{
    int count = 0;
    for (TransportPass *pass : registrations)
    {
        if (pass->getRouteId() == routeId && pass->getStatus() == "Approved")
        {
            count++;
        }
    }
    return count;
}

void TransportManager::updateRouteUsage(const string &routeId)
{
    Route *route = findRouteById(routeId);
    if (route != nullptr)
    {
        route->incrementUsage();
    }
}

string TransportManager::generatePassId() const
{
    return "P" + to_string(registrations.size() + 1);
}

string TransportManager::generateBillId() const
{
    return "B" + to_string(bills.size() + 1);
}

void TransportManager::displayRoutes() const
{
    cout << "\nAvailable Routes:" << endl;
    for (Route *route : routes.getAll())
    {
        cout << "Route ID: " << route->getId() << " | Name: " << route->getName()
             << " | Distance: " << route->getDistance() << " km | Assigned Vehicle: "
             << (route->getAssignedVehicleId().empty() ? "None" : route->getAssignedVehicleId())
             << " | Usage: " << route->getUsageCount() << endl;
    }
}

void TransportManager::displayVehicles() const
{
    cout << "\nRegistered Vehicles:" << endl;
    for (Vehicle *vehicle : vehicles.getAll())
    {
        vehicle->display();
    }
}

void TransportManager::displayApplications() const
{
    cout << "\nTransport Applications:" << endl;
    for (TransportPass *pass : registrations)
    {
        if (pass->getStatus() == "Pending")
        {
            cout << "Pass ID: " << pass->getPassId() << " | Student ID: " << pass->getStudentId()
                 << " | Route ID: " << pass->getRouteId() << " | Status: " << pass->getStatus() << endl;
        }
    }
}

void TransportManager::displayReports() const
{
    double totalRevenue = 0.0;
    for (Bill *bill : bills)
    {
        totalRevenue += bill->getTotalAmount();
    }

    cout << "\n---- Revenue Report ----" << endl;
    cout << "Total Revenue: " << totalRevenue << " currency units" << endl;

    cout << "\n---- Route Usage Report ----" << endl;
    for (Route *route : routes.getAll())
    {
        cout << "Route " << route->getId() << " (" << route->getName() << "): " << route->getUsageCount() << " bookings" << endl;
    }

    cout << "\n---- Vehicle Usage Report ----" << endl;
    for (Vehicle *vehicle : vehicles.getAll())
    {
        int routeBookings = 0;
        string routeId = vehicle->getAssignedRouteId();
        if (!routeId.empty())
        {
            routeBookings = countApprovedBookings(routeId);
        }
        cout << vehicle->getType() << " " << vehicle->getId() << " assigned to "
             << (routeId.empty() ? "None" : routeId) << " has " << routeBookings << " approved bookings" << endl;
    }
}

void TransportManager::adminAddVehicle()
{
    cout << "\n=== Add New Vehicle ===" << endl;

    // Select vehicle type from menu
    string type = InputHelper::selectVehicleType();

    // Get validated vehicle ID
    string id = InputHelper::getVehicleId("Enter Vehicle ID (e.g., BUS001, VAN123, BUS321): ");

    if (findVehicleById(id) != nullptr)
    {
        cout << "Error: A vehicle with ID '" << id << "' already exists." << endl;
        return;
    }

    // Get validated model name
    string model = InputHelper::getModelName("Enter Model Name (e.g., Toyota Hiace): ");

    // Get validated capacity
    int capacity = InputHelper::getCapacity("Enter Capacity (5-100 passengers): ");

    if (type == "Bus")
    {
        bool hasAC = InputHelper::selectYesNo("Does the bus have AC?");
        vehicles.add(new Bus(id, model, capacity, hasAC));
        cout << "✓ Bus added successfully!" << endl;
        cout << "  ID: " << id << " | Model: " << model << " | Capacity: " << capacity << " | AC: " << (hasAC ? "Yes" : "No") << endl;
    }
    else if (type == "Van")
    {
        bool hasLuggage = InputHelper::selectYesNo("Does the van have luggage space?");
        vehicles.add(new Van(id, model, capacity, hasLuggage));
        cout << "✓ Van added successfully!" << endl;
        cout << "  ID: " << id << " | Model: " << model << " | Capacity: " << capacity << " | Luggage: " << (hasLuggage ? "Yes" : "No") << endl;
    }
}

void TransportManager::adminEditVehicle()
{
    cout << "\n=== Edit Vehicle ===" << endl;
    displayVehicles();

    vector<string> vehicleOptions;
    vector<Vehicle *> availableVehicles;
    for (Vehicle *v : vehicles.getAll())
    {
        vehicleOptions.push_back(v->getId() + " (" + v->getType() + " - " + v->getModel() + ")");
        availableVehicles.push_back(v);
    }

    if (availableVehicles.empty())
    {
        cout << "No vehicles available to edit." << endl;
        return;
    }

    int index = InputHelper::selectFromMenu(vehicleOptions, "Select Vehicle to Edit:");
    Vehicle *vehicle = availableVehicles[index];

    string model = InputHelper::getModelName("Enter new Model Name: ");
    int capacity = InputHelper::getCapacity("Enter new Capacity (5-100): ");

    vehicle->setModel(model);
    vehicle->setCapacity(capacity);
    cout << "✓ Vehicle updated successfully!" << endl;
}

void TransportManager::adminRemoveVehicle()
{
    cout << "\n=== Remove Vehicle ===" << endl;
    displayVehicles();

    vector<string> vehicleOptions;
    vector<Vehicle *> availableVehicles;
    for (Vehicle *v : vehicles.getAll())
    {
        vehicleOptions.push_back(v->getId() + " (" + v->getType() + " - " + v->getModel() + ")");
        availableVehicles.push_back(v);
    }

    if (availableVehicles.empty())
    {
        cout << "No vehicles available to remove." << endl;
        return;
    }

    int index = InputHelper::selectFromMenu(vehicleOptions, "Select Vehicle to Remove:");
    Vehicle *vehicle = availableVehicles[index];

    if (!vehicle->getAssignedRouteId().empty())
    {
        cout << "Error: Cannot remove a vehicle assigned to a route." << endl;
        return;
    }

    vehicles.remove(vehicle);
    delete vehicle;
    cout << "✓ Vehicle removed successfully!" << endl;
}

void TransportManager::adminAddRoute()
{
    cout << "\n=== Add New Route ===" << endl;

    string id = InputHelper::getRouteId("Enter Route ID (format: R### e.g., R001): ");
    if (findRouteById(id) != nullptr)
    {
        cout << "Error: A route with ID '" << id << "' already exists." << endl;
        return;
    }

    string name = InputHelper::getRouteName("Enter Route Name (e.g., City Center Route): ");
    double distance = InputHelper::getDistance("Enter Distance in km (1-500): ");

    routes.add(new Route(id, name, distance));
    cout << "✓ Route created successfully!" << endl;
    cout << "  ID: " << id << " | Name: " << name << " | Distance: " << distance << " km" << endl;
}

void TransportManager::adminAssignVehicle()
{
    cout << "\n=== Assign Vehicle to Route ===" << endl;

    // Select unassigned vehicle
    vector<string> unassignedVehicles;
    vector<Vehicle *> availableVehicles;
    for (Vehicle *v : vehicles.getAll())
    {
        if (v->getAssignedRouteId().empty())
        {
            unassignedVehicles.push_back(v->getId() + " (" + v->getType() + " - " + v->getModel() + ")");
            availableVehicles.push_back(v);
        }
    }

    if (availableVehicles.empty())
    {
        cout << "No unassigned vehicles available." << endl;
        return;
    }

    int vehicleIndex = InputHelper::selectFromMenu(unassignedVehicles, "Select Vehicle to Assign:");
    Vehicle *vehicle = availableVehicles[vehicleIndex];

    // Select route without assigned vehicle
    vector<string> unassignedRoutes;
    vector<Route *> availableRoutes;
    for (Route *r : routes.getAll())
    {
        if (r->getAssignedVehicleId().empty())
        {
            unassignedRoutes.push_back(r->getId() + " - " + r->getName() + " (" + to_string((int)r->getDistance()) + " km)");
            availableRoutes.push_back(r);
        }
    }

    if (availableRoutes.empty())
    {
        cout << "No routes available for assignment." << endl;
        return;
    }

    int routeIndex = InputHelper::selectFromMenu(unassignedRoutes, "Select Route to Assign To:");
    Route *route = availableRoutes[routeIndex];

    vehicle->setAssignedRouteId(route->getId());
    route->setAssignedVehicleId(vehicle->getId());
    cout << "✓ Vehicle assigned to route successfully!" << endl;
    cout << "  Vehicle: " << vehicle->getId() << " → Route: " << route->getId() << " (" << route->getName() << ")" << endl;
}

void TransportManager::adminViewApplications()
{
    displayApplications();
}

void TransportManager::adminApproveRequest()
{
    cout << "\n=== Approve Transport Request ===" << endl;
    displayApplications();

    vector<string> pendingApplications;
    vector<TransportPass *> pendingPasses;
    for (TransportPass *pass : registrations)
    {
        if (pass->getStatus() == "Pending")
        {
            Student *student = findStudentById(pass->getStudentId());
            Route *route = findRouteById(pass->getRouteId());
            string display = pass->getPassId() + " - Student: " + pass->getStudentId();
            if (student)
                display += " (" + student->getName() + ")";
            display += " | Route: " + (route ? route->getName() : "Unknown");
            pendingApplications.push_back(display);
            pendingPasses.push_back(pass);
        }
    }

    if (pendingPasses.empty())
    {
        cout << "No pending applications." << endl;
        return;
    }

    int index = InputHelper::selectFromMenu(pendingApplications, "Select Application to Approve:");
    TransportPass *pass = pendingPasses[index];

    Route *route = findRouteById(pass->getRouteId());
    if (route == nullptr || route->getAssignedVehicleId().empty())
    {
        cout << "Error: Route is not valid or does not have an assigned vehicle." << endl;
        return;
    }

    Vehicle *vehicle = findVehicleById(route->getAssignedVehicleId());
    if (vehicle == nullptr)
    {
        cout << "Error: Assigned vehicle not found." << endl;
        return;
    }

    int approvedCount = countApprovedBookings(route->getId());
    if (approvedCount >= vehicle->getCapacity())
    {
        cout << "Error: Cannot approve. The assigned vehicle is full." << endl;
        return;
    }

    pass->approve();
    updateRouteUsage(route->getId());

    Bill *newBill = new Bill(generateBillId(), pass->getStudentId(), pass->getRouteId(), "2026-06-01", "2026-06-10", "Unpaid", 0.0, 0.0, 0.0);
    newBill->calculateFee(route->getDistance());
    newBill->applyLateFine(0);
    pass->assignBill(*newBill);
    bills.push_back(newBill);

    cout << "✓ Request approved successfully!" << endl;
    cout << "  Pass: " << pass->getPassId() << " | Status: Approved | Bill Generated: " << newBill->getBillId() << endl;
}

void TransportManager::adminRejectRequest()
{
    cout << "\n=== Reject Transport Request ===" << endl;
    displayApplications();

    vector<string> pendingApplications;
    vector<TransportPass *> pendingPasses;
    for (TransportPass *pass : registrations)
    {
        if (pass->getStatus() == "Pending")
        {
            Student *student = findStudentById(pass->getStudentId());
            Route *route = findRouteById(pass->getRouteId());
            string display = pass->getPassId() + " - Student: " + pass->getStudentId();
            if (student)
                display += " (" + student->getName() + ")";
            display += " | Route: " + (route ? route->getName() : "Unknown");
            pendingApplications.push_back(display);
            pendingPasses.push_back(pass);
        }
    }

    if (pendingPasses.empty())
    {
        cout << "No pending applications." << endl;
        return;
    }

    int index = InputHelper::selectFromMenu(pendingApplications, "Select Application to Reject:");
    TransportPass *pass = pendingPasses[index];

    pass->reject();
    cout << "✓ Request rejected successfully!" << endl;
    cout << "  Pass: " << pass->getPassId() << " | Status: Rejected" << endl;
}

void TransportManager::adminGenerateReports()
{
    displayReports();
}

void TransportManager::adminSaveData()
{
    saveAllData();
    cout << "All data saved successfully." << endl;
}

void TransportManager::studentViewRoutes(Student *student) const
{
    displayRoutes();
}

void TransportManager::studentApplyForTransport(Student *student)
{
    if (student->hasTransportPass())
    {
        cout << "Error: You already have an application or registration." << endl;
        return;
    }

    cout << "\n=== Apply for Transport ===" << endl;
    displayRoutes();

    // Build list of available routes
    vector<string> availableRoutes;
    vector<Route *> selectableRoutes;
    for (Route *r : routes.getAll())
    {
        if (r->getAssignedVehicleId().empty())
            continue;

        Vehicle *vehicle = findVehicleById(r->getAssignedVehicleId());
        if (vehicle == nullptr)
            continue;

        int approvedCount = countApprovedBookings(r->getId());
        if (approvedCount >= vehicle->getCapacity())
            continue;

        availableRoutes.push_back(r->getId() + " - " + r->getName() + " (" + to_string((int)r->getDistance()) + " km) [" + 
                                 to_string(approvedCount) + "/" + to_string(vehicle->getCapacity()) + " booked]");
        selectableRoutes.push_back(r);
    }

    if (selectableRoutes.empty())
    {
        cout << "No available routes with capacity." << endl;
        return;
    }

    int index = InputHelper::selectFromMenu(availableRoutes, "Select Route to Apply For:");
    Route *route = selectableRoutes[index];

    TransportPass *pass = new TransportPass(generatePassId(), student->getId(), route->getId(), "Pending");
    registrations.push_back(pass);
    student->setTransportPass(pass);
    cout << "✓ Application submitted successfully!" << endl;
    cout << "  Pass ID: " << pass->getPassId() << " | Route: " << route->getId() << " | Status: Pending" << endl;
}

void TransportManager::studentViewRegistration(Student *student) const
{
    if (!student->hasTransportPass())
    {
        cout << "You have not applied for transport yet." << endl;
        return;
    }
    TransportPass *pass = student->getTransportPass();
    cout << "Registration Status: " << pass->getStatus() << endl;
    cout << "Pass ID: " << pass->getPassId() << " | Route ID: " << pass->getRouteId() << endl;
    if (pass->hasBill())
    {
        Bill bill = pass->getBill();
        cout << bill;
    }
}

void TransportManager::studentCancelRegistration(Student *student)
{
    if (!student->hasTransportPass())
    {
        cout << "You do not have a registration to cancel." << endl;
        return;
    }
    TransportPass *pass = student->getTransportPass();
    if (pass->getStatus() == "Approved" || pass->getStatus() == "Pending")
    {
        pass->cancel();
        student->clearTransportPass();
        cout << "Your registration has been cancelled." << endl;
    }
    else
    {
        cout << "This registration cannot be cancelled." << endl;
    }
}

void TransportManager::runMainMenu()
{
    bool finished = false;
    while (!finished)
    {
        cout << "\n=== University Transport Management System ===" << endl;
        cout << "1. Register User" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Select an option: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            cout << "\n=== Student Registration ===" << endl;
            string id = InputHelper::getStudentId("Enter Student ID (format: S#### e.g., S1001): ");
            if (findUserById(id) != nullptr)
            {
                cout << "Error: User ID '" << id << "' already exists." << endl;
                break;
            }
            string name = InputHelper::getName("Enter Full Name: ");
            string email = InputHelper::getEmail("Enter Email Address: ");
            string password = InputHelper::getPassword("Enter Password (minimum 6 alphanumeric characters): ");
            int year = InputHelper::selectYear();

            Student *student = new Student(id, name, email, password, year);
            users.push_back(student);
            cout << "✓ Student registered successfully!" << endl;
            cout << "  ID: " << id << " | Name: " << name << " | Year: " << year << endl;
            break;
        }
        case 2:
        {
            cout << "\n=== User Login ===" << endl;
            string id, password;
            cout << "Enter User ID (or 'admin' for admin): ";
            getline(cin, id);
            cout << "Enter Password: ";
            getline(cin, password);

            User *user = findUserById(id);
            if (user == nullptr || !user->authenticate(password))
            {
                cout << "✗ Error: Invalid ID or password." << endl;
                break;
            }

            cout << "✓ Login successful! Welcome " << user->getName() << "." << endl;

            if (dynamic_cast<Student *>(user))
            {
                bool loggedOut = false;
                while (!loggedOut)
                {
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
                    Student *student = dynamic_cast<Student *>(user);
                    switch (studentChoice)
                    {
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
            }
            else if (dynamic_cast<Admin *>(user))
            {
                bool loggedOut = false;
                while (!loggedOut)
                {
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
                    switch (adminChoice)
                    {
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
