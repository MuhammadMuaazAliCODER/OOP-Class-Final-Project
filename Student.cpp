#include "Student.h"
#include "TransportPass.h"
#include <iostream>
using namespace std;

Student::Student()
    : User(), year(0), transportPass(nullptr) {}

Student::Student(const string& id,
                 const string& name,
                 const string& email,
                 const string& password,
                 int year)
    : User(id, name, email, password), year(year), transportPass(nullptr) {}

Student::Student(const Student& other)
    : User(other), year(other.year), transportPass(other.transportPass) {}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        User::operator=(other);
        year = other.year;
        transportPass = other.transportPass;
    }
    return *this;
}

Student::~Student() {}

int Student::getYear() const {
    return year;
}

void Student::setYear(int value) {
    year = value;
}

TransportPass* Student::getTransportPass() const {
    return transportPass;
}

void Student::setTransportPass(TransportPass* pass) {
    transportPass = pass;
}

void Student::clearTransportPass() {
    transportPass = nullptr;
}

bool Student::hasTransportPass() const {
    return transportPass != nullptr;
}

string Student::getRole() const {
    return "Student";
}

void Student::display() const {
    cout << "Student ID: " << id << " | Name: " << name << " | Year: " << year << '\n';
}
