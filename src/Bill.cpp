#include "../include/Bill.h"
using namespace std;

Bill::Bill()
    : billId(""), studentId(""), routeId(""), issueDate(""), dueDate(""), status("Pending"), amount(0.0), lateFine(0.0), totalAmount(0.0) {}

Bill::Bill(const string& billId,
           const string& studentId,
           const string& routeId,
           const string& issueDate,
           const string& dueDate,
           const string& status,
           double amount,
           double lateFine,
           double totalAmount)
    : billId(billId), studentId(studentId), routeId(routeId), issueDate(issueDate), dueDate(dueDate), status(status), amount(amount), lateFine(lateFine), totalAmount(totalAmount) {}

Bill::Bill(const Bill& other)
    : billId(other.billId), studentId(other.studentId), routeId(other.routeId), issueDate(other.issueDate), dueDate(other.dueDate), status(other.status), amount(other.amount), lateFine(other.lateFine), totalAmount(other.totalAmount) {}

Bill& Bill::operator=(const Bill& other) {
    if (this != &other) {
        billId = other.billId;
        studentId = other.studentId;
        routeId = other.routeId;
        issueDate = other.issueDate;
        dueDate = other.dueDate;
        status = other.status;
        amount = other.amount;
        lateFine = other.lateFine;
        totalAmount = other.totalAmount;
    }
    return *this;
}

Bill::~Bill() {}

string Bill::getBillId() const {
    return billId;
}

string Bill::getStudentId() const {
    return studentId;
}

string Bill::getRouteId() const {
    return routeId;
}

string Bill::getIssueDate() const {
    return issueDate;
}

string Bill::getDueDate() const {
    return dueDate;
}

string Bill::getStatus() const {
    return status;
}

double Bill::getAmount() const {
    return amount;
}

double Bill::getLateFine() const {
    return lateFine;
}

double Bill::getTotalAmount() const {
    return totalAmount;
}

void Bill::setStatus(const string& value) {
    status = value;
}

void Bill::calculateFee(double distance) {
    amount = 30.0 + distance * 5.0;
    lateFine = 0.0;
    totalAmount = amount;
    status = "Unpaid";
}

void Bill::applyLateFine(int daysLate) {
    if (daysLate > 0) {
        lateFine = daysLate * 5.0;
    } else {
        lateFine = 0.0;
    }
    totalAmount = amount + lateFine;
}

ostream &operator<<(ostream &out, const Bill &bill) {
    out << "Bill ID: " << bill.billId << '\n';
    out << "Student ID: " << bill.studentId << '\n';
    out << "Route ID: " << bill.routeId << '\n';
    out << "Issue Date: " << bill.issueDate << '\n';
    out << "Due Date: " << bill.dueDate << '\n';
    out << "Status: " << bill.status << '\n';
    out << "Base Amount: " << bill.amount << '\n';
    out << "Late Fine: " << bill.lateFine << '\n';
    out << "Total Amount: " << bill.totalAmount << '\n';
    return out;
}
