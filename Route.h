#ifndef ROUTE_H
#define ROUTE_H

#include <string>
using namespace std;

class Route {
private:
    string id;
    string name;
    double distance;
    string assignedVehicleId;
    int usageCount;

public:
    Route();
    Route(const string& id,
          const string& name,
          double distance);
    Route(const Route& other);
    Route& operator=(const Route& other);
    ~Route();

    string getId() const;
    string getName() const;
    double getDistance() const;
    string getAssignedVehicleId() const;
    int getUsageCount() const;

    void setName(const string& name);
    void setDistance(double distance);
    void setAssignedVehicleId(const string& vehicleId);
    void clearAssignedVehicle();
    void incrementUsage();
};

#endif // ROUTE_H
