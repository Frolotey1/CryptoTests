#ifndef AUTHORIZATION_H_
#define AUTHORIZATION_H_

#include "Header.h"

struct User {
    std::string login;
    std::string password;
    std::string status;

    bool operator==(const User& other) {
        return this->login == other.login
               && this->password == other.password && this->status == other.status;
    }
};

extern std::vector<User> users;
extern std::string currentUserStatus;
bool Login();
bool RegisterUser();
bool DeleteAccount();
bool captcha();
bool Change_info();

#endif
