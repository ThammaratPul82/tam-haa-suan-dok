#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <vector>

// struct User {
//     std::string username;
//     std::string name_surname;
//     std::string password;
//     int attempt;
// };

bool checkLogin(const std::string& username,
                const std::string& password);

void loadUsers();
void saveToFile();

#endif