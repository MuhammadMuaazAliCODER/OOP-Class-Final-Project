#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <string>
using namespace std;

class Admin : public User
{
public:
    Admin();
    Admin(const string &id,
          const string &name,
          const string &email,
          const string &password);
    Admin(const Admin &other);
    Admin &operator=(const Admin &other);
    virtual ~Admin();

    virtual string getRole() const override;
    virtual void display() const override;
};

#endif // ADMIN_H

