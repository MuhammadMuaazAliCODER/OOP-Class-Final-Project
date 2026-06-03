#ifndef TRANSPORTMANAGER_H
#define TRANSPORTMANAGER_H

#include <string>
#include <vector>
#include "TemplateStorage.h"
#include "User.h"
#include "Student.h"
#include "Admin.h"
#include "Vehicle.h"
#include "Bus.h"
#include "Van.h"
#include "Route.h"
#include "TransportPass.h"
#include "Bill.h"
using namespace std;

class TransportManager {
private:
    vector<User*> users;
    Storage<Vehicle*> vehicles;
    Storage<Route*> routes;
    vector<TransportPass*> registrations;
    vector<Bill*> bills;

    const string usersFile;
    const string vehiclesFile;
    const string routesFile;
    const string registrationsFile;
    const string billsFile;

    void loadUsers();
    void loadVehicles();
    void loadRoutes();
    void loadRegistrations();
    void loadBills();
    void attachTransportPasses();
    void createDefaultAdmin();

    void saveUsers();
    void saveVehicles();
    void saveRoutes();
    void saveRegistrations();
    void saveBills();

    User* findUserById(const string& id) const;
    Student* findStudentById(const string& id) const;
    Admin* findAdminById(const string& id) const;
    Vehicle* findVehicleById(const string& id) const;
    Route* findRouteById(const string& id) const;
    TransportPass* findRegistrationByPassId(const string& passId) const;
    TransportPass* findRegistrationByStudentId(const string& studentId) const;
    int countApprovedBookings(const string& routeId) const;
    void updateRouteUsage(const string& routeId);
    vector<string> splitLine(const string& line, char delimiter) const;
    string generatePassId() const;
    string generateBillId() const;

    void displayRoutes() const;
    void displayVehicles() const;
    void displayApplications() const;
    void displayReports() const;

    void adminAddVehicle();
    void adminEditVehicle();
    void adminRemoveVehicle();
    void adminAddRoute();
    void adminAssignVehicle();
    void adminViewApplications();
    void adminApproveRequest();
    void adminRejectRequest();
    void adminGenerateReports();
    void adminSaveData();

    void studentViewRoutes(Student* student) const;
    void studentApplyForTransport(Student* student);
    void studentViewRegistration(Student* student) const;
    void studentCancelRegistration(Student* student);

public:
    TransportManager();
    ~TransportManager();

    void loadAllData();
    void saveAllData();
    void runMainMenu();
};

#endif // TRANSPORTMANAGER_H
