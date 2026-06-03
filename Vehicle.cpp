#include "Vehicle.h"
using namespace std;

Vehicle::Vehicle() : id(""), model(""), capacity(0), assignedRouteId("") {}

Vehicle::Vehicle(const string& id,
                 const string& model,
                 int capacity)
    : id(id), model(model), capacity(capacity), assignedRouteId("") {}

Vehicle::Vehicle(const Vehicle& other)
    : id(other.id), model(other.model), capacity(other.capacity), assignedRouteId(other.assignedRouteId) {}

Vehicle& Vehicle::operator=(const Vehicle& other) {
    if (this != &other) {
        id = other.id;
        model = other.model;
        capacity = other.capacity;
        assignedRouteId = other.assignedRouteId;
    }
    return *this;
}

Vehicle::~Vehicle() {}

string Vehicle::getId() const {
    return id;
}

string Vehicle::getModel() const {
    return model;
}

int Vehicle::getCapacity() const {
    return capacity;
}

string Vehicle::getAssignedRouteId() const {
    return assignedRouteId;
}

void Vehicle::setModel(const string& value) {
    model = value;
}

void Vehicle::setCapacity(int value) {
    capacity = value;
}

void Vehicle::setAssignedRouteId(const string& routeId) {
    assignedRouteId = routeId;
}

void Vehicle::clearAssignedRoute() {
    assignedRouteId.clear();
}
