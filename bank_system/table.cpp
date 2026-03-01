#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include <windows.h>
#include "statement.h" //

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            CreateStatementUI(hWnd, "123456"); // เรียกใช้ฟังก์ชันจาก header
            break;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            SetTextColor(hdc, RGB(0, 71, 171));
            HFONT hFont = CreateFont(26, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 0, 0, CLEARTYPE_QUALITY, 0, L"Segoe UI");
            SelectObject(hdc, hFont);
            TextOutW(hdc, 20, 25, L"FAM SOD BANK - Statement", 24);
            DeleteObject(hFont);
            EndPaint(hWnd, &ps);
        } break;
        case WM_DESTROY: PostQuitMessage(0); break;
        default: return DefWindowProcW(hWnd, msg, wp, lp);
    }
    return 0;
}

// ใช้ wWinMain เพื่อแก้ปัญหา undefined reference to wWinMain
int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPWSTR lpCmd, int nShow) {
    WNDCLASSEXW wc = { 0 };
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"BankTableClass";
    RegisterClassExW(&wc);
    HWND hWnd = CreateWindowExW(0, L"BankTableClass", L"Statement History", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
                                CW_USEDEFAULT, CW_USEDEFAULT, 600, 500, NULL, NULL, hInst, NULL);
    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return (int)msg.wParam;
}