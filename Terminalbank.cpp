#include <windows.h>

// 1. กำหนด ID สำหรับปุ่มต่างๆ
#define ID_BTN_LOGIN 1
#define ID_BTN_SIGNIN 2
#define ID_BTN_EXIT 3
#define ID_BTN_SUBMIT_LOGIN 4
#define ID_BTN_SUBMIT_CREATE 5
#define ID_BTN_BACK 6

// 2. ตัวแปร Global สำหรับ Handle ต่างๆ
HFONT hFont, hTitleFont;
HWND hTitle, btn1, btn2, btn3; 
HWND hStaticUser, hEditUser, hStaticPass, hEditPass, hBtnSubmitLogin; 
HWND hStaticNewUser, hEditNewUser, hStaticNewBankID, hEditNewBankID, hStaticNewPass, hEditNewPass, hBtnSubmitCreate;

// 3. ฟังก์ชันซ่อนปุ่มหน้าแรก
void HideMainPage() {
    ShowWindow(btn1, SW_HIDE);
    ShowWindow(btn2, SW_HIDE);
    ShowWindow(btn3, SW_HIDE);
}

// 4. หน้า Login
void CreateLoginUI(HWND hwnd) {
    HideMainPage();
    
    hStaticUser = CreateWindow("Static", "Username:", WS_VISIBLE | WS_CHILD, 250, 222, 100, 25, hwnd, NULL, NULL, NULL);
    hEditUser = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 350, 220, 200, 30, hwnd, NULL, NULL, NULL);
    hStaticPass = CreateWindow("Static", "Password:", WS_VISIBLE | WS_CHILD, 250, 272, 100, 25, hwnd, NULL, NULL, NULL);
    hEditPass = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 350, 270, 200, 30, hwnd, NULL, NULL, NULL);
    hBtnSubmitLogin = CreateWindow("    Button", "CONFIRM LOGIN", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 300, 350, 200, 50, hwnd, (HMENU)ID_BTN_SUBMIT_LOGIN, NULL, NULL);

    SendMessage(hEditUser, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hEditPass, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnSubmitLogin, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hStaticUser, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hStaticPass, WM_SETFONT, (WPARAM)hFont, TRUE);
}

// 5. หน้า Create Account (ปรับปรุงตามที่สั่ง)
void CreateAccountUI(HWND hwnd) {
    HideMainPage();
    CreateWindow("Static", "CREATE YOUR ACCOUNT", WS_VISIBLE | WS_CHILD | SS_CENTER, 200, 160, 400, 30, hwnd, NULL, NULL, NULL);
    
    hStaticNewUser = CreateWindow("Static", "Username:", WS_VISIBLE | WS_CHILD, 200, 212, 120, 25, hwnd, NULL, NULL, NULL);
    hEditNewUser = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 330, 210, 250, 30, hwnd, NULL, NULL, NULL);
    
    // เปลี่ยนเป็น 8 digits
    hStaticNewBankID = CreateWindow("Static", "Bank ID (8 digits):", WS_VISIBLE | WS_CHILD, 200, 262, 120, 25, hwnd, NULL, NULL, NULL);
    hEditNewBankID = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 330, 260, 250, 30, hwnd, NULL, NULL, NULL);
    
    // เอา (Numbers) ออก
    hStaticNewPass = CreateWindow("Static", "Password:", WS_VISIBLE | WS_CHILD, 200, 312, 120, 25, hwnd, NULL, NULL, NULL);
    hEditNewPass = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD | ES_NUMBER, 330, 310, 250, 30, hwnd, NULL, NULL, NULL);
    
    hBtnSubmitCreate = CreateWindow("Button", "CONFIRM REGISTRATION", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 300, 380, 200, 50, hwnd, (HMENU)ID_BTN_SUBMIT_CREATE, NULL, NULL);

    SendMessage(hEditNewUser, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hEditNewBankID, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hEditNewPass, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnSubmitCreate, WM_SETFONT, (WPARAM)hFont, TRUE);
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE: {
            hFont = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "Segoe UI");
            hTitleFont = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "Segoe UI");

            hTitle = CreateWindow("Static", "FAM SOD BANK", WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 80, 800, 70, hwnd, NULL, NULL, NULL);
            SendMessage(hTitle, WM_SETFONT, (WPARAM)hTitleFont, TRUE);

            btn1 = CreateWindow("Button", "LOG-IN", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 300, 250, 200, 50, hwnd, (HMENU)ID_BTN_LOGIN, NULL, NULL);
            btn2 = CreateWindow("Button", "CREATE ACCOUNT", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 300, 320, 200, 50, hwnd, (HMENU)ID_BTN_SIGNIN, NULL, NULL);
            btn3 = CreateWindow("Button", "EXIT", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 300, 450, 200, 40, hwnd, (HMENU)ID_BTN_EXIT, NULL, NULL);
            
            SendMessage(btn1, WM_SETFONT, (WPARAM)hFont, TRUE);
            SendMessage(btn2, WM_SETFONT, (WPARAM)hFont, TRUE);
            SendMessage(btn3, WM_SETFONT, (WPARAM)hFont, TRUE);
            break;
        }

        case WM_CTLCOLORSTATIC: {
            HDC hdcStatic = (HDC)wp;
            SetTextColor(hdcStatic, RGB(255, 255, 255));
            SetBkMode(hdcStatic, TRANSPARENT);
            return (INT_PTR)CreateSolidBrush(RGB(0, 100, 0)); 
        }

        case WM_COMMAND:
            if (LOWORD(wp) == ID_BTN_LOGIN) CreateLoginUI(hwnd);
            if (LOWORD(wp) == ID_BTN_SIGNIN) CreateAccountUI(hwnd);
            if (LOWORD(wp) == ID_BTN_EXIT) PostQuitMessage(0);

            if (LOWORD(wp) == ID_BTN_SUBMIT_CREATE) {
                char newBankID[12];
                GetWindowText(hEditNewBankID, newBankID, 12);
                
                
                if (lstrlen(newBankID) != 8) {
                    MessageBox(hwnd, "Bank ID must be exactly 8 digits!", "Error", MB_OK | MB_ICONWARNING);
                } else {
                    MessageBox(hwnd, "Account Created Successfully!", "Success", MB_OK | MB_ICONINFORMATION);
                }
            }
            break;

        case WM_DESTROY:
            DeleteObject(hFont);
            DeleteObject(hTitleFont);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

// 7. ส่วนฟังก์ชันหลัก
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASS wc = {0};
    wc.hbrBackground = CreateSolidBrush(RGB(0, 100, 0)); 
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = "myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClass(&wc)) return -1;

    CreateWindow("myWindowClass", "FAM SOD BANK - GUI", 
                 WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, 
                 100, 100, 800, 600, NULL, NULL, hInst, NULL);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}