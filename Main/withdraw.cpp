#include "withdraw.h"
#include "user_system.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip> 


using namespace std;

bool withdrawMoney(std::string username,std::string password, double amount, double &newBalance)
{
    loadUsers();

    for (auto &u : user_info)
    {
        if (u.username == username)
        {
            if (u.password != password)
                return false;
            if (amount > u.balance)
                return false;

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

            return true;
        }
    }

    return false;
}




