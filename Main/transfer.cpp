#include "transfer.h"
#include "user_system.h"
#include <fstream>
#include <iomanip>


bool transferMoney  (const std::string& fromUser,
                     const std::string& toUser,
                     std::string password,
                     double amount)
{
    loadUsers();

    User* sender = nullptr;
    User* receiver = nullptr;

    for (auto &u : user_info)
    {
        if(u.password != password)
            return false;

        if (u.username == fromUser)
            sender = &u;

        if (u.username == toUser)
            receiver = &u;
    }

    if (!sender || !receiver)
        return false;

    if (amount <= 0)
        return false;

    if (amount > sender->balance)
        return false;

    sender->balance -= amount;
    receiver->balance += amount;

    std::string time = getCurrentTime();

    saveToFile();

    std::ofstream filed("database.csv", std::ios::app);

    filed << sender->username << ","
          << "0.00,"
          << std::fixed << std::setprecision(2) << amount << ","
          << time << ","
          <<  receiver->username << "\n";

    filed << receiver->username << ","
          << std::fixed << std::setprecision(2) << amount << ","
          << "0.00,"
          << time << ","
          << "TRANSFER_IN\n";

    filed.close();
    return true;
}