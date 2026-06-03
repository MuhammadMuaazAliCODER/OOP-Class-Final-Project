#include "Bus.h"
#include <iostream>
using namespace std;

Bus::Bus() : Vehicle(), hasAC(false) {}

Bus::Bus(const string& id,
         const string& model,
         int capacity,
         bool hasAC)
    : Vehicle(id, model, capacity), hasAC(hasAC) {}

Bus::Bus(const Bus& other)
    : Vehicle(other), hasAC(other.hasAC) {}

Bus& Bus::operator=(const Bus& other) {
    if (this != &other) {
        Vehicle::operator=(other);
        hasAC = other.hasAC;
    }
    return *this;
}

Bus::~Bus() {}

bool Bus::getHasAC() const {
    return hasAC;
}

void Bus::setHasAC(bool value) {
    hasAC = value;
}

string Bus::getType() const {
    return "Bus";
}

void Bus::display() const {
    cout << "[Bus] ID: " << id
              << " | Model: " << model
              << " | Capacity: " << capacity
              << " | AC: " << (hasAC ? "Yes" : "No")
              << " | Route: " << (assignedRouteId.empty() ? "None" : assignedRouteId)
              << endl;
}

Vehicle* Bus::clone() const {
    return new Bus(*this);
}
