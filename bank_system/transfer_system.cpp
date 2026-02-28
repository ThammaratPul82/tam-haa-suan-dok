#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip> 
#include <ctime>

using namespace std;



struct Acc{
    string id;
    string name;
    string password;
    int attemp;
    string day;
    double balance;
};

string getCurrentTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", ltm);
    return string(buffer);
}


void transfer_system(){
    string findidf;
    string findidl;
    double amount;
    vector<Acc> account;
    string time;
    bool dep = false;
    bool w = false;

    //open file 
    ifstream filein("balance.csv"); //add new path of balance
    string line;
    while(getline(filein,line)){
        if(line.empty()) continue;
        stringstream ss(line);
        string id, name, pass, att, day, b;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, pass, ',');
        getline(ss, att, ',');
        getline(ss, day, ',');
        getline(ss, b);

        if (id.empty() || b.empty()) continue;

        try {
            int attempt = stoi(att);
            double balance = stod(b);
            account.push_back({id, name, pass, attempt, day,balance});
        } catch (...) {
            continue; 
        }
    }
    filein.close();
    //input
    cout << "-----โอนเงิน------" << "\n";
    
    cout << "กรุณากรอกเลขบัญชีของท่าน (จำนวน 9 หลัก) : " ;
    cin >> findidf;
    if(findidf.length() != 9) {
        cout << "เลขบัญชีไม่ถูกต้อง";
        return;
    }
    cout << "กรุณากรอกเลขบัญชีปลายทาง (จำนวน 9 หลัก) : " ;
    cin >> findidl;
    if(findidl.length() != 9) {
        cout << "เลขบัญชีไม่ถูกต้อง";
        return;
    }
    

    //Update
    Acc* sender =nullptr;
    Acc* receiver=nullptr;

    for (auto &acc : account) {
        if (acc.id == findidf) sender = &acc;   
        if (acc.id == findidl) receiver = &acc; 
    }
    if (!sender) {
        cout << "ไม่พบบัญชีต้นทางในระบบ!\n";
        return;
    }
    if (!receiver) {
        cout << "ไม่พบบัญชีปลายทางในระบบ!\n";
        return;
    }

    cout << "ยอดเงินคงเหลือปัจจุบันของคุณ: " << fixed << setprecision(2) << sender->balance << " บาท\n";
    cout << "กรุณากรอกจำนวนเงินที่ต้องการโอน: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "จำนวนเงินไม่ถูกต้อง\n";
        return;
    }
    if (amount > sender->balance) {
        cout << "ยอดเงินในบัญชีไม่เพียงพอ!\n";
        return;
    }

    sender->balance -= amount;
    receiver->balance += amount;
    time = getCurrentTime();
    
     //save
    ofstream fileb("balance.csv");
    for (const auto &acc : account) {
        fileb << acc.id << "," 
              << acc.name << ","
              << acc.password << ","
              << acc.attemp << ","
              << acc.day << ","
              << fixed << setprecision(2) << acc.balance << "\n";
    }
    fileb.close();

    ofstream filed("database.csv", ios::app);
    if (filed) {
        filed << sender->id << "," 
              << "0.00,"                                     
              << fixed << setprecision(2) << amount << ","   
              << time << "," 
              << "1" << "\n";
        filed << receiver->id << "," 
              << fixed << setprecision(2) << amount << ","   
              << "0.00,"                                     
              << time << "," 
              << "1" << "\n";
              
        filed.close();
    }
    // แสดงผลสำเร็จ
    cout << "\n----- โอนเงินสำเร็จ -----\n";
    cout << "โอนเงินไปยังบัญชี : " << receiver->id << "\n";
    cout << "จำนวนเงิน       : " << fixed << setprecision(2) << amount << " บาท\n";
    cout << "เวลาทำรายการ    : " << time << "\n";
    cout << "ยอดเงินคงเหลือของคุณ: " << fixed << setprecision(2) << sender->balance << " บาท\n";
}


int main() {
    transfer_system();
    return 0;
}

