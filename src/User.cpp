#include "../head/User.h"
#include <iostream>

void UserManager::addUser(const User &user){
    auto getUsername = [](const User& user) -> std::string { return user.username; };
    auto comparator = [](const std::string& a, const std::string& b) -> bool { return a < b; };
    // 使用二分查找检查用户是否已存在
    int index = users.binarySearch<std::string>(std::string("leisure"), getUsername, comparator);
    if (index >= 0) {
        std::cout << "用户已存在，无法添加。" << std::endl;
        return;
    }

    users.add(user);
}

bool UserManager::removeUser(const std::string &username){
    const User* userPtr = findUser(username);
    if (userPtr) {
        // 找到用户，获取其索引并删除
        int index = static_cast<int>(userPtr - &users[0]);
        users.removeAt(index);
        return true;
    }
    return false;
}

bool UserManager::updateUser(const std::string &oldUsername, const User &newUser) {
    const User* userPtr = findUser(oldUsername);
    if (userPtr) {
        int idx = static_cast<int>(userPtr - &users[0]);
        users[idx] = newUser; // 更新用户信息
        // 重新计算哈希表
        users.rebuildHashTable();
        return true;
    }
    return false;
}

void UserManager::printAllUsers() const {
    for (size_t i = 0; i < users.getSize(); ++i) {
        const User& user = users[i];
        std::cout << "用户名: " << user.username
                  << ", 角色: " << (user.role == ADMIN ? "管理员" : "普通用户") << std::endl;
    }
}

const User* UserManager::findUser(const std::string &username) const {
    int idx = users.hashFindByUsername(username);
    if (idx >= 0) {
        return &users[idx];
    }
    return nullptr;
}