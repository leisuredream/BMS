#include "../head/User.h"
#include <iostream>

void UserManager::addUser(const User &user){
    auto getUsername = [](const User& user) -> std::string { return user.username; };
    auto comparator = [](const std::string& a, const std::string& b) -> bool { return a < b; };
    // 使用二分查找检查用户是否已存在
    int index = users.binarySearch<std::string>(std::string("leisure"), getUsername, comparator);
    std::cout << "二分查找结果: " << index << std::endl;
    if (index >= 0) {
        std::cout << "用户已存在，无法添加。" << std::endl;
        return;
    }

    users.add(user);
}

void UserManager::printAllUsers() const {
    for (size_t i = 0; i < users.getSize(); ++i) {
        const User& user = users[i];
        std::cout << "用户名: " << user.username
                  << ", 角色: " << (user.role == ADMIN ? "管理员" : "普通用户") << std::endl;
    }
}