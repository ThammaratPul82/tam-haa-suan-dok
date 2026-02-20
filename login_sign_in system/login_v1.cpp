#include <iostream> 
#include <fstream> 
#include <sstream> //seperate text by comma 
#include <vector>
#include <string> 
using namespace std;

int main(){
    ifstream file("users.csv") ;
    string line ; 
    vector<vector<string>> user_info ;

    if (!file.is_open()) {
        cerr << "can not open ! " << endl; 
        return 1 ; 
    }





    while (getline(file, line)){
        stringstream ss(line);  //ถ้าไม่ใช่จะแยกบรรทัดไม่ได้
        string value ; 
        vector <string> blow; 
    
    while (getline(ss, value, ',')) {
            blow.push_back(value);
        }
        user_info.push_back(blow);   //assing ใส่ เวกเตอร์ 2 มิติ
        
    }
    string user_input,pass_input; 
    cout << "Input your username :" ; 
    cin >> user_input; 
    for (int i = 0; i < user_info.size(); i++) {   //check user_
    //cout << user_info[i][0] << endl;   // check run <<<---------------->>>>
        if(user_input == user_info[i][0]){
            cout << "Input your password :"  ; 
            cin >> pass_input; 
            
                //cout <<"pass :"<< user_info[i][2] << endl;   // check run <<<---------------->>>>
               if(pass_input == user_info[i][2]) cout << "correct password "  << endl ; 
               else {
                    user_info[i][3] = "1" ; 
                    cout << user_info[i][3] ;
               }
        }
    }

    file.close(); // ปิดไฟล์เมื่อใช้งานเสร็จ
    return 0;
}