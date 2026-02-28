#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

string cleanString(string str)
{
    string res = "";
    for (char c : str)
    {
        if (c != ' ' && c != '\r')
            res += c;
    }
    return res;
}

vector<vector<string>> fetch_data(string id)
{
    ifstream file("data.csv");
    string line;
    vector<vector<string>> data;

    while (getline(file, line))
    {
        stringstream ss(line);
        string s;
        vector<string> row;
        bool keep = 1;

        if (getline(ss, s, ','))
        {
            if (id == s)
            {
                while (getline(ss, s, ','))
                {
                    if ((!s.empty() && s.back() == '\r') || s.back() == '1')
                        s.pop_back();

                    row.push_back(s);

                    if (cleanString(s) == "0")
                        keep = 0;
                }
            }
            else
                continue;
        }

        if (keep && !row.empty())
            data.push_back(row);
    }
    return data;
}