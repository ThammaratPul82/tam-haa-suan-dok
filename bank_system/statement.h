#ifndef STATEMENT_H
#define STATEMENT_H

#include <windows.h>
#include <commctrl.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// --- 1. Helper Functions ---

// ฟังก์ชันล้างช่องว่างและอักขระพิเศษท้ายบรรทัด
inline string cleanString(string str) {
    string res = "";
    for (char c : str) {
        if (c != ' ' && c != '\r' && c != '\n' && c != '\t') res += c;
    }
    return res;
}

// ฟังก์ชันแปลง string (UTF-8) เป็น wstring (Unicode) สำหรับ Win32 UI
inline wstring s2ws(const string& s) {
    if (s.empty()) return L"";
    int len = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.length(), NULL, 0);
    wstring ws(len, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.length(), &ws[0], len);
    return ws;
}

// --- 2. Data Logic (CSV Parsing) ---

// ปรับตามรูปแบบไฟล์ของเจ้านาย: ID, Balance, Date Time, Status
inline vector<vector<string>> fetch_data(string id) {
    ifstream file("database.csv"); //
    string line;
    vector<vector<string>> data;

    if (!file.is_open()) {
        MessageBoxA(NULL, "ไม่พบไฟล์ database.csv ในโฟลเดอร์โปรเจกต์!", "File Error", MB_ICONERROR);
        return data;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string s;
        vector<string> temp_row;
        
        while (getline(ss, s, ',')) {
            temp_row.push_back(cleanString(s));
        }

        // ตรวจสอบ ID (อยู่หลักแรก Index 0)
        if (!temp_row.empty() && temp_row[0] == id) {
            vector<string> formatted;
            
            // จัดเรียงใหม่เพื่อโชว์ในตาราง: Date, Type, Amount, Balance
            // 1. Date (จาก Index 2)
            formatted.push_back(temp_row.size() > 2 ? temp_row[2] : "-");
            
            // 2. Type (จาก Index 3: 1 = ฝาก, 0 = ถอน)
            string status = (temp_row.size() > 3) ? temp_row[3] : "";
            formatted.push_back(status == "1" ? "DEPOSIT" : "WITHDRAWAL");
            
            // 3. Amount (ใช้ค่าจาก Index 1)
            formatted.push_back(temp_row.size() > 1 ? temp_row[1] : "0.00");
            
            // 4. Balance (ใช้ค่าจาก Index 1)
            formatted.push_back(temp_row.size() > 1 ? temp_row[1] : "0.00");

            data.push_back(formatted);
        }
    }
    file.close();
    return data;
}

// --- 3. UI Function (Win32 ListView) ---

#define ID_LISTVIEW 2001

inline void CreateStatementUI(HWND hWnd, string userId) {
    // โหลด Visual Style สำหรับ Common Controls รุ่นใหม่
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(icex);
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);

    // สร้างตาราง ListView (SysListView32)
    HWND hLV = CreateWindowEx(
        0, WC_LISTVIEW, L"", 
        WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_SINGLESEL, 
        20, 80, 545, 320, 
        hWnd, (HMENU)ID_LISTVIEW, GetModuleHandle(NULL), NULL
    );

    // ตั้งค่าสไตล์ Modern: เลือกทั้งแถว, มีเส้นตาราง, กันกระพริบ
    ListView_SetExtendedListViewStyle(hLV, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER);

    // เพิ่มหัวตาราง (Columns)
    const wchar_t* headers[] = { L"Date Time", L"Transaction", L"Amount (THB)", L"Remaining" };
    int widths[] = { 160, 100, 130, 130 };
    LVCOLUMNW lvc = { 0 };
    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    
    for (int i = 0; i < 4; i++) {
        lvc.iSubItem = i;
        lvc.pszText = (LPWSTR)headers[i];
        lvc.cx = widths[i];
        lvc.fmt = LVCFMT_LEFT;
        SendMessageW(hLV, LVM_INSERTCOLUMNW, i, (LPARAM)&lvc);
    }

    // ดึงข้อมูลและใส่ลงตาราง
    vector<vector<string>> csvData = fetch_data(userId);
    
    for (int i = 0; i < csvData.size(); i++) {
        LVITEMW lvi = { 0 };
        lvi.mask = LVIF_TEXT; //
        lvi.iItem = i;
        lvi.iSubItem = 0;
        
        // ใส่ข้อมูลช่องแรก (Date)
        wstring wDate = s2ws(csvData[i][0]);
        lvi.pszText = (LPWSTR)wDate.c_str();
        SendMessageW(hLV, LVM_INSERTITEMW, 0, (LPARAM)&lvi);

        // ใส่ข้อมูลช่องย่อย (Type, Amount, Balance)
        for (int j = 1; j < 4; j++) {
            wstring wVal = s2ws(csvData[i][j]);
            ListView_SetItemText(hLV, i, j, (LPWSTR)wVal.c_str());
        }
    }
}

#endif