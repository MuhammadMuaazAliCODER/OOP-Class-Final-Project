#include "../include/TransportPass.h"
using namespace std;

TransportPass::TransportPass()
    : passId(""), studentId(""), routeId(""), status("Pending"), bill(), billAssigned(false) {}

TransportPass::TransportPass(const string& passId,
                             const string& studentId,
                             const string& routeId,
                             const string& status)
    : passId(passId), studentId(studentId), routeId(routeId), status(status), bill(), billAssigned(false) {}

TransportPass::TransportPass(const TransportPass& other)
    : passId(other.passId), studentId(other.studentId), routeId(other.routeId), status(other.status), bill(other.bill), billAssigned(other.billAssigned) {}

TransportPass& TransportPass::operator=(const TransportPass& other) {
    if (this != &other) {
        passId = other.passId;
        studentId = other.studentId;
        routeId = other.routeId;
        status = other.status;
        bill = other.bill;
        billAssigned = other.billAssigned;
    }
    return *this;
}

TransportPass::~TransportPass() {}

string TransportPass::getPassId() const {
    return passId;
}

string TransportPass::getStudentId() const {
    return studentId;
}

string TransportPass::getRouteId() const {
    return routeId;
}

string TransportPass::getStatus() const {
    return status;
}

void TransportPass::setStatus(const string& value) {
    status = value;
}

void TransportPass::assignBill(const Bill& newBill) {
    bill = newBill;
    billAssigned = true;
}

bool TransportPass::hasBill() const {
    return billAssigned;
}

Bill TransportPass::getBill() const {
    return bill;
}

void TransportPass::approve() {
    status = "Approved";
}

void TransportPass::reject() {
    status = "Rejected";
}

void TransportPass::cancel() {
    status = "Cancelled";
}
