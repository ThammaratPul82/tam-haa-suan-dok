#ifndef TRANSFER_H
#define TRANSFER_H

#include <string>

bool transferMoney(const std::string& fromUser,
                     const std::string& toUser,
                     std::string password,
                     double amount);

#endif