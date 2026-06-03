#include "Admin.h"
#include <iostream>
using namespace std;

Admin::Admin() : User() {}

Admin::Admin(const string& id,
             const string& name,
             const string& email,
             const string& password)
    : User(id, name, email, password) {}

Admin::Admin(const Admin& other) : User(other) {}

Admin& Admin::operator=(const Admin& other) {
    if (this != &other) {
        User::operator=(other);
    }
    return *this;
}

Admin::~Admin() {}

string Admin::getRole() const {
    return "Admin";
}

void Admin::display() const {
    cout << "Admin ID: " << id << " | Name: " << name << '\n';
}
