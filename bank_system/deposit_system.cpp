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
    string name;
    string password;
    int attemp;
    double balance;
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
    string time;

    //open file 
    ifstream filein("balance.csv"); //add new path of balance
    string line;
    while(getline(filein,line)){
        if(line.empty()) continue;
        stringstream ss(line);
        string id, name, pass, att, b;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, pass, ',');
        getline(ss, att, ',');
        getline(ss, b);

        if (id.empty() || b.empty()) continue;

        try {
            int attempt = stoi(att);
            double balance = stod(b);
            
            account.push_back({id, name, pass, attempt, balance});
        } catch (...) {
            continue; 
        }
    }
    filein.close();

    //input
    cout << "-----ฝากเงิน------" << "\n";
    
    cout << "กรุณากรอกเลขบัญชี (จำนวน 9 หลัก) : " ;
    cin >> findid;
    if(findid.length() != 9) {
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
            time= getCurrentTime(); 
            dep = true;
            cout << "-----ฝากเงินสำเร็จ-----" << "\n";
            cout << "เวลาทำรายการ  : " << time<< "\n";
            cout << "ยอดเงินคงเหลือ : " << fixed << setprecision(2) << acc.balance << " บาท\n";
            break;
        }
    }

    //save
    if (dep) {
        ofstream fileb("balance.csv"); //add new path of balance
        for (const auto &acc : account) {
            fileb << acc.id << "," 
                  << acc.name << ","
                  << acc.password << ","
                  << acc.attemp << ","
                  << fixed << setprecision(2) << acc.balance << "\n";

        }
        fileb.close();
        
        ofstream filed("database.csv", ios::app);
        filed << findid << "," 
                << fixed << setprecision(2) << amount << "," 
                << "0.00,"
                << time << "," 
                << "1" << "\n";
                
        filed.close();
    } else {
        cout << "ไม่พบเลขบัญชีในระบบ (" << findid << ")\n";
    }
}

int main() {
    deposit_system();
    return 0;
}

