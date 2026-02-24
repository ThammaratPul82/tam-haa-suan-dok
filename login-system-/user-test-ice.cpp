#include <iostream> 
#include <fstream> 
#include <sstream> //seperate text by comma 
#include <vector>
#include <string> 
using namespace std;

struct User {
    string username;
    string name_surname;
    string password;
    int  attempt;
};
vector<User> user_info;


void saveToFile(const vector<User> &user_info) {   //input vector โง่ๆ
    ofstream outFile("users.csv");

    if (outFile.is_open()) {
        for (const auto &u : user_info) {  //ใช้ auto เพราะเรื่อง datatype มันจะทำให้เองเลย และ วนจนกว่าจะครบ
            outFile << u.username << ","
                    << u.name_surname << ","
                    << u.password << ","
                    << u.attempt << "\n";
        }
        outFile.close();
    }
}

int main(){
    ifstream file("users.csv") ;
    string line ; 
    bool status = false ;
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
        //user_info.push_back(blow);   //assing ใส่ เวกเตอร์ 2 มิติ       
        if (blow.size() >= 4) {
            User u;
            u.username = blow[0];
            u.name_surname = blow[1];
            u.password = blow[2];
            u.attempt = stoi(blow[3]); // แปลง string เป็น int          
            user_info.push_back(u);
        }

    }
    string user_input,pass_input; 
    cout << "Input your username : " ; 
    cin >> user_input; 
    for (int i = 0; i < user_info.size(); i++) {   //check user_
    //cout << user_info[i][0] << endl;   // check run <<<---------------->>>>
        if(user_input == user_info[i].username){
            status = true ;
            while(user_info[i].attempt <= 3){
                cout << "Input your password : "  ; 
                cin >> pass_input; 
                if(pass_input == user_info[i].password) {
                    cout << "correct password "  << endl ; 
                    user_info[i].attempt = 0;
                    saveToFile(user_info); 
                    break;

                } else if(user_info[i].attempt >=3) {
                    cout << "Contact Bank to login";
                    saveToFile(user_info); 
                    break;

                }else {
                    user_info[i].attempt += 1;
                    cout << "You enter wrong password " << endl ;
                    cout << "Your attempt is : "<< user_info[i].attempt << " / 3" << endl;
                    cout << "--------------------------------------------\n";
                }
        }
    } 
        
    } if(status == false){
        cout << "You Enter wrong username !" << endl ;
        cout << "Have you had an account yet? " << endl ;
    }  

    file.close(); // ปิดไฟล์เมื่อใช้งานเสร็จ
    return 0;
}