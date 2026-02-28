#ifndef USER_SYSTEM_H
#define USER_SYSTEM_H

#include <vector>
#include <string>

struct User {
    std::string username;
    std::string name_surname;
    std::string password;
    int attempt;
    std::string date_time;
};

extern std::vector<User> user_info;

void loadUsers();
void saveToFile();
std::string getCurrentDate();

#endif