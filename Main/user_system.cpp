#include "user_system.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<User> user_info;

void loadUsers() {

    user_info.clear();   // 🔥 เพิ่มบรรทัดนี้

    std::ifstream file("users.csv");
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string value;
        std::vector<std::string> data;

        while (std::getline(ss, value, ',')) {
            data.push_back(value);
        }

        if (data.size() >= 6) {
            User u;
            u.username = data[0];
            u.name_surname = data[1];
            u.password = data[2];
            u.attempt = std::stoi(data[3]);
            u.date_time = data[4];
            u.balance = std::stod(data[5]);
            user_info.push_back(u);
        }
    }
}

void saveToFile() {
    std::ofstream out("users.csv");
    for (auto &u : user_info) {
        out << u.username << ","
            << u.name_surname << ","
            << u.password << ","
            << u.attempt << ","
            << u.date_time << ","
            << u.balance << "\n";
    }
}

std::string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", ltm);
    return std::string(buffer);
}

double getBalance(const std::string& username)
{
    for (auto &u : user_info)
    {
        if (u.username == username)
        {
            return u.balance;
        }
    }
    return 0.0;
}