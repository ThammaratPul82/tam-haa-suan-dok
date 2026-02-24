#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

void createIMG(string id, string type, string amount, string balance) {
    string temp = "E:/Projects/p1/generateSlip/create_img.exe " + id + " " + type + " " + amount + " " + balance;
    system(temp.c_str());
}