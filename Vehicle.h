#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
using namespace std;

class Vehicle {
protected:
    string id;
    string model;
    int capacity;
    string assignedRouteId;

public:
    Vehicle();
    Vehicle(const string& id,
            const string& model,
            int capacity);
    Vehicle(const Vehicle& other);
    Vehicle& operator=(const Vehicle& other);
    virtual ~Vehicle();

    string getId() const;
    string getModel() const;
    int getCapacity() const;
    string getAssignedRouteId() const;

    void setModel(const string& model);
    void setCapacity(int capacity);
    void setAssignedRouteId(const string& routeId);
    void clearAssignedRoute();

    virtual string getType() const = 0;
    virtual void display() const = 0;
    virtual Vehicle* clone() const = 0;
};

#endif // VEHICLE_H
