#include "../head/User.h"
#include <iostream>

void UserManager::addUser(const User &user){
    users.add(user);
}

void UserManager::printAllUsers() const {
    for (size_t i = 0; i < users.getSize(); ++i) {
        const User& user = users[i];
        std::cout << "用户名: " << user.username
                  << ", 角色: " << (user.role == ADMIN ? "管理员" : "普通用户") << std::endl;
    }
}