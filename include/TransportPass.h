#ifndef TRANSPORTPASS_H
#define TRANSPORTPASS_H

#include <string>
#include "Bill.h"
using namespace std;

class TransportPass
{
private:
    string passId;
    string studentId;
    string routeId;
    string status;
    Bill bill;
    bool billAssigned;

public:
    TransportPass();
    TransportPass(const string &passId,
                  const string &studentId,
                  const string &routeId,
                  const string &status);
    TransportPass(const TransportPass &other);
    TransportPass &operator=(const TransportPass &other);
    ~TransportPass();

    string getPassId() const;
    string getStudentId() const;
    string getRouteId() const;
    string getStatus() const;

    void setStatus(const string &status);
    void assignBill(const Bill &bill);
    bool hasBill() const;
    Bill getBill() const;

    void approve();
    void reject();
    void cancel();
};

#endif // TRANSPORTPASS_H

