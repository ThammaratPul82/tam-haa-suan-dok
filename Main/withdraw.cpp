#include "include/withdraw.h"
#include "include/user_system.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip> 
#include "include/runCreate_img.h"

using namespace std;

int withdrawMoney(std::string username,std::string password, double amount, double &newBalance)
{
    loadUsers();

    for (auto &u : user_info)
    {
        if (u.username == username)
        {
            if (u.password != password)
                return 2;

            if (amount > u.balance)
                return 3;

            if (amount <= 0)
                return 4;

            u.balance -= amount;

            saveToFile();

            // บันทึก transaction
            std::ofstream filed("database.csv", std::ios::app);

            std::string time = getCurrentTime();

            filed << username << ","
                  << std::fixed << "0.00" << ","
                  << std::setprecision(2) << amount <<","
                  << time << ","
                  << "1\n";

            filed.close();

            createIMG(u.username, "0", std::to_string(amount), std::to_string(u.balance));
            return 1;
        }
    }

    return 0;
}




