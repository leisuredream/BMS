#ifndef USER_H
#define USER_H

#include "./MyVector.h"
#include <string>

enum Role { ADMIN, USER };

struct User {
    std::string username;
    std::string password;
    Role role;

    User() : username(""), password(""), role(USER) {}

    User(const std::string &username, const std::string &password, Role role)
        : username(username), password(password), role(role) {}

    static std::string getUsername(const User& user){
        return user.username;
    }
};

class UserManager
{
private:
    MyVector<User> users;
public:
    void addUser(const User &user);
    bool removeUser(const std::string &username);
    bool updateUser(const std::string &oldUsername, const User &newUser);
    void printAllUsers() const;
};

#endif // USER_H