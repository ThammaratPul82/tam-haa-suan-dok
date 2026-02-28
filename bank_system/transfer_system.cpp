#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip> 
#include <ctime>

using namespace std;

//update19/2/26 1

struct Acc{
    string id;
    double balance;
    string time;
    bool status;
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
    bool dep = false;
    bool w = false;

    //open file 
    ifstream filein("database.csv");
    string line;
    while(getline(filein,line)){
        if(line.empty()) continue;
        stringstream ss(line);
        string id,b,time,boo;
        getline (ss,id,',');
        getline (ss,b,',');
        getline (ss,time);
        getline (ss,boo);

        if (id.empty() || b.empty()) continue;

        try {
            account.push_back({id, stod(b), time, true});
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
    sender->time = getCurrentTime();

    receiver->balance += amount;
    receiver->time = getCurrentTime();


    //save
    ofstream fileout("database.csv");
    for (const auto &acc : account) {
        fileout << acc.id << "," 
                << fixed << setprecision(2) << acc.balance << "," 
                << acc.time << ","
                << "1" << endl;
    }
    fileout.close();

    // แสดงผลสำเร็จ
    cout << "\n----- โอนเงินสำเร็จ -----\n";
    cout << "โอนเงินไปยังบัญชี : " << receiver->id << "\n";
    cout << "จำนวนเงิน       : " << fixed << setprecision(2) << amount << " บาท\n";
    cout << "เวลาทำรายการ    : " << sender->time << "\n";
    cout << "ยอดเงินคงเหลือของคุณ: " << fixed << setprecision(2) << sender->balance << " บาท\n";
}


int main() {
    transfer_system();
    return 0;
}

