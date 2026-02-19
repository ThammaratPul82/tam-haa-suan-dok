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


void deposit_system(){
    string findid;
    double amount;
    vector<Acc> account;
    bool dep = false;

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

        if (id.empty() || b.empty()) continue;

        try {
            account.push_back({id, stod(b), time});
        } catch (...) {
            continue; 
        }
    }
    filein.close();

    //input
    cout << "-----ฝากเงิน------" << "\n";
    
    cout << "กรุณากรอกเลขบัญชี (จำนวน 6 หลัก) : " ;
    cin >> findid;
    if(findid.length() != 6) {
        cout << "เลขบัญชีไม่ถูกต้อง";
        return;
    }
    
    cout << "กรุณากรอกจำนวนเงินที่ต้องการฝาก : ";
    cin >> amount;
    if (amount<=0) {
        cout << "จำนวนเงินไม่ถูกต้อง";
        return;
    }

    //Update
    for (auto &acc : account) {
        if (acc.id == findid) {

            acc.balance += amount;         
            acc.time= getCurrentTime(); 
            dep = true;
            cout << "-----ฝากเงินสำเร็จ-----" << "\n";
            cout << "เวลาทำรายการ  : " << acc.time<< "\n";
            cout << "ยอดเงินคงเหลือ : " << fixed << setprecision(2) << acc.balance << " บาท\n";
            break;
        }
    }

    //save
    if (dep) {
        ofstream fileout("database.csv");
        for (const auto &acc : account) {
            fileout << acc.id << "," 
                    << fixed << setprecision(2) << acc.balance << "," 
                    << acc.time << "," ;
                    
        }
        fileout.close();
    } else {
        cout << "ไม่พบเลขบัญชีในระบบ (" << findid << ")\n";
    }
}

int main() {
    deposit_system();
    return 0;
}

