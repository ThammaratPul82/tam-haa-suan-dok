#include <windows.h>

#define ID_BTN_LOGIN 1
#define ID_BTN_SIGNIN 2
#define ID_BTN_EXIT 3

HFONT hFont, hTitleFont; // ตัวแปรสำหรับเก็บฟอนต์

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE: {
            // 1. สร้างฟอนต์ (ขนาด 20 สำหรับปุ่ม, ขนาด 48 สำหรับหัวข้อ)
            hFont = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "Segoe UI");
            hTitleFont = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "Segoe UI");

            // 2. สร้างหัวข้อธนาคาร
            HWND hTitle = CreateWindow("Static", "FAM SOD BANK", WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 80, 800, 70, hwnd, NULL, NULL, NULL);
            SendMessage(hTitle, WM_SETFONT, (WPARAM)hTitleFont, TRUE);

            // 3. สร้างปุ่มและใส่ฟอนต์
            HWND btn1 = CreateWindow("Button", "LOG-IN", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 300, 250, 200, 50, hwnd, (HMENU)ID_BTN_LOGIN, NULL, NULL);
            HWND btn2 = CreateWindow("Button", "SIGN IN", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 300, 320, 200, 50, hwnd, (HMENU)ID_BTN_SIGNIN, NULL, NULL);
            HWND btn3 = CreateWindow("Button", "EXIT", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 300, 450, 200, 40, hwnd, (HMENU)ID_BTN_EXIT, NULL, NULL);
            
            SendMessage(btn1, WM_SETFONT, (WPARAM)hFont, TRUE);
            SendMessage(btn2, WM_SETFONT, (WPARAM)hFont, TRUE);
            SendMessage(btn3, WM_SETFONT, (WPARAM)hFont, TRUE);
            break;
        }

        case WM_CTLCOLORSTATIC: {
            // 4. ทำให้พื้นหลังตัวหนังสือโปร่งใสและเปลี่ยนสีตัวอักษรเป็นสีขาว
            HDC hdcStatic = (HDC)wp;
            SetTextColor(hdcStatic, RGB(255, 255, 255)); // สีขาว
            SetBkMode(hdcStatic, TRANSPARENT);
            return (INT_PTR)CreateSolidBrush(RGB(0, 100, 0)); // สีเขียวเข้มเดียวกับพื้นหลัง
        }

        case WM_COMMAND:
            if (LOWORD(wp) == ID_BTN_EXIT) PostQuitMessage(0);
            break;

        case WM_DESTROY:
            DeleteObject(hFont); // ลบฟอนต์ออกจากหน่วยความจำเมื่อปิดโปรแกรม
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
    wc.lpszClassName = "myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClass(&wc)) return -1;

    CreateWindow("myWindowClass", "FAM SOD BANK - Modern UI", 
                 WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, 
                 100, 100, 800, 600, NULL, NULL, hInst, NULL);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}