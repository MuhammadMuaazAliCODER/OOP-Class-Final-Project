#ifndef BUS_H
#define BUS_H

#include "Vehicle.h"
using namespace std;

class Bus : public Vehicle {
private:
    bool hasAC;

public:
    Bus();
    Bus(const string& id,
        const string& model,
        int capacity,
        bool hasAC);
    Bus(const Bus& other);
    Bus& operator=(const Bus& other);
    virtual ~Bus();

    bool getHasAC() const;
    void setHasAC(bool value);

    virtual string getType() const override;
    virtual void display() const override;
    virtual Vehicle* clone() const override;
};

#endif // BUS_H
