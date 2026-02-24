#include <windows.h>
#include <cstdio> 


#define ID_BTN_DEPOSIT  101
#define ID_BTN_WITHDRAW 102
#define ID_BTN_TRANSFER 103
#define ID_BTN_LOGOUT   104

HFONT hFont, hTitleFont;
HWND hStaticBalance, hStaticAccount;
double userBalance = 5000.00; // ยอดเงินเริ่มต้น

// คำสั่งเมื่อกดปุ่ม
void HandleTransaction(HWND hwnd, int btnID) {
    char buf[50];
    if (btnID == ID_BTN_DEPOSIT) {
        userBalance += 100.0; // ฝากทีละ 100
        MessageBox(hwnd, "Deposited $100 successfully!", "Success", MB_OK | MB_ICONINFORMATION);
    } 
    else if (btnID == ID_BTN_WITHDRAW) {
        if (userBalance >= 100.0) {
            userBalance -= 100.0; // ถอนทีละ 100
            MessageBox(hwnd, "Withdrew $100 successfully!", "Success", MB_OK | MB_ICONINFORMATION);
        } else {
            MessageBox(hwnd, "Insufficient funds!", "Error", MB_OK | MB_ICONERROR);
        }
    }
    else if (btnID == ID_BTN_TRANSFER) {
        MessageBox(hwnd, "Transfer System: Please enter account number.", "Transfer", MB_OK);
    }

    // อัปเดตยอดเงิน
    sprintf(buf, "BALANCE: $%.2f", userBalance);
    SetWindowText(hStaticBalance, buf);
}
    LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
        switch (msg) {
            case WM_CREATE: {
                hFont = CreateFont(22, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "Segoe UI");
                hTitleFont = CreateFont(55, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "Segoe UI");

                HWND hTitle = CreateWindow("Static", "FAM SOD BANK", WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 50, 800, 70, hwnd, NULL, NULL, NULL);
                SendMessage(hTitle, WM_SETFONT, (WPARAM)hTitleFont, TRUE);

                // เลขบัญชี
                hStaticAccount = CreateWindow("Static", "ACCOUNT ID: 12345678", WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 160, 800, 30, hwnd, NULL, NULL, NULL);
                SendMessage(hStaticAccount, WM_SETFONT, (WPARAM)hFont, TRUE);

                // ยอดเงินคงเหลือ
                char balText[50];
                sprintf(balText, "BALANCE: $%.2f", userBalance);
                hStaticBalance = CreateWindow("Static", balText, WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 200, 800, 60, hwnd, NULL, NULL, NULL);
                SendMessage(hStaticBalance, WM_SETFONT, (WPARAM)hTitleFont, TRUE);

                // ปุ่มฝาก ถอน โอน
                HWND btnDep = CreateWindow("Button", "DEPOSIT", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 100, 350, 180, 80, hwnd, (HMENU)ID_BTN_DEPOSIT, NULL, NULL);
                HWND btnWit = CreateWindow("Button", "WITHDRAW", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 310, 350, 180, 80, hwnd, (HMENU)ID_BTN_WITHDRAW, NULL, NULL);
                HWND btnTra = CreateWindow("Button", "TRANSFER", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 520, 350, 180, 80, hwnd, (HMENU)ID_BTN_TRANSFER, NULL, NULL);
                HWND btnLog = CreateWindow("Button", "EXIT SYSTEM", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 325, 480, 150, 40, hwnd, (HMENU)ID_BTN_LOGOUT, NULL, NULL);

                SendMessage(btnDep, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendMessage(btnWit, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendMessage(btnTra, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendMessage(btnLog, WM_SETFONT, (WPARAM)hFont, TRUE);
                break;
            }

        case WM_CTLCOLORSTATIC: {
            HDC hdcStatic = (HDC)wp;
            SetTextColor(hdcStatic, RGB(255, 255, 255)); // ข้อความสีขาว
            SetBkMode(hdcStatic, TRANSPARENT);
            return (INT_PTR)CreateSolidBrush(RGB(0, 100, 0)); // พื้นหลังเขียวธนาคาร
        }

        case WM_COMMAND:
            if (LOWORD(wp) == ID_BTN_LOGOUT) PostQuitMessage(0);
            else HandleTransaction(hwnd, LOWORD(wp));
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

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASS wc = {0};
    wc.hbrBackground = CreateSolidBrush(RGB(0, 100, 0));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = "MainDashboardClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClass(&wc)) return -1;

    CreateWindow("MainDashboardClass", "FAM SOD BANK - Management System", 
                 WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, 
                 100, 100, 800, 600, NULL, NULL, hInst, NULL);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}