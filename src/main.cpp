#include "../head/User.h"
#include <windows.h>
#include <iostream>

int main(){
    SetConsoleOutputCP(CP_UTF8);

    UserManager userManager = UserManager();

    userManager.addUser({
        "leisure",
        "123546",
        ADMIN
    });

    userManager.addUser({
        "leisure",
        "123546",
        ADMIN
    });

    userManager.updateUser("leisure", {
        "leisure123",
        "654321",
        USER
    });

    const User* user = userManager.findUser("leisure");
    if (user) {
        user->print();
    } else {
        std::cout << "未找到用户" << std::endl;
    }

    user = userManager.findUser("leisure123");
    if (user) {
        user->print();
    } else {
        std::cout << "未找到用户" << std::endl;
    }

    userManager.removeUser("leisure123");

    userManager.printAllUsers();

    return 0;

}