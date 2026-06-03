#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include <string>
using namespace std;

class TransportPass;

class Student : public User {
private:
    int year;
    TransportPass* transportPass;

public:
    Student();
    Student(const string& id,
            const string& name,
            const string& email,
            const string& password,
            int year);
    Student(const Student& other);
    Student& operator=(const Student& other);
    virtual ~Student();

    int getYear() const;
    void setYear(int year);

    TransportPass* getTransportPass() const;
    void setTransportPass(TransportPass* pass);
    void clearTransportPass();
    bool hasTransportPass() const;

    virtual string getRole() const override;
    virtual void display() const override;
};

#endif // STUDENT_H
