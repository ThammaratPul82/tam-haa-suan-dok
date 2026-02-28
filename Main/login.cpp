#include "login.h"
#include "user_system.h"
#include <windows.h>

// std::vector<User> user_info;


bool checkLogin(const std::string& username,
                const std::string& password)
{
    loadUsers();

    for (auto &u : user_info)
    {
        if (u.username == username)
        {
            if (u.attempt >= 3)
            {
                MessageBox(NULL, "Account locked!", 
                           "Error", MB_OK);
                return false;
            }

            if (u.password == password)
            {
                u.attempt = 0;   // รีเซ็ต
                saveToFile();
                return true;
            }
            else
            {
                u.attempt++;
                saveToFile();

                int left = 3 - u.attempt;

                if (left > 0)
                {
                    std::string msg = 
                        "Wrong password! Attempts left: "
                        + std::to_string(left);

                    MessageBox(NULL, msg.c_str(),
                               "Error", MB_OK);
                }
                else
                {
                    MessageBox(NULL, 
                        "Account locked (3 attempts)!", 
                        "Error", MB_OK);
                }

                return false;
            }
        }
    }

    MessageBox(NULL, "Username not found!", 
               "Error", MB_OK);

    return false;
}