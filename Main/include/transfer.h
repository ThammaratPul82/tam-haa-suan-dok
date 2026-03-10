#ifndef TRANSFER_H
#define TRANSFER_H

#include <string>

int transferMoney(const std::string& fromUser,
                     const std::string& toUser,
                     std::string password,
                     long double amount);

#endif