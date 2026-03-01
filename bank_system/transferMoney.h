#include <iostream>
#include "user_system.h"
#include "statement.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

bool transferTo(string tarId, int amount) {
    ifstream file(".../users.csv");
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string s;

        if (getline(ss, s, ','))
        {
            if (tarId == s)
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
    return data;while (getline(file, line))
    {
        
    }
}