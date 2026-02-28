#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip> 
#include <ctime>

using namespace std;

//update19/2/26 

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


void withdraw_system(){
    string findid;
    double amount;
    vector<Acc> account;
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

        if (id.empty() || b.empty()) continue;

        try {
            account.push_back({id, stod(b), time});
        } catch (...) {
            continue; 
        }
    }
    filein.close();

    //input
    cout << "-----ถอนเงิน------" << "\n";
    
    cout << "กรุณากรอกเลขบัญชี (จำนวน 9 หลัก) : " ;
    cin >> findid;
    if(findid.length() != 9) {
        cout << "เลขบัญชีไม่ถูกต้อง";
        return;
    }
    
    

    //Update
    for (auto &acc : account) {
        if (acc.id == findid) {
            cout << "ยอดเงินคงเหลือปัจจุบัน: " << fixed << setprecision(2) << acc.balance << " บาท\n";
            cout << "กรุณากรอกจำนวนเงินที่ต้องการถอน: ";
            cin >> amount;
            if (amount <= 0) {
                cout << "Error: จำนวนเงินไม่ถูกต้อง\n";
                return;
            }
            if (amount > acc.balance) {
                cout << "Error: ยอดเงินในบัญชีไม่เพียงพอ!\n";
                return;
            }

            // คำนวณยอดใหม่
            acc.balance -= amount;         
            acc.time = getCurrentTime();
            w = true;
            cout << "-----ถอนเงินสำเร็จ-----" << "\n";
            cout << "เวลาทำรายการ  : " << acc.time<< "\n";
            cout << "ยอดเงินคงเหลือ : " << fixed << setprecision(2) << acc.balance << " บาท\n";
            break;
        }
    }

    //save
    if (w) {
        ofstream fileout("database.csv");
        for (const auto &acc : account) {
            fileout << acc.id << "," 
                    << fixed << setprecision(2) << acc.balance << "," 
                    << acc.time << endl;
                    
        }
        fileout.close();
    } else {
        cout << "ไม่พบเลขบัญชีในระบบ (" << findid << ")\n";
    }
}

int main() {
    withdraw_system();
    return 0;
}

