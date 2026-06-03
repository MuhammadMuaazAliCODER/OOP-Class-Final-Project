#include "../include/Route.h"
using namespace std;

Route::Route() : id(""), name(""), distance(0.0), assignedVehicleId(""), usageCount(0) {}

Route::Route(const string& id,
             const string& name,
             double distance)
    : id(id), name(name), distance(distance), assignedVehicleId(""), usageCount(0) {}

Route::Route(const Route& other)
    : id(other.id), name(other.name), distance(other.distance), assignedVehicleId(other.assignedVehicleId), usageCount(other.usageCount) {}

Route& Route::operator=(const Route& other) {
    if (this != &other) {
        id = other.id;
        name = other.name;
        distance = other.distance;
        assignedVehicleId = other.assignedVehicleId;
        usageCount = other.usageCount;
    }
    return *this;
}

Route::~Route() {}

string Route::getId() const {
    return id;
}

string Route::getName() const {
    return name;
}

double Route::getDistance() const {
    return distance;
}

string Route::getAssignedVehicleId() const {
    return assignedVehicleId;
}

int Route::getUsageCount() const {
    return usageCount;
}

void Route::setName(const string& value) {
    name = value;
}

void Route::setDistance(double value) {
    distance = value;
}

void Route::setAssignedVehicleId(const string& vehicleId) {
    assignedVehicleId = vehicleId;
}

void Route::clearAssignedVehicle() {
    assignedVehicleId.clear();
}

void Route::incrementUsage() {
    usageCount++;
}
