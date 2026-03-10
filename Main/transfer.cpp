#include "include/transfer.h"
#include "include/user_system.h"
#include <fstream>
#include <iomanip>
#include "include/runCreate_img.h"

int transferMoney(const std::string &fromUser,
                   const std::string &toUser,
                   std::string password,
                   long double amount)
{
    loadUsers();

    User *sender = nullptr;
    User *receiver = nullptr;

    for (auto &u : user_info)
    {
        if (u.username == fromUser)
            sender = &u;
        if (u.username == toUser)
            receiver = &u;
    }

    if (!sender || sender->password != password)
    {
        return 2;
    }

    if (!receiver)
    {
        return 3;
    }

    if (amount <= 0)
    {
        return 4;
    }

    if (amount > sender->balance)
    {
        return 5;
    }

    sender->balance -= amount;
    receiver->balance += amount;

    std::string time = getCurrentTime();

    saveToFile();

    std::ofstream filed("database.csv", std::ios::app);

    filed << sender->username << ","
          << "0.00,"
          << std::fixed << std::setprecision(2) << amount << ","
          << time << ","
          << receiver->username << "\n";

    filed << receiver->username << ","
          << std::fixed << std::setprecision(2) << amount << ","
          << "0.00,"
          << time << ","
          << "TRANSFER_IN\n";

    filed.close();
    createSlip(sender->username, sender->name_surname, receiver->username, receiver->name_surname, std::to_string(amount));
    return 1;
}