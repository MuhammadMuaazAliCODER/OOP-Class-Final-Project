#include "User.h"
using namespace std;

User::User() : id(""), name(""), email(""), password("") {}

User::User(const string& id, const string& name, const string& email, const string& password)
    : id(id), name(name), email(email), password(password) {}

User::User(const User& other)
    : id(other.id), name(other.name), email(other.email), password(other.password) {}

User& User::operator=(const User& other) {
    if (this != &other) {
        id = other.id;
        name = other.name;
        email = other.email;
        password = other.password;
    }
    return *this;
}

User::~User() {}

string User::getId() const {
    return id;
}

string User::getName() const {
    return name;
}

string User::getEmail() const {
    return email;
}

string User::getPassword() const {
    return password;
}

void User::setName(const string& value) {
    name = value;
}

void User::setEmail(const string& value) {
    email = value;
}

void User::setPassword(const string& value) {
    password = value;
}

bool User::authenticate(const string& attempt) const {
    return password == attempt;
}
