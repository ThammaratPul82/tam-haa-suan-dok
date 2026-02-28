#include <windows.h>
#include <string>
#include "login.h"
#include "sign-in.h"
#include "user_system.h"

#define ID_BTN_LOGIN_MENU   1
#define ID_BTN_SIGNIN_MENU  2
#define ID_BTN_EXIT         3
#define ID_BTN_LOGIN_DO     4
#define ID_BTN_BACK         5
#define ID_BTN_SIGN_IN_DO   6
#define ID_BTN_DEPOSITE     7
#define ID_BTN_WITHDRAW 
#define ID_BTN_TRANSFER 
#define ID_BTN_LOGOUT

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
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        loadUsers();
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
        {
            ShowSigninPage();
            break;
        }

        case ID_BTN_LOGIN_DO:
        {
            char user[100], pass[100];
            GetWindowText(hEditUser, user, 100);
            GetWindowText(hEditPass, pass, 100);

            if (checkLogin(user, pass))
                MessageBox(hwnd,"Login Success!","Success",MB_OK);
            // else
            //     MessageBox(hwnd,"Login Failed!","Error",MB_OK);
            SetWindowText(hEditUser, "");
            SetWindowText(hEditPass, "");
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
        
        case ID_BTN_EXIT:
        {
            PostQuitMessage(0);
            break;
        }
        break;
        }
    }
    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wp;
        SetTextColor(hdcStatic, RGB(255,255,255));
        SetBkMode(hdcStatic, TRANSPARENT);
        return (INT_PTR)CreateSolidBrush(RGB(0,100,0));
    }

    case WM_DESTROY:
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
    wc.hbrBackground = CreateSolidBrush(RGB(0,100,0));
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = "BankClass";
    wc.lpfnWndProc = WindowProcedure;

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