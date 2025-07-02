#include "../head/User.h"
#include "../head/PermissionManager.h"
#include <windows.h>
#include <iostream>

int main(){
    SetConsoleOutputCP(CP_UTF8);

    UserManager userManager = UserManager();
    PermissionManager permissionManager = PermissionManager(&userManager);

    userManager.addUser({
        "leisure",
        "123456",
        USER
    });
    userManager.printAllUsers();

    userManager.addUser({
        "leisure123",
        "123456",
        ADMIN
    });

    userManager.printAllUsers();

    if (permissionManager.login("leisure123","123456"))
    {
        std::cout << "login successful" << std::endl;

        try{
            permissionManager.requirePermission(ADMIN, [&]() {
                MyVector<std::string> usersToRemove;
                usersToRemove.push_back("leisure123");
                userManager.adminRemoveUsers(usersToRemove);
            });
        }catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        } 
    }else {
        std::cerr << "login failed" << std::endl;
    }
    
    userManager.printAllUsers();

    return 0;

}