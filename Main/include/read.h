#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

vector<vector<string>> fetch_name(string id1, string id2) {
    ifstream file("../users.csv"); 
    string line;
    vector<vector<string>> x;

    while (getline(file, line)) {
        stringstream ss(line);
        string s;
        vector<string> temp;
        
        int i=0,
            c1 = 1,
            c2 = 1;

        while (getline(ss, s, ',')) {
            i=0;
            if (c1 && id1 == s) {
                if (i < 2) {
                    temp.push_back(s);
                    ++i;
                }
                c1 = 0;
            } else if (c2 && id2 == s) {
                if (i < 2) {
                    temp.push_back(s);
                    ++i;
                }
                c2 = 0;
            }
            if (temp.size() > 0) x.push_back(temp);
        }
    }

    return x;
}