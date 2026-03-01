#ifndef ALL_H
#define ALL_H

#include <string>
using namespace std;

struct Acc{
    string id;
    string name;
    string password;
    int attemp;
    string day;
    double balance;
};


string getCurrentTime();

#endif
