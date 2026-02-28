#ifndef SIGNIN_H
#define SIGNIN_H

#include <string>
#include <vector>

// struct Users {
//     std::string username;
//     std::string name_surname;
//     std::string password;
//     int attempt;
//     std::string date_time;
// };

bool registerUser(const std::string& username,
                  const std::string& password,
                  const std::string& name);

// void loadUsers();
// void saveToFile();

#endif