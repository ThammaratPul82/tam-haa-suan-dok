#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

inline string cleanString(string str) {
    string res = "";
    for (char c : str) {
        if (c != ' ' && c != '\r' && c != '\n' && c != '\t') res += c;
    }
    return res;
}

vector<vector<string>> fetch_data(string id) {
    ifstream file("D:\\year1\\1-2\\Compro\\project\\TAM-HAA-SUAN-DOK\\Main\\database.csv"); 
    string line;
    vector<vector<string>> data;
    vector<string> keep;

    if (!file.is_open()) return {{"-1"}};

    while (getline(file, line)) {
        stringstream ss(line);
        string s;
        vector<string> temp;
        
        while (getline(ss, s, ',')) {
            temp.push_back(cleanString(s));
        }
        if (temp.size() < 5) continue;

        if (temp[0] == id) {
            size_t colonPos = temp[3].find(':');
            string date = (colonPos != string::npos && colonPos >= 2) ? temp[3].substr(0, colonPos - 2) : temp[3];
            string time = (colonPos != string::npos && colonPos >= 2) ? temp[3].substr(colonPos - 2) : "";

            vector<string> formatted;
            formatted.push_back(date);
            formatted.push_back(time);

            if (temp[4] == "1") {
                if (stod(temp[1]) > 0) {
                    formatted.push_back("DEPOSIT");
                    formatted.push_back("+" + temp[1]);
                } else {
                    formatted.push_back("WITHDRAWAL");
                    formatted.push_back("-" + temp[2]);
                }
            } 
            else if (temp[4] == "TRANSFER_IN") {
                formatted.push_back("RECEIVE");
                formatted.push_back("+" + temp[1]);
            } 
            else {
                formatted.push_back("TRANSFER " + keep[0]);
                formatted.push_back("-" + temp[2]);
            }
            
            data.push_back(formatted);
        }
        keep = temp;
    }
    file.close();
    return data;
}