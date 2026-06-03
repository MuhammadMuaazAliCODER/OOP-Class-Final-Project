#ifndef BILL_H
#define BILL_H

#include <string>
#include <iostream>
using namespace std;

class Bill {
private:
    string billId;
    string studentId;
    string routeId;
    string issueDate;
    string dueDate;
    string status;
    double amount;
    double lateFine;
    double totalAmount;

public:
    Bill();
    Bill(const string& billId,
         const string& studentId,
         const string& routeId,
         const string& issueDate,
         const string& dueDate,
         const string& status,
         double amount,
         double lateFine,
         double totalAmount);
    Bill(const Bill& other);
    Bill& operator=(const Bill& other);
    ~Bill();

    string getBillId() const;
    string getStudentId() const;
    string getRouteId() const;
    string getIssueDate() const;
    string getDueDate() const;
    string getStatus() const;
    double getAmount() const;
    double getLateFine() const;
    double getTotalAmount() const;

    void setStatus(const string& status);
    void calculateFee(double distance);
    void applyLateFine(int daysLate);

    friend ostream& operator<<(ostream& out, const Bill& bill);
};

#endif // BILL_H
