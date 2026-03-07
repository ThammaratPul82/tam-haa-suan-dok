#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

std::string getNameByID(std::string targetID) {
    std::ifstream file("users.csv"); 
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: ไม่สามารถเปิดไฟล์ users.csv ได้" << std::endl;
        return "";
    }

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string id, name;

        if (std::getline(ss, id, ',')) {
            if (std::getline(ss, name, ',')) {
                if (id == targetID) {
                    file.close();
                    return name;
                }
            }
        }
    }

    file.close();
    return "";
}