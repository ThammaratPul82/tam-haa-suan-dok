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
    
    
    string username ,name,password;
    cout << "Enter username : ";
    cin >> username; 
    bool state_username = false;  //set non
    for (int i = 0; i < user_info.size(); i++) { 
        //cout << username << " == " << user_info[i].username<< endl ;     ***** debugging system  *******
        if (username == user_info[i].username){ 
            state_username = true;   //set contain
            break ; 
        }else state_username = false; //set non
  
    }

    if (state_username == true)  cout << "Account already exists" ; 
    else {
        cout << "Password : " <<endl; 
        cin >> password ; 
        cout << "Name : " <<endl;
        cin >> name ; 
    }





    user_info.push_back({username, name, password, 0});
    saveToFile(user_info);
}