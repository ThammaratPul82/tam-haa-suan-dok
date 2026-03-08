#ifndef RUNCREATE_IMG_H
#define RUNCREATE_IMG_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <shellapi.h>

inline void createIMG(std::string id, std::string type, std::string amount, std::string balance) {
    std::string exePath = "D:/year1/1-2/Compro/project/TAM-HAA-SUAN-DOK/Main/slip_system/create_img.exe";
    std::string workingDir = "D:/year1/1-2/Compro/project/TAM-HAA-SUAN-DOK/Main/slip_system/";
    
    std::string args = id + " \"" + type + "\" " + amount + " \"" + balance;

    ShellExecuteA(NULL, "open", exePath.c_str(), args.c_str(), workingDir.c_str(), SW_HIDE);
}

inline void createSlip(std::string id1, std::string n1, std::string id2, std::string n2, std::string amount) {
    std::string exePath = "D:/year1/1-2/Compro/project/TAM-HAA-SUAN-DOK/Main/slip_system/create_transfer.exe";
    std::string workingDir = "D:/year1/1-2/Compro/project/TAM-HAA-SUAN-DOK/Main/slip_system/";
    
    std::string args = id1 + " \"" + n1 + "\" " + id2 + " \"" + n2 + "\" " + amount;

    ShellExecuteA(NULL, "open", exePath.c_str(), args.c_str(), workingDir.c_str(), SW_HIDE);
}

#endif