#ifndef USER_H
#define USER_H

#include <string>

enum Role { ADMIN, USER };

struct User {
    std::string username;
    std::string password;
    Role role;

    User(const std::string &username, const std::string &password, Role role)
        : username(username), password(password), role(role) {}
};

#endif // USER_H