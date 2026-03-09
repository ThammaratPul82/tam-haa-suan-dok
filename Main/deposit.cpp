#include "include/user_system.h"
#include "include/deposit.h"
#include <fstream>
#include <iomanip>
#include "include/runCreate_img.h"
#include <string>

int depositMoney(std::string username, std::string password, double amount)
{
    loadUsers();

    for (auto &u : user_info)
    {
        if (u.username == username)
        {
            if (u.password != password)
                return 2;

            if (amount <= 0)
                return 3;

            u.balance += amount;

            saveToFile();

            // บันทึก transaction
            std::ofstream filed("database.csv", std::ios::app);

            std::string time = getCurrentTime();

            filed << username << ","
                  << std::fixed << std::setprecision(2) << amount << ","
                  << "0.00,"
                  << time << ","
                  << "1\n";

            filed.close();
            createIMG(u.username, "1", std::to_string(amount), std::to_string(u.balance));
            return 1;
        }
    }

    return 0;
}