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

    userManager.printAllUsers();

    return 0;

}