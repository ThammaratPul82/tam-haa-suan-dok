#include <windows.h>
#include <string>
#include "login.h"
#include "sign-in.h"
#include "user_system.h"

#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;

#define ID_BTN_LOGIN_MENU   1
#define ID_BTN_SIGNIN_MENU  2
#define ID_BTN_EXIT         3
#define ID_BTN_LOGIN_DO     4
#define ID_BTN_BACK         5
#define ID_BTN_SIGN_IN_DO   6
#define ID_BTN_DEPOSITE     7
#define ID_BTN_WITHDRAW     8 
#define ID_BTN_TRANSFER     9
#define ID_BTN_LOGOUT       10

HFONT hFont, hTitleFont;

// ===== หน้าแรก =====
HWND btnLoginMenu, btnSigninMenu, btnExit;

// ===== หน้า Login =====
HWND hEditUser, hEditPass;
HWND btnLoginDo, btnBack;
HWND lblUser, lblPass;

// signin
HWND hEditName;
HWND btnSigninDo;
HWND lblName;

//home_bank
HWND btnDep;
HWND btnWit;
HWND btnTra;
HWND btnLog;

//AccBalan
HWND hStaticBalance, hStaticAccount;

double userBalance ; // ยอดเงินเริ่มต้น
std::string currentUser = "";
char balText[100];

HBRUSH hBrushBg;
ULONG_PTR gdiplusToken;
Image* imgDeposit = nullptr;

void ShowMainMenu() {
    ShowWindow(btnLoginMenu, SW_SHOW);
    ShowWindow(btnSigninMenu, SW_SHOW);
    ShowWindow(btnExit, SW_SHOW);

    ShowWindow(hEditUser, SW_HIDE);
    ShowWindow(hEditPass, SW_HIDE);
    ShowWindow(hEditName, SW_HIDE);
    ShowWindow(btnLoginDo, SW_HIDE);
    ShowWindow(btnBack, SW_HIDE);
    ShowWindow(lblUser, SW_HIDE);
    ShowWindow(lblPass, SW_HIDE);
    ShowWindow(lblName , SW_HIDE);
    ShowWindow(btnSigninDo, SW_HIDE);

    ShowWindow(btnDep, SW_HIDE);
    ShowWindow(btnWit, SW_HIDE);
    ShowWindow(btnTra, SW_HIDE);
    ShowWindow(btnLog, SW_HIDE);

    ShowWindow(hStaticBalance, SW_HIDE);
    ShowWindow(hStaticAccount, SW_HIDE);
}

void ShowLoginPage() {
    ShowWindow(btnLoginMenu, SW_HIDE);
    ShowWindow(btnSigninMenu, SW_HIDE);
    ShowWindow(btnExit, SW_HIDE);
    ShowWindow(lblName , SW_HIDE);

    ShowWindow(hEditUser, SW_SHOW);
    ShowWindow(hEditPass, SW_SHOW);
    ShowWindow(hEditName, SW_HIDE);
    ShowWindow(btnLoginDo, SW_SHOW);
    ShowWindow(btnBack, SW_SHOW);
    ShowWindow(lblUser, SW_SHOW);
    ShowWindow(lblPass, SW_SHOW);
    ShowWindow(btnSigninDo, SW_HIDE);

    ShowWindow(btnDep, SW_HIDE);
    ShowWindow(btnWit, SW_HIDE);
    ShowWindow(btnTra, SW_HIDE);
    ShowWindow(btnLog, SW_HIDE);

    ShowWindow(hStaticBalance, SW_HIDE);
    ShowWindow(hStaticAccount, SW_HIDE);
}

void ShowSigninPage(){
    ShowWindow(btnLoginMenu, SW_HIDE);
    ShowWindow(btnSigninMenu, SW_HIDE);
    ShowWindow(btnExit, SW_HIDE);

    ShowWindow(hEditUser, SW_SHOW);
    ShowWindow(hEditPass, SW_SHOW);
    ShowWindow(btnLoginDo, SW_HIDE);
    ShowWindow(btnSigninDo, SW_SHOW);
    ShowWindow(btnBack, SW_SHOW);
    ShowWindow(lblUser, SW_SHOW);
    ShowWindow(lblPass, SW_SHOW);
    ShowWindow(lblName , SW_SHOW);
    ShowWindow(hEditName, SW_SHOW);

    ShowWindow(btnDep, SW_HIDE);
    ShowWindow(btnWit, SW_HIDE);
    ShowWindow(btnTra, SW_HIDE);
    ShowWindow(btnLog, SW_HIDE);

    ShowWindow(hStaticBalance, SW_HIDE);
    ShowWindow(hStaticAccount, SW_HIDE);
}
void AccoutPage(){
    ShowWindow(btnLoginMenu, SW_HIDE);
    ShowWindow(btnSigninMenu, SW_HIDE);
    ShowWindow(btnExit, SW_HIDE);

    ShowWindow(hEditUser, SW_HIDE);
    ShowWindow(hEditPass, SW_HIDE);
    ShowWindow(hEditName, SW_HIDE);
    ShowWindow(btnLoginDo, SW_HIDE);
    ShowWindow(btnBack, SW_HIDE);
    ShowWindow(lblUser, SW_HIDE);
    ShowWindow(lblPass, SW_HIDE);
    ShowWindow(lblName , SW_HIDE);
    ShowWindow(btnSigninDo, SW_HIDE);

    ShowWindow(btnDep, SW_SHOW);
    ShowWindow(btnWit, SW_SHOW);
    ShowWindow(btnTra, SW_SHOW);
    ShowWindow(btnLog, SW_SHOW);

    ShowWindow(hStaticBalance, SW_SHOW);
    ShowWindow(hStaticAccount, SW_SHOW);
}
void Showdeposit(){
    ShowWindow(btnDep, SW_HIDE);
    ShowWindow(btnWit, SW_HIDE);
    ShowWindow(btnTra, SW_HIDE);
    ShowWindow(btnLog, SW_HIDE);

    ShowWindow(hStaticBalance, SW_SHOW);
    ShowWindow(hStaticAccount, SW_SHOW);
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        loadUsers();
        imgDeposit = new Image(L"D:\\year1\\1-2\\Compro\\project\\GUI\\dep2.png");
        hFont = CreateFont(20,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,
            DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,
            VARIABLE_PITCH,"Segoe UI");

        hTitleFont = CreateFont(40,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,
            DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,
            VARIABLE_PITCH,"Segoe UI");

        HWND hTitle = CreateWindow("Static","FAM SOD BANK",
            WS_VISIBLE|WS_CHILD|SS_CENTER,
            0,60,800,60,
            hwnd,NULL,NULL,NULL);

        SendMessage(hTitle, WM_SETFONT, (WPARAM)hTitleFont, TRUE);

        // ===== ปุ่มหน้าแรก =====
        btnLoginMenu = CreateWindow("Button","LOGIN",
            WS_VISIBLE|WS_CHILD,
            300,250,200,40,
            hwnd,(HMENU)ID_BTN_LOGIN_MENU,NULL,NULL);

        btnSigninMenu = CreateWindow("Button","SIGN IN",
            WS_VISIBLE|WS_CHILD,
            300,310,200,40,
            hwnd,(HMENU)ID_BTN_SIGNIN_MENU,NULL,NULL);

        btnExit = CreateWindow("Button","EXIT",
            WS_VISIBLE|WS_CHILD,
            300,370,200,40,
            hwnd,(HMENU)ID_BTN_EXIT,NULL,NULL);

        SendMessage(btnLoginMenu, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(btnSigninMenu, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(btnExit, WM_SETFONT, (WPARAM)hFont, TRUE);

        // ===== หน้า Login (ซ่อนไว้ก่อน) =====
        lblUser = CreateWindow("Static","Student-ID:",
            WS_CHILD,250,150,100,25,
            hwnd,NULL,NULL,NULL);

        hEditUser = CreateWindow("Edit","",
            WS_CHILD|WS_BORDER|ES_NUMBER,
            350,150,200,25,
            hwnd,NULL,NULL,NULL);
        SendMessage(hEditUser, EM_SETLIMITTEXT, 9, 0);


        lblPass = CreateWindow("Static","Password:",
            WS_CHILD,250,200,100,25,
            hwnd,NULL,NULL,NULL);

        hEditPass = CreateWindow("Edit","",
            WS_CHILD|WS_BORDER|ES_PASSWORD|ES_NUMBER,
            350,200,200,25, 
            hwnd,NULL,NULL,NULL);
        SendMessage(hEditPass, EM_SETLIMITTEXT, 8, 0);

        lblName = CreateWindow("Static","Name:",
            WS_CHILD,250,250,100,25,
            hwnd,NULL,NULL,NULL);

        hEditName = CreateWindow("Edit","",
            WS_CHILD|WS_BORDER,
            350,250,200,25,
            hwnd,NULL,NULL,NULL);

        btnLoginDo = CreateWindow("Button","LOGIN",
            WS_CHILD,
            300,320,200,40,
            hwnd,(HMENU)ID_BTN_LOGIN_DO,NULL,NULL);
        
        btnSigninDo = CreateWindow("Button","SIGN-IN",
            WS_CHILD,
            300,320,200,40,
            hwnd,(HMENU)ID_BTN_SIGN_IN_DO,NULL,NULL);

        btnBack = CreateWindow("Button","BACK",
            WS_CHILD,
            300,370,200,35,
            hwnd,(HMENU)ID_BTN_BACK,NULL,NULL);

        // btnDep = CreateWindow("Button", "DEPOSIT"
        //     , WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        //     100, 300, 180, 80, hwnd, (HMENU)ID_BTN_DEPOSITE, NULL, NULL);
        hBrushBg = CreateSolidBrush(RGB(0,100,0));
        btnDep = CreateWindow("BUTTON", "",
            WS_CHILD | BS_OWNERDRAW,
            100, 300, 180, 80,
            hwnd, (HMENU)ID_BTN_DEPOSITE,
            ((LPCREATESTRUCT)lp)->hInstance,NULL);

        btnWit = CreateWindow("Button", "WITHDRAW"
            , WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
            310, 300, 180, 80, hwnd, (HMENU)ID_BTN_WITHDRAW, NULL, NULL);

        btnTra = CreateWindow("Button", "TRANSFER"
            , WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
            520, 300, 180, 80, hwnd, (HMENU)ID_BTN_TRANSFER, NULL, NULL);

        btnLog = CreateWindow("Button", "EXIT SYSTEM"
            , WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
            325, 480, 150, 40, hwnd, (HMENU)ID_BTN_LOGOUT, NULL, NULL);

        hStaticAccount = CreateWindow("Static","", 
            WS_VISIBLE | WS_CHILD | SS_CENTER, 
            0, 120, 800, 30, hwnd, NULL, NULL, NULL);
        SendMessage(hStaticAccount, WM_SETFONT, (WPARAM)hFont, TRUE);

                // ยอดเงินคงเหลือ
        // sprintf(balText, "BALANCE : %.2f Baht.", userBalance);
        hStaticBalance = CreateWindow("Static", "", 
            WS_VISIBLE | WS_CHILD | SS_CENTER, 
            0, 150, 800, 60, hwnd, NULL, NULL, NULL);
        SendMessage(hStaticBalance, WM_SETFONT, (WPARAM)hTitleFont, TRUE);

        SendMessage(btnLoginDo, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(btnSigninDo, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(btnBack, WM_SETFONT, (WPARAM)hFont, TRUE);

        ShowMainMenu();
        break;
    }

    case WM_COMMAND:
    {
        switch (LOWORD(wp))
        {
        case ID_BTN_LOGIN_MENU:
            ShowLoginPage();
            break;

        case ID_BTN_BACK:
            ShowMainMenu();
            break;

        case ID_BTN_SIGNIN_MENU:
            ShowSigninPage();
            break;

        case ID_BTN_LOGIN_DO:
        {
            char user[100], pass[100];
            GetWindowText(hEditUser, user, 100);
            GetWindowText(hEditPass, pass, 100);

            if (checkLogin(user, pass)){
                currentUser = user;   // 🔥 เก็บชื่อที่ login สำเร็จ
                std::string welcome = "Account ID : " + currentUser;

                userBalance = getBalance(user);

                char balText[100];
                sprintf(balText, "BALANCE : %.2f THB .", userBalance);
                SetWindowText(hStaticBalance, balText);
                SetWindowText(hStaticAccount, welcome.c_str());
                AccoutPage(); 
            }
            break;
        }
        
        case ID_BTN_SIGN_IN_DO:
        {
            char user[100], pass[100], name[100];

            GetWindowText(hEditUser, user, 100);
            GetWindowText(hEditPass, pass, 100);
            GetWindowText(hEditName, name, 100); // ถ้ามีช่อง name

            if (registerUser(user, pass, name))
                MessageBox(hwnd, "Registration Success!",
                        "Success", MB_OK);
            else
                MessageBox(hwnd, "Username already exists!",
                        "Error", MB_OK);
            SetWindowText(hEditUser, "");
            SetWindowText(hEditPass, "");
            SetWindowText(hEditName, "");
            break;

        }
        // case ID_BTN_DEPOSITE:
            // Showdeposit();
            // break;
        
        case ID_BTN_EXIT:
        {
            PostQuitMessage(0);
            break;
        }
        // break;
        }
        break;
    }
    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wp;
        SetTextColor(hdcStatic, RGB(255,255,255));
        SetBkMode(hdcStatic, TRANSPARENT);
        return (INT_PTR)hBrushBg;
    }

    case WM_DRAWITEM:
    {
        LPDRAWITEMSTRUCT dis = (LPDRAWITEMSTRUCT)lp;
        if (dis->CtlID == ID_BTN_DEPOSITE)
        {
            FillRect(dis->hDC, &dis->rcItem, hBrushBg);

            Graphics graphics(dis->hDC);
            graphics.DrawImage(imgDeposit,
            static_cast<INT>(dis->rcItem.left),
            static_cast<INT>(dis->rcItem.top),
            static_cast<INT>(dis->rcItem.right - dis->rcItem.left),
            static_cast<INT>(dis->rcItem.bottom - dis->rcItem.top));

            return TRUE;
        }
    }
    break;

    case WM_DESTROY:
        delete imgDeposit;
        GdiplusShutdown(gdiplusToken);
        DeleteObject(hBrushBg);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd,msg,wp,lp);
    }
    return 0 ;
}

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int)
{
    WNDCLASS wc = {0};
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = "BankClass";
    wc.lpfnWndProc = WindowProcedure;

    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    hBrushBg = CreateSolidBrush(RGB(0,100,0));
    wc.hbrBackground = hBrushBg;
    
    RegisterClass(&wc);

    CreateWindow("BankClass","FAM SOD BANK",
        WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|
        WS_MINIMIZEBOX|WS_VISIBLE,
        200,100,800,500,
        NULL,NULL,hInst,NULL);

    MSG msg;
    while(GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}