#include "../include/Van.h"
#include <iostream>
using namespace std;

Van::Van() : Vehicle(), hasLuggageSpace(false) {}

Van::Van(const string& id,
         const string& model,
         int capacity,
         bool hasLuggageSpace)
    : Vehicle(id, model, capacity), hasLuggageSpace(hasLuggageSpace) {}

Van::Van(const Van& other)
    : Vehicle(other), hasLuggageSpace(other.hasLuggageSpace) {}

Van& Van::operator=(const Van& other) {
    if (this != &other) {
        Vehicle::operator=(other);
        hasLuggageSpace = other.hasLuggageSpace;
    }
    return *this;
}

Van::~Van() {}

bool Van::getHasLuggageSpace() const {
    return hasLuggageSpace;
}

void Van::setHasLuggageSpace(bool value) {
    hasLuggageSpace = value;
}

string Van::getType() const {
    return "Van";
}

void Van::display() const {
    cout << "[Van] ID: " << id
              << " | Model: " << model
              << " | Capacity: " << capacity
              << " | Luggage Space: " << (hasLuggageSpace ? "Yes" : "No")
              << " | Route: " << (assignedRouteId.empty() ? "None" : assignedRouteId)
              << endl;
}

Vehicle* Van::clone() const {
    return new Van(*this);
}
