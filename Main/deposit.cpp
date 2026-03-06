#include "user_system.h"
#include "deposit.h"
#include <fstream>
#include <iomanip>

bool depositMoney(std::string username, std::string password, double amount)
{
    loadUsers();

    for (auto &u : user_info)
    {
        if (u.username == username)
        {
            if (u.password != password)
                return false;

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

            return true;
        }
    }

    return false;
}