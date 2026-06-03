#ifndef VAN_H
#define VAN_H

#include "Vehicle.h"
using namespace std;

class Van : public Vehicle
{
private:
    bool hasLuggageSpace;

public:
    Van();
    Van(const string &id,
        const string &model,
        int capacity,
        bool hasLuggageSpace);
    Van(const Van &other);
    Van &operator=(const Van &other);
    virtual ~Van();

    bool getHasLuggageSpace() const;
    void setHasLuggageSpace(bool value);

    virtual string getType() const override;
    virtual void display() const override;
    virtual Vehicle *clone() const override;
};

#endif // VAN_H

