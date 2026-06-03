#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User
{
protected:
    string id;
    string name;
    string email;
    string password;

public:
    User();
    User(const string &id, const string &name, const string &email, const string &password);
    User(const User &other);
    User &operator=(const User &other);
    virtual ~User();

    string getId() const;
    string getName() const;
    string getEmail() const;
    string getPassword() const;
    void setName(const string &name);
    void setEmail(const string &email);
    void setPassword(const string &password);
    bool authenticate(const string &password) const;

    virtual string getRole() const = 0;
    virtual void display() const = 0;
};

#endif // USER_H

