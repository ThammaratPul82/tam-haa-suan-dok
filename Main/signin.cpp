#include "sign-in.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include "user_system.h"

// std::vector<Users> user_info;

// ===== โหลดข้อมูล =====


// ===== วันที่ปัจจุบัน =====
/*std::string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", ltm);
    return std::string(buffer);
}
*/

// ===== ฟังก์ชันสมัครสมาชิก =====
bool registerUser(const std::string& username,
                  const std::string& password,
                  const std::string& name)
{
    loadUsers();
    // ตรวจว่าซ้ำไหม
    for (const auto& u : user_info) {
        if (u.username == username) {
            return false;  // มี user แล้ว
        }
    }

    // เพิ่ม user ใหม่
    User newUser;
    newUser.username = username;
    newUser.password = password;
    newUser.name_surname = name;
    newUser.attempt = 0;
    newUser.date_time = getCurrentDate();
    newUser.balance = 0;

    user_info.push_back(newUser);
    saveToFile();

    return true;
}