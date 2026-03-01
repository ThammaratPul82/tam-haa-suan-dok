#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

void createIMG(string id, string type, string amount, string balance) {
    string temp = "E:/Projects/p1/generateSlip/create_img.exe " + id + " " + type + " " + amount + " " + balance;
    system(temp.c_str());
}

void createSlip(string id1, string n1, string id2, string n2, string amount) {
    string temp = "E:/Projects/p1/generateSlip/create_transfer.exe " + id1 + " \"" + n1 + "\" " + id2 + " \"" + n2 + "\" " + amount;
    system(temp.c_str());
}