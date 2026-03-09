#include <windows.h>
#include <string>
#include "include/login.h"
#include "include/sign-in.h"
#include "include/user_system.h"
#include "include/deposit.h"
#include "include/withdraw.h"
#include "include/transfer.h"
#include "include/statement.h"
#include "include/runCreate_img.h"

// test
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;

#define ID_BTN_LOGIN_MENU 1
#define ID_BTN_SIGNIN_MENU 2
#define ID_BTN_EXIT 3
#define ID_BTN_LOGIN_DO 4
#define ID_BTN_BACK 5
#define ID_BTN_SIGN_IN_DO 6
#define ID_BTN_DEPOSITE 7
#define ID_BTN_DEPOSITE_DO 8
#define ID_BTN_WITHDRAW 9
#define ID_BTN_WITHDRAW_DO 10
#define ID_BTN_TRANSFER 11
#define ID_BTN_TRANSFER_DO 12
#define ID_BTN_LOGOUT 13
#define ID_BTN_HOME 14
#define ID_BTN_STATEMENT 15
#define ID_LIST_HISTORY 16

WNDPROC oldAmountProc;
// ====== Prototype ======
LRESULT CALLBACK AmountProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// ====== WindowProcedure ======
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

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

// home_bank
HWND btnDep;
HWND btnWit;
HWND btnTra;
HWND btnLog;

// AccBalan
HWND hStaticBalance, hStaticAccount;
HWND lblAmount, hEditAmount;
HWND btnDep_do;
HWND lblAcPass, hEditPass_Ac;

HWND btnWith_do;

HWND lblto_user, lblAmount_tran, lblPass_tran;
HWND hEditTo_user, hEditAmount_tran, hEditPass_tran;

HWND btnTran_do;

HWND btnHome, btnLogout, btnstate;
HWND hListHistory;

HWND hHeaderDate, hHeaderTime, hHeaderAction, hHeaderAmount;

// HBRUSH hEditBg;
HPEN hEditBorder;
HPEN hEditBorderFocus;

HWND focusedEdit = NULL;

HBRUSH hEditBg = CreateSolidBrush(RGB(0, 120, 0)); // สีเขียว

HINSTANCE g_hInstance;


double userBalance; // ยอดเงินเริ่มต้น
std::string currentUser = "";
char balText[100];

HBRUSH hBrushBg;
ULONG_PTR gdiplusToken;

Image *imgLogin = nullptr;
Image *imgSignin = nullptr;
Image *imgExit = nullptr;
Image *imgDeposit = nullptr;
Image *imgWithdraw = nullptr;
Image *imgTransfer = nullptr;
Image *imgHome = nullptr;
Image *imgLogout = nullptr;
Image *imgDep = nullptr;
Image *imgStatement = nullptr;

Image *imgLogin_do = nullptr;
Image *imgSignin_do = nullptr;

bool loginPressed = false;

void ShowMainMenu(HWND hwnd)
{
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
    ShowWindow(lblName, SW_HIDE);
    ShowWindow(btnSigninDo, SW_HIDE);

    ShowWindow(btnDep, SW_HIDE);
    ShowWindow(btnWit, SW_HIDE);
    ShowWindow(btnTra, SW_HIDE);
    ShowWindow(btnLog, SW_HIDE);

    ShowWindow(hStaticBalance, SW_HIDE);
    ShowWindow(hStaticAccount, SW_HIDE);

    ShowWindow(hEditAmount, SW_HIDE);
    ShowWindow(lblAmount, SW_HIDE);
    ShowWindow(lblAcPass, SW_HIDE);
    ShowWindow(hEditPass_Ac, SW_HIDE);
    ShowWindow(btnDep_do, SW_HIDE);
    ShowWindow(btnWith_do, SW_HIDE);

    ShowWindow(lblto_user, SW_HIDE);
    ShowWindow(lblAmount_tran, SW_HIDE);
    ShowWindow(lblPass_tran, SW_HIDE);
    ShowWindow(hEditAmount_tran, SW_HIDE);
    ShowWindow(hEditPass_tran, SW_HIDE);
    ShowWindow(hEditTo_user, SW_HIDE);
    ShowWindow(btnTran_do, SW_HIDE);

    ShowWindow(btnHome, SW_HIDE);
    ShowWindow(btnLogout, SW_HIDE);
    ShowWindow(btnstate, SW_HIDE);
    ShowWindow(hListHistory, SW_HIDE);

    ShowWindow(hHeaderDate, SW_HIDE);
    ShowWindow(hHeaderTime, SW_HIDE);
    ShowWindow(hHeaderAction, SW_HIDE);
    ShowWindow(hHeaderAmount, SW_HIDE);

    InvalidateRect(hwnd, NULL, TRUE); // refresh หน้าจอ
}

void ShowLoginPage(HWND hwnd)
{
    ShowWindow(btnLoginMenu, SW_HIDE);
    ShowWindow(btnSigninMenu, SW_HIDE);
    ShowWindow(btnExit, SW_HIDE);
    ShowWindow(lblName, SW_HIDE);

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

    ShowWindow(hEditAmount, SW_HIDE);
    ShowWindow(lblAmount, SW_HIDE);
    ShowWindow(lblAcPass, SW_HIDE);
    ShowWindow(hEditPass_Ac, SW_HIDE);
    ShowWindow(btnDep_do, SW_HIDE);
    ShowWindow(btnWith_do, SW_HIDE);

    ShowWindow(lblto_user, SW_HIDE);
    ShowWindow(lblAmount_tran, SW_HIDE);
    ShowWindow(lblPass_tran, SW_HIDE);
    ShowWindow(hEditAmount_tran, SW_HIDE);
    ShowWindow(hEditPass_tran, SW_HIDE);
    ShowWindow(hEditTo_user, SW_HIDE);
    ShowWindow(btnTran_do, SW_HIDE);

    ShowWindow(btnHome, SW_HIDE);
    ShowWindow(btnLogout, SW_HIDE);
    ShowWindow(btnstate, SW_HIDE);
    ShowWindow(hListHistory, SW_HIDE);

    ShowWindow(hHeaderDate, SW_HIDE);
    ShowWindow(hHeaderTime, SW_HIDE);
    ShowWindow(hHeaderAction, SW_HIDE);
    ShowWindow(hHeaderAmount, SW_HIDE);

    InvalidateRect(hwnd, NULL, TRUE); // refresh หน้าจอ

}

void ShowSigninPage(HWND hwnd)
{
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
    ShowWindow(lblName, SW_SHOW);
    ShowWindow(hEditName, SW_SHOW);

    ShowWindow(btnDep, SW_HIDE);
    ShowWindow(btnWit, SW_HIDE);
    ShowWindow(btnTra, SW_HIDE);
    ShowWindow(btnLog, SW_HIDE);

    ShowWindow(hStaticBalance, SW_HIDE);
    ShowWindow(hStaticAccount, SW_HIDE);

    ShowWindow(hEditAmount, SW_HIDE);
    ShowWindow(lblAmount, SW_HIDE);
    ShowWindow(lblAcPass, SW_HIDE);
    ShowWindow(hEditPass_Ac, SW_HIDE);
    ShowWindow(btnDep_do, SW_HIDE);
    ShowWindow(btnWith_do, SW_HIDE);

    ShowWindow(lblto_user, SW_HIDE);
    ShowWindow(lblAmount_tran, SW_HIDE);
    ShowWindow(lblPass_tran, SW_HIDE);
    ShowWindow(hEditAmount_tran, SW_HIDE);
    ShowWindow(hEditPass_tran, SW_HIDE);
    ShowWindow(hEditTo_user, SW_HIDE);
    ShowWindow(btnTran_do, SW_HIDE);

    ShowWindow(btnHome, SW_HIDE);
    ShowWindow(btnLogout, SW_HIDE);
    ShowWindow(btnstate, SW_HIDE);
    ShowWindow(hListHistory, SW_HIDE);

    ShowWindow(hHeaderDate, SW_HIDE);
    ShowWindow(hHeaderTime, SW_HIDE);
    ShowWindow(hHeaderAction, SW_HIDE);
    ShowWindow(hHeaderAmount, SW_HIDE);

    InvalidateRect(hwnd, NULL, TRUE); // refresh หน้าจอ

}
void AccoutPage(HWND hwnd)
{
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
    ShowWindow(lblName, SW_HIDE);
    ShowWindow(btnSigninDo, SW_HIDE);

    ShowWindow(btnDep, SW_SHOW);
    ShowWindow(btnWit, SW_SHOW);
    ShowWindow(btnTra, SW_SHOW);
    ShowWindow(btnLog, SW_SHOW);

    ShowWindow(hStaticBalance, SW_SHOW);
    ShowWindow(hStaticAccount, SW_SHOW);

    ShowWindow(hEditAmount, SW_HIDE);
    ShowWindow(lblAmount, SW_HIDE);
    ShowWindow(lblAcPass, SW_HIDE);
    ShowWindow(hEditPass_Ac, SW_HIDE);
    ShowWindow(btnDep_do, SW_HIDE);
    ShowWindow(btnWith_do, SW_HIDE);

    ShowWindow(lblto_user, SW_HIDE);
    ShowWindow(lblAmount_tran, SW_HIDE);
    ShowWindow(lblPass_tran, SW_HIDE);
    ShowWindow(hEditAmount_tran, SW_HIDE);
    ShowWindow(hEditPass_tran, SW_HIDE);
    ShowWindow(hEditTo_user, SW_HIDE);
    ShowWindow(btnTran_do, SW_HIDE);

    ShowWindow(btnHome, SW_HIDE);
    ShowWindow(btnLogout, SW_SHOW);
    ShowWindow(btnstate, SW_SHOW);
    ShowWindow(hListHistory, SW_HIDE);

    ShowWindow(hHeaderDate, SW_HIDE);
    ShowWindow(hHeaderTime, SW_HIDE);
    ShowWindow(hHeaderAction, SW_HIDE);
    ShowWindow(hHeaderAmount, SW_HIDE);

    InvalidateRect(hwnd, NULL, TRUE); // refresh หน้าจอ
}
void Showdeposit(HWND hwnd)
{
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
    ShowWindow(lblName, SW_HIDE);
    ShowWindow(btnSigninDo, SW_HIDE);

    ShowWindow(btnDep, SW_HIDE);
    ShowWindow(btnWit, SW_HIDE);
    ShowWindow(btnTra, SW_HIDE);
    ShowWindow(btnLog, SW_HIDE);

    ShowWindow(hStaticBalance, SW_SHOW);
    ShowWindow(hStaticAccount, SW_SHOW);

    ShowWindow(hEditAmount, SW_SHOW);
    ShowWindow(lblAmount, SW_SHOW);
    ShowWindow(lblAcPass, SW_SHOW);
    ShowWindow(hEditPass_Ac, SW_SHOW);
    ShowWindow(btnDep_do, SW_SHOW);
    ShowWindow(btnWith_do, SW_HIDE);

    ShowWindow(lblto_user, SW_HIDE);
    ShowWindow(lblAmount_tran, SW_HIDE);
    ShowWindow(lblPass_tran, SW_HIDE);
    ShowWindow(hEditAmount_tran, SW_HIDE);
    ShowWindow(hEditPass_tran, SW_HIDE);
    ShowWindow(hEditTo_user, SW_HIDE);
    ShowWindow(btnTran_do, SW_HIDE);

    ShowWindow(btnHome, SW_SHOW);
    ShowWindow(btnLogout, SW_HIDE);
    ShowWindow(btnstate, SW_HIDE);
    ShowWindow(hListHistory, SW_HIDE);

    ShowWindow(hHeaderDate, SW_HIDE);
    ShowWindow(hHeaderTime, SW_HIDE);
    ShowWindow(hHeaderAction, SW_HIDE);
    ShowWindow(hHeaderAmount, SW_HIDE);

    InvalidateRect(hwnd, NULL, TRUE); // refresh หน้าจอ

}

void ShowWithdrawPage(HWND hwnd)
{
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
    ShowWindow(lblName, SW_HIDE);
    ShowWindow(btnSigninDo, SW_HIDE);

    ShowWindow(btnDep, SW_HIDE);
    ShowWindow(btnWit, SW_HIDE);
    ShowWindow(btnTra, SW_HIDE);
    ShowWindow(btnLog, SW_HIDE);

    ShowWindow(hStaticBalance, SW_SHOW);
    ShowWindow(hStaticAccount, SW_SHOW);

    ShowWindow(hEditAmount, SW_SHOW);
    ShowWindow(lblAmount, SW_SHOW);
    ShowWindow(lblAcPass, SW_SHOW);
    ShowWindow(hEditPass_Ac, SW_SHOW);
    ShowWindow(btnDep_do, SW_HIDE);
    ShowWindow(btnWith_do, SW_SHOW);

    ShowWindow(lblto_user, SW_HIDE);
    ShowWindow(lblAmount_tran, SW_HIDE);
    ShowWindow(lblPass_tran, SW_HIDE);
    ShowWindow(hEditAmount_tran, SW_HIDE);
    ShowWindow(hEditPass_tran, SW_HIDE);
    ShowWindow(hEditTo_user, SW_HIDE);
    ShowWindow(btnTran_do, SW_HIDE);

    ShowWindow(btnHome, SW_SHOW);
    ShowWindow(btnLogout, SW_HIDE);
    ShowWindow(btnstate, SW_HIDE);
    ShowWindow(hListHistory, SW_HIDE);

    ShowWindow(hHeaderDate, SW_HIDE);
    ShowWindow(hHeaderTime, SW_HIDE);
    ShowWindow(hHeaderAction, SW_HIDE);
    ShowWindow(hHeaderAmount, SW_HIDE);

    InvalidateRect(hwnd, NULL, TRUE); // refresh หน้าจอ

}

void ShowTransferPage(HWND hwnd)
{
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
    ShowWindow(lblName, SW_HIDE);
    ShowWindow(btnSigninDo, SW_HIDE);

    ShowWindow(btnDep, SW_HIDE);
    ShowWindow(btnWit, SW_HIDE);
    ShowWindow(btnTra, SW_HIDE);
    ShowWindow(btnLog, SW_HIDE);

    ShowWindow(hStaticBalance, SW_SHOW);
    ShowWindow(hStaticAccount, SW_SHOW);

    ShowWindow(hEditAmount, SW_HIDE);
    ShowWindow(lblAmount, SW_HIDE);
    ShowWindow(lblAcPass, SW_HIDE);
    ShowWindow(hEditPass_Ac, SW_HIDE);
    ShowWindow(btnDep_do, SW_HIDE);
    ShowWindow(btnWith_do, SW_HIDE);

    ShowWindow(lblto_user, SW_SHOW);
    ShowWindow(lblAmount_tran, SW_SHOW);
    ShowWindow(lblPass_tran, SW_SHOW);
    ShowWindow(hEditAmount_tran, SW_SHOW);
    ShowWindow(hEditPass_tran, SW_SHOW);
    ShowWindow(hEditTo_user, SW_SHOW);
    ShowWindow(btnTran_do, SW_SHOW);

    ShowWindow(btnHome, SW_SHOW);
    ShowWindow(btnLogout, SW_HIDE);
    ShowWindow(btnstate, SW_HIDE);
    ShowWindow(hListHistory, SW_HIDE);

    ShowWindow(hHeaderDate, SW_HIDE);
    ShowWindow(hHeaderTime, SW_HIDE);
    ShowWindow(hHeaderAction, SW_HIDE);
    ShowWindow(hHeaderAmount, SW_HIDE);

    InvalidateRect(hwnd, NULL, TRUE); // refresh หน้าจอ

}

void ShowStatementPage(HWND hwnd)
{
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
    ShowWindow(lblName, SW_HIDE);
    ShowWindow(btnSigninDo, SW_HIDE);

    ShowWindow(btnDep, SW_HIDE);
    ShowWindow(btnWit, SW_HIDE);
    ShowWindow(btnTra, SW_HIDE);
    ShowWindow(btnLog, SW_HIDE);

    ShowWindow(hStaticBalance, SW_HIDE);
    ShowWindow(hStaticAccount, SW_SHOW);

    ShowWindow(hEditAmount, SW_HIDE);
    ShowWindow(lblAmount, SW_HIDE);
    ShowWindow(lblAcPass, SW_HIDE);
    ShowWindow(hEditPass_Ac, SW_HIDE);
    ShowWindow(btnDep_do, SW_HIDE);
    ShowWindow(btnWith_do, SW_HIDE);

    ShowWindow(lblto_user, SW_HIDE);
    ShowWindow(lblAmount_tran, SW_HIDE);
    ShowWindow(lblPass_tran, SW_HIDE);
    ShowWindow(hEditAmount_tran, SW_HIDE);
    ShowWindow(hEditPass_tran, SW_HIDE);
    ShowWindow(hEditTo_user, SW_HIDE);
    ShowWindow(btnTran_do, SW_HIDE);

    ShowWindow(btnHome, SW_SHOW);
    ShowWindow(btnLogout, SW_SHOW);
    ShowWindow(btnstate, SW_HIDE);
    ShowWindow(hListHistory, SW_SHOW);

    ShowWindow(hHeaderDate, SW_SHOW);
    ShowWindow(hHeaderTime, SW_SHOW);
    ShowWindow(hHeaderAction, SW_SHOW);
    ShowWindow(hHeaderAmount, SW_SHOW);

    InvalidateRect(hwnd, NULL, TRUE); // refresh หน้าจอ

}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        loadUsers();
        hEditBg = CreateSolidBrush(RGB(255, 255, 255));
        hEditBorder = CreatePen(PS_SOLID, 2, RGB(0, 150, 0));      // ขอบปกติ
        hEditBorderFocus = CreatePen(PS_SOLID, 2, RGB(0, 200, 0)); // ตอน focus

        imgLogin = new Image(L"D:\\year1\\1-2\\Compro\\project\\TAM-HAA-SUAN-DOK\\Main\\button_img\\1.png");
        imgSignin = new Image(L"D:\\year1\\1-2\\Compro\\project\\TAM-HAA-SUAN-DOK\\Main\\button_img\\2.png");
        imgExit = new Image(L"D:\\year1\\1-2\\Compro\\project\\TAM-HAA-SUAN-DOK\\Main\\button_img\\3.png");
        imgDeposit = new Image(L"D:\\year1\\1-2\\Compro\\project\\TAM-HAA-SUAN-DOK\\Main\\button_img\\11.png");
        imgWithdraw = new Image(L"D:\\year1\\1-2\\Compro\\project\\TAM-HAA-SUAN-DOK\\Main\\button_img\\12.png");
        imgTransfer = new Image(L"D:\\year1\\1-2\\Compro\\project\\TAM-HAA-SUAN-DOK\\Main\\button_img\\13.png");
        imgHome = new Image(L"D:\\year1\\1-2\\Compro\\project\\TAM-HAA-SUAN-DOK\\Main\\button_img\\4.png");
        imgDep = new Image(L"D:\\year1\\1-2\\Compro\\project\\TAM-HAA-SUAN-DOK\\Main\\button_img\\17.png");
        imgLogout = new Image(L"D:\\year1\\1-2\\Compro\\project\\TAM-HAA-SUAN-DOK\\Main\\button_img\\7.png");
        imgStatement = new Image(L"D:\\year1\\1-2\\Compro\\project\\TAM-HAA-SUAN-DOK\\Main\\button_img\\16.png");
        imgLogin_do = new Image(L"D:\\year1\\1-2\\Compro\\project\\TAM-HAA-SUAN-DOK\\Main\\button_img\\18.png");
        imgSignin_do = new Image(L"D:\\year1\\1-2\\Compro\\project\\TAM-HAA-SUAN-DOK\\Main\\button_img\\19.png");

        hFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                           DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                           CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                           VARIABLE_PITCH, "Segoe UI");

        hTitleFont = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                                CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                                VARIABLE_PITCH, "Segoe UI");

        HWND hTitle = CreateWindow("Static", "FAM SOD BANK",
                                   WS_VISIBLE | WS_CHILD | SS_CENTER,
                                   0, 60, 800, 60,
                                   hwnd, NULL, NULL, NULL);

        SendMessage(hTitle, WM_SETFONT, (WPARAM)hTitleFont, TRUE);

        hHeaderDate = CreateWindow("Static", "Date", WS_CHILD | SS_LEFT, 
                                   80, 175, 100, 20, hwnd, NULL, NULL, NULL);
        hHeaderTime = CreateWindow("Static", "Time", WS_CHILD | SS_LEFT, 
                                   192, 175, 100, 20, hwnd, NULL, NULL, NULL);
        hHeaderAction = CreateWindow("Static", "Action", WS_CHILD | SS_LEFT, 
                                     305, 175, 150, 20, hwnd, NULL, NULL, NULL);
        hHeaderAmount = CreateWindow("Static", "Amount", WS_CHILD | SS_LEFT, 
                                     550, 175, 150, 20, hwnd, NULL, NULL, NULL);

        // เซ็ตฟอนต์ให้ตรงกับส่วนอื่นๆ
        SendMessage(hHeaderDate, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hHeaderTime, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hHeaderAction, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hHeaderAmount, WM_SETFONT, (WPARAM)hFont, TRUE);

        // ===== ปุ่มหน้าแรก =====
        // btnLoginMenu = CreateWindow("Button","LOGIN",
        //     WS_VISIBLE|WS_CHILD,
        //     300,250,200,40,
        //     hwnd,(HMENU)ID_BTN_LOGIN_MENU,NULL,NULL);

        btnLoginMenu = CreateWindow("Button", "",
                                    WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                                    300, 250, 200, 40,
                                    hwnd, (HMENU)ID_BTN_LOGIN_MENU, ((LPCREATESTRUCT)lp)->hInstance, NULL);

        btnSigninMenu = CreateWindow("Button", "",
                                     WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
                                     300, 310, 200, 40,
                                     hwnd, (HMENU)ID_BTN_SIGNIN_MENU, ((LPCREATESTRUCT)lp)->hInstance, NULL);

        btnExit = CreateWindow("Button", "",
                               WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
                               300, 370, 200, 40,
                               hwnd, (HMENU)ID_BTN_EXIT, ((LPCREATESTRUCT)lp)->hInstance, NULL);

        // SendMessage(btnLoginMenu, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(btnLoginMenu, BM_SETSTYLE, BS_OWNERDRAW, TRUE);
        SendMessage(btnSigninMenu, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(btnExit, WM_SETFONT, (WPARAM)hFont, TRUE);

        // ===== หน้า Login (ซ่อนไว้ก่อน) =====
        lblUser = CreateWindow("Static", "Student-ID :",
                               WS_CHILD, 250, 150, 100, 25,
                               hwnd, NULL, NULL, NULL);

        hEditUser = CreateWindow("Edit", "",
                                 WS_CHILD | ES_NUMBER | ES_AUTOHSCROLL,
                                 370, 150, 200, 22,
                                 hwnd, NULL, NULL, NULL);
        SendMessage(hEditUser, EM_SETLIMITTEXT, 9, 0);

        lblPass = CreateWindow("Static", "Password :",
                               WS_CHILD, 250, 200, 100, 25,
                               hwnd, NULL, NULL, NULL);

        hEditPass = CreateWindow("Edit", "",
                                 WS_CHILD | ES_PASSWORD | ES_NUMBER,
                                 370, 200, 200, 25,
                                 hwnd, NULL, NULL, NULL);
        SendMessage(hEditPass, EM_SETLIMITTEXT, 8, 0);

        lblName = CreateWindow("Static", "Name:",
                               WS_CHILD, 250, 250, 100, 25,
                               hwnd, NULL, NULL, NULL);

        hEditName = CreateWindow("Edit", "",
                                 WS_CHILD ,
                                 370, 250, 200, 25,
                                 hwnd, NULL, NULL, NULL);

        btnLoginDo = CreateWindow("Button", "LOGIN",
                                  WS_CHILD | BS_OWNERDRAW,
                                  320, 320, 150, 50,
                                  hwnd, (HMENU)ID_BTN_LOGIN_DO, ((LPCREATESTRUCT)lp)->hInstance, NULL);

        btnSigninDo = CreateWindow("Button", "SIGN-IN",
                                   WS_CHILD | BS_OWNERDRAW,
                                   320, 320, 150, 50,
                                   hwnd, (HMENU)ID_BTN_SIGN_IN_DO, ((LPCREATESTRUCT)lp)->hInstance, NULL);

        btnBack = CreateWindow("Button", "BACK",
                               WS_CHILD | BS_OWNERDRAW,
                               15, 15, 180, 80,
                               hwnd, (HMENU)ID_BTN_BACK, ((LPCREATESTRUCT)lp)->hInstance, NULL);

        // btnDep = CreateWindow("Button", "DEPOSIT"
        //     , WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        //     100, 300, 180, 80, hwnd, (HMENU)ID_BTN_DEPOSITE, NULL, NULL);
        hBrushBg = CreateSolidBrush(RGB(1, 50, 32));
        btnDep = CreateWindow("BUTTON", "",
                              WS_CHILD | BS_OWNERDRAW,
                              100, 300, 180, 80,
                              hwnd, (HMENU)ID_BTN_DEPOSITE,
                              ((LPCREATESTRUCT)lp)->hInstance, NULL);

        btnWit = CreateWindow("Button", "",
                              WS_CHILD | BS_OWNERDRAW,
                              310, 300, 180, 80,
                              hwnd, (HMENU)ID_BTN_WITHDRAW,
                              ((LPCREATESTRUCT)lp)->hInstance, NULL);

        btnTra = CreateWindow("Button", "",
                              WS_CHILD | BS_OWNERDRAW,
                              520, 300, 180, 80,
                              hwnd, (HMENU)ID_BTN_TRANSFER,
                              ((LPCREATESTRUCT)lp)->hInstance, NULL);

        btnHome = CreateWindow("Button", "",
                               WS_CHILD | BS_OWNERDRAW,
                               15, 15, 180, 80,
                               hwnd, (HMENU)ID_BTN_HOME,
                               ((LPCREATESTRUCT)lp)->hInstance, NULL);

        btnLogout = CreateWindow("Button", "",
                                 WS_CHILD | BS_OWNERDRAW,
                                 600, 10, 180, 80,
                                 hwnd, (HMENU)ID_BTN_LOGOUT,
                                 ((LPCREATESTRUCT)lp)->hInstance, NULL);

        btnLog = CreateWindow("Button", "EXIT SYSTEM", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                              325, 480, 150, 40, hwnd, (HMENU)ID_BTN_LOGOUT, NULL, NULL);

        btnstate = CreateWindow("Button", "",
                                WS_CHILD | BS_OWNERDRAW,
                                10, 10, 180, 80,
                                hwnd, (HMENU)ID_BTN_STATEMENT,
                                ((LPCREATESTRUCT)lp)->hInstance, NULL);

        hStaticAccount = CreateWindow("Static", "",
                                      WS_VISIBLE | WS_CHILD | SS_CENTER,
                                      0, 120, 800, 30, hwnd, NULL, NULL, NULL);
        SendMessage(hStaticAccount, WM_SETFONT, (WPARAM)hFont, TRUE);

        // ยอดเงินคงเหลือ
        // sprintf(balText, "BALANCE : %.2f Baht.", userBalance);
        hStaticBalance = CreateWindow("Static", "",
                                      WS_VISIBLE | WS_CHILD | SS_CENTER,
                                      0, 150, 800, 60, hwnd, NULL, NULL, NULL);
        SendMessage(hStaticBalance, WM_SETFONT, (WPARAM)hTitleFont, TRUE);

        lblAmount = CreateWindow("Static", "Amount :",
                                 WS_CHILD, 250, 220, 100, 25,
                                 hwnd, NULL, NULL, NULL);

        hEditAmount = CreateWindow("Edit", "",
                                   WS_CHILD | ES_AUTOHSCROLL,
                                   370, 220, 180, 22,
                                   hwnd, NULL, NULL, NULL);
        SendMessage(hEditAmount, EM_SETLIMITTEXT, 7, 0);

        oldAmountProc = (WNDPROC)SetWindowLongPtr(
            hEditAmount,
            GWLP_WNDPROC,
            (LONG_PTR)AmountProc);

        lblAcPass = CreateWindow("Static", "Password :",
                                 WS_CHILD, 250, 270, 100, 25,
                                 hwnd, NULL, NULL, NULL);

        hEditPass_Ac = CreateWindow("Edit", "",
                                    WS_CHILD | ES_PASSWORD | ES_NUMBER,
                                    370, 270, 180, 25,
                                    hwnd, NULL, NULL, NULL);
        SendMessage(hEditPass_Ac, EM_SETLIMITTEXT, 8, 0);

        btnDep_do = CreateWindow("Button", "",
                                 WS_CHILD | SS_CENTER | BS_OWNERDRAW,
                                 320, 350, 150, 50,
                                 hwnd, (HMENU)ID_BTN_DEPOSITE_DO,
                                 ((LPCREATESTRUCT)lp)->hInstance, NULL);

        btnWith_do = CreateWindow("Button", "",
                                  WS_CHILD | SS_CENTER | BS_OWNERDRAW,
                                  320, 350, 150, 50,
                                  hwnd, (HMENU)ID_BTN_WITHDRAW_DO, ((LPCREATESTRUCT)lp)->hInstance, NULL);

        btnTran_do = CreateWindow("Button", "",
                                  WS_CHILD | SS_CENTER | BS_OWNERDRAW,
                                  320, 370, 150, 50,
                                  hwnd, (HMENU)ID_BTN_TRANSFER_DO, ((LPCREATESTRUCT)lp)->hInstance, NULL);

        lblto_user = CreateWindow("Static", "To :",
                                  WS_CHILD, 250, 220, 100, 25,
                                  hwnd, NULL, NULL, NULL);

        hEditTo_user = CreateWindow("Edit", "",
                                    WS_CHILD | ES_NUMBER | ES_AUTOHSCROLL,
                                    370, 220, 180, 22,
                                    hwnd, NULL, NULL, NULL);
        SendMessage(hEditTo_user, EM_SETLIMITTEXT, 9, 0);

        lblAmount_tran = CreateWindow("Static", "Amount :",
                                      WS_CHILD, 250, 270, 100, 25,
                                      hwnd, NULL, NULL, NULL);

        hEditAmount_tran = CreateWindow("Edit", "",
                                        WS_CHILD | ES_AUTOHSCROLL,
                                        370, 270, 180, 25,
                                        hwnd, NULL, NULL, NULL);
        SendMessage(hEditAmount_tran, EM_SETLIMITTEXT, 7, 0);

        SetWindowLongPtr(
            hEditAmount_tran,
            GWLP_WNDPROC,
            (LONG_PTR)AmountProc);

        lblPass_tran = CreateWindow("Static", "Password :",
                                    WS_CHILD, 250, 320, 100, 25,
                                    hwnd, NULL, NULL, NULL);

        hEditPass_tran = CreateWindow("Edit", "",
                                      WS_CHILD | ES_PASSWORD | ES_NUMBER,
                                      370, 320, 180, 25,
                                      hwnd, NULL, NULL, NULL);
        SendMessage(hEditPass_tran, EM_SETLIMITTEXT, 8, 0);

        hListHistory = CreateWindow(
            "LISTBOX",
            "",
            WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | WS_VSCROLL | LBS_USETABSTOPS,
            60, 200, 680, 200, // ขยายความกว้างนิดหน่อยให้พอดีกับข้อมูล
            hwnd,
            (HMENU)ID_LIST_HISTORY,
            GetModuleHandle(NULL),
            NULL);

        // ตั้งค่าระยะ Tab แต่ละคอลัมน์ (หน่วยเป็น Dialog Template Units)
        int tabStops[] = { 65, 120, 250 }; // กะระยะให้พอดี Date -> Time -> Action -> Amount
        SendMessage(hListHistory, LB_SETTABSTOPS, (WPARAM)3, (LPARAM)tabStops);

        // บังคับให้ ListBox ใช้ฟอนต์ hFont ตัวเดียวกับปุ่มอื่นๆ
        SendMessage(hListHistory, WM_SETFONT, (WPARAM)hFont, TRUE);

        SendMessage(btnLoginDo, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(btnSigninDo, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(btnDep_do, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(btnWith_do, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(btnTran_do, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(btnBack, WM_SETFONT, (WPARAM)hFont, TRUE);

        ShowMainMenu(hwnd);
        break;
    }

    case WM_COMMAND:
    {
        if (HIWORD(wp) == EN_SETFOCUS)
        {
            if ((HWND)lp == hEditUser)
            {
                focusedEdit = (HWND)lp;
                InvalidateRect(hwnd, NULL, TRUE);
            }
            if ((HWND)lp == hEditPass)
            {
                focusedEdit = (HWND)lp;
                InvalidateRect(hwnd, NULL, TRUE);
            }
            if ((HWND)lp == hEditAmount)
            {
                focusedEdit = (HWND)lp;
                InvalidateRect(hwnd, NULL, TRUE);
            }
            if ((HWND)lp == hEditAmount_tran)
            {
                focusedEdit = (HWND)lp;
                InvalidateRect(hwnd, NULL, TRUE);
            }
            if ((HWND)lp == hEditPass_Ac)
            {
                focusedEdit = (HWND)lp;
                InvalidateRect(hwnd, NULL, TRUE);
            }
            if ((HWND)lp == hEditPass_tran)
            {
                focusedEdit = (HWND)lp;
                InvalidateRect(hwnd, NULL, TRUE);
            }
            if ((HWND)lp == hEditName)
            {
                focusedEdit = (HWND)lp;
                InvalidateRect(hwnd, NULL, TRUE);
            }
            if ((HWND)lp == hEditTo_user)
            {
                focusedEdit = (HWND)lp;
                InvalidateRect(hwnd, NULL, TRUE);
            }
        }

        if (HIWORD(wp) == EN_KILLFOCUS)
        {
            focusedEdit = NULL;
            InvalidateRect(hwnd, NULL, TRUE);
        }

        switch (LOWORD(wp))
        {
        case ID_BTN_LOGIN_MENU:
            ShowLoginPage(hwnd);
            break;

        case ID_BTN_BACK:
            ShowMainMenu(hwnd);
            break;

        case ID_BTN_SIGNIN_MENU:
            ShowSigninPage(hwnd);
            break;

        case ID_BTN_LOGIN_DO:
        {
            char user[100], pass[100];
            GetWindowText(hEditUser, user, 100);
            GetWindowText(hEditPass, pass, 100);

            if (checkLogin(user, pass))
            {
                currentUser = user; // 🔥 เก็บชื่อที่ login สำเร็จ
                std::string welcome = "Account ID : " + currentUser;

                userBalance = getBalance(user);

                char balText[100];
                snprintf(balText, sizeof(balText), "BALANCE : %.2f THB.", userBalance);
                SetWindowText(hStaticBalance, balText);
                // sprintf(balText, "BALANCE : %.2f    THB .", userBalance);
                // SetWindowText(hStaticBalance, balText);
                SetWindowText(hStaticAccount, welcome.c_str());
                AccoutPage(hwnd);
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
        case ID_BTN_DEPOSITE:
            Showdeposit(hwnd);
            break;

        case ID_BTN_DEPOSITE_DO:
        {
            char pass[20];
            char amountStr[200];

            GetWindowText(hEditPass_Ac, pass, 20);
            GetWindowText(hEditAmount, amountStr, 200);

            std::string amountText = amountStr;

            // 🔴 ตรวจ format เงินก่อน
            if (!isValidAmount(amountText))
            {
                MessageBox(hwnd,
                           "Invalid amount format\nExample: 100 or 100.50",
                           "Error", MB_OK);
                return 0;
            }

            double amount = std::stod(amountText);
            int func = depositMoney(currentUser, pass, amount);

            if (func == 1)
            {
                MessageBox(hwnd, "Deposit Success", "Success", MB_OK);

                userBalance = getBalance(currentUser);

                char balText[50];
                snprintf(balText, sizeof(balText), "BALANCE : %.2f THB.", userBalance);
                SetWindowText(hStaticBalance, balText);
            }
            else if (func == 2)
            {
                MessageBox(hwnd, "Wrong password", "Error", MB_OK);
            }

            else if (func == 3)
            {
                MessageBox(hwnd, "Please Enter the amount", "Error", MB_OK);
            }
            else
            {
                MessageBox(hwnd, "Please contact the bank", "Error", MB_OK);
            }

            SetWindowText(hEditAmount, "");
            SetWindowText(hEditPass_Ac, "");
            break;
        }

        case ID_BTN_WITHDRAW:
            ShowWithdrawPage(hwnd);
            break;

        case ID_BTN_WITHDRAW_DO:
        {
            char pass[20];
            char amountStr[200];

            GetWindowText(hEditPass_Ac, pass, 20);
            GetWindowText(hEditAmount, amountStr, 200);

            std::string amountText = amountStr;

            // 🔴 ตรวจ format เงินก่อน
            if (!isValidAmount(amountText))
            {
                MessageBox(hwnd,
                           "Invalid amount format\nExample: 100 or 100.50",
                           "Error", MB_OK);
                return 0;
            }

            double amount = std::stod(amountText);
            int func1 = withdrawMoney(currentUser, pass, amount, userBalance);

            if (func1 == 1)
            {

                MessageBox(hwnd, "Withdraw Success", "Success", MB_OK);

                userBalance = getBalance(currentUser);

                char balText[50];
                snprintf(balText, sizeof(balText), "BALANCE : %.2f THB.", userBalance);
                SetWindowText(hStaticBalance, balText);
            }
            else if (func1 == 2)
            {
                MessageBox(hwnd, "Wrong password", "Error", MB_OK);
            }
            else if (func1 == 3)
            {
                MessageBox(hwnd, "Your current balance is insufficient", "Error", MB_OK);
            }
            else if (func1 == 4)
            {
                MessageBox(hwnd, "Please Enter the amount", "Error", MB_OK);
            }
            else if (func1 == 0)
            {
                MessageBox(hwnd, "Please contact the bank", "Error", MB_OK);
            }
            SetWindowText(hEditAmount, "");
            SetWindowText(hEditPass_Ac, "");
        }
        break;

        case ID_BTN_TRANSFER:
            ShowTransferPage(hwnd);
            break;

        case ID_BTN_TRANSFER_DO:
        {
            char target[100];
            char pass[20];
            char amountStr[200];

            GetWindowText(hEditTo_user, target, 100);
            GetWindowText(hEditPass_tran, pass, 20);
            GetWindowText(hEditAmount_tran, amountStr, 200);

            std::string amountText = amountStr;

            // 🔴 ตรวจ format เงินก่อน
            if (!isValidAmount(amountText))
            {
                MessageBox(hwnd,
                           "Invalid amount format\nExample: 100 or 100.50",
                           "Error", MB_OK);
                return 0;
            }

            double amount = std::stod(amountText);
            int func2 = transferMoney(currentUser, target, pass, amount);

            if (func2 == 1)
            {
                userBalance = getBalance(currentUser);

                MessageBox(hwnd, "Transfer Success", "Success", MB_OK);

                char balText[50];
                snprintf(balText, sizeof(balText), "BALANCE : %.2f THB.", userBalance);
                SetWindowText(hStaticBalance, balText);
            }
            else if (func2 == 2)
            {
                MessageBox(hwnd, "Wrong password", "Error", MB_OK);
            }
            else if (func2 == 3)
            {
                MessageBox(hwnd, "Account not found", "Error", MB_OK);
            }
            else if (func2 == 4)
            {
                MessageBox(hwnd, "Please Enter the amount", "Error", MB_OK);
            }
            else if (func2 == 5)
            {
                MessageBox(hwnd, "Your current balance is insufficient", "Error", MB_OK);
            }
            SetWindowText(hEditAmount_tran, "");
            SetWindowText(hEditPass_tran, "");
            SetWindowText(hEditTo_user, "");
        }
        break;

        case ID_BTN_HOME:
            AccoutPage(hwnd);
            SetWindowText(hEditAmount_tran, "");
            SetWindowText(hEditPass_tran, "");
            SetWindowText(hEditTo_user, "");
            SetWindowText(hEditPass_Ac, "");
            SetWindowText(hEditAmount, "");
            break;

        case ID_BTN_LOGOUT:
            ShowMainMenu(hwnd);
            SetWindowText(hEditAmount_tran, "");
            SetWindowText(hEditPass_tran, "");
            SetWindowText(hEditTo_user, "");
            SetWindowText(hEditPass_Ac, "");
            SetWindowText(hEditAmount, "");
            SetWindowText(hEditUser, "");
            SetWindowText(hEditPass, "");
            break;

        case ID_BTN_STATEMENT:
            ShowStatementPage(hwnd);
            break;

        case ID_LIST_HISTORY:
        {
            SendMessage(hListHistory, LB_RESETCONTENT, 0, 0);

            vector<vector<string>> data = fetch_data(currentUser);

            for (auto &row : data)
            {
                char buffer[200];
                // เปลี่ยนจาก %-12s มาใช้ \t ขั้นระหว่างข้อมูลแทน
                snprintf(buffer, sizeof(buffer), "%s\t%s\t%s\t%s",
                         row[0].c_str(),
                         row[1].c_str(),
                         row[2].c_str(),
                         row[3].c_str());

                SendMessage(hListHistory, LB_ADDSTRING, 0, (LPARAM)buffer);
            }
        }
        break;

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
        SetTextColor(hdcStatic, RGB(255, 255, 255));
        SetBkMode(hdcStatic, TRANSPARENT);
        return (INT_PTR)hBrushBg;
    }

    case WM_CTLCOLOREDIT:
    {
        HDC hdc = (HDC)wp;

        SetTextColor(hdc, RGB(255, 255, 255)); // สีตัวอักษร
        SetBkColor(hdc, RGB(1, 60, 32));       // สีพื้นหลังเหมือน BG

        // return (INT_PTR)hEditBg;            // ใช้พื้นหลังสีเขียวแทน
        return (INT_PTR)hBrushBg; // ใช้ brush เดียวกับ background
    }

    case WM_DRAWITEM:
    {
        LPDRAWITEMSTRUCT dis = (LPDRAWITEMSTRUCT)lp;

        dis->itemState &= ~ODS_FOCUS; // 🔥 ปิด focus rectangle

        // ===== ปุ่ม DEPOSIT =====
        if (dis->CtlID == ID_BTN_LOGIN_MENU)
        {
            FillRect(dis->hDC, &dis->rcItem, hBrushBg);

            Graphics graphics(dis->hDC);
            graphics.DrawImage(imgLogin,
                               static_cast<INT>(dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.top),
                               static_cast<INT>(dis->rcItem.right - dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.bottom - dis->rcItem.top));

            return TRUE;
        }

        if (dis->CtlID == ID_BTN_SIGNIN_MENU)
        {
            FillRect(dis->hDC, &dis->rcItem, hBrushBg);

            Graphics graphics(dis->hDC);
            graphics.DrawImage(imgSignin,
                               static_cast<INT>(dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.top),
                               static_cast<INT>(dis->rcItem.right - dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.bottom - dis->rcItem.top));

            return TRUE;
        }

        if (dis->CtlID == ID_BTN_EXIT)
        {
            FillRect(dis->hDC, &dis->rcItem, hBrushBg);

            Graphics graphics(dis->hDC);
            graphics.DrawImage(imgExit,
                               static_cast<INT>(dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.top),
                               static_cast<INT>(dis->rcItem.right - dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.bottom - dis->rcItem.top));

            return TRUE;
        }

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
        if (dis->CtlID == ID_BTN_WITHDRAW)
        {
            FillRect(dis->hDC, &dis->rcItem, hBrushBg);

            Graphics graphics(dis->hDC);
            graphics.DrawImage(imgWithdraw,
                               static_cast<INT>(dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.top),
                               static_cast<INT>(dis->rcItem.right - dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.bottom - dis->rcItem.top));

            return TRUE;
        }

        if (dis->CtlID == ID_BTN_TRANSFER)
        {
            FillRect(dis->hDC, &dis->rcItem, hBrushBg);

            Graphics graphics(dis->hDC);
            graphics.DrawImage(imgTransfer,
                               static_cast<INT>(dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.top),
                               static_cast<INT>(dis->rcItem.right - dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.bottom - dis->rcItem.top));

            return TRUE;
        }
        if (dis->CtlID == ID_BTN_HOME)
        {
            FillRect(dis->hDC, &dis->rcItem, hBrushBg);

            Graphics graphics(dis->hDC);
            graphics.DrawImage(imgHome,
                               static_cast<INT>(dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.top),
                               static_cast<INT>(dis->rcItem.right - dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.bottom - dis->rcItem.top));

            return TRUE;
        }

        if (dis->CtlID == ID_BTN_BACK)
        {
            FillRect(dis->hDC, &dis->rcItem, hBrushBg);

            Graphics graphics(dis->hDC);
            graphics.DrawImage(imgHome,
                               static_cast<INT>(dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.top),
                               static_cast<INT>(dis->rcItem.right - dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.bottom - dis->rcItem.top));

            return TRUE;
        }

        if (dis->CtlID == ID_BTN_LOGOUT)
        {
            FillRect(dis->hDC, &dis->rcItem, hBrushBg);

            Graphics graphics(dis->hDC);
            graphics.DrawImage(imgLogout,
                               static_cast<INT>(dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.top),
                               static_cast<INT>(dis->rcItem.right - dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.bottom - dis->rcItem.top));

            return TRUE;
        }

        if (dis->CtlID == ID_BTN_DEPOSITE_DO)
        {
            FillRect(dis->hDC, &dis->rcItem, hBrushBg);

            Graphics graphics(dis->hDC);
            graphics.DrawImage(imgDep,
                               static_cast<INT>(dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.top),
                               static_cast<INT>(dis->rcItem.right - dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.bottom - dis->rcItem.top));

            return TRUE;
        }

        if (dis->CtlID == ID_BTN_WITHDRAW_DO)
        {
            FillRect(dis->hDC, &dis->rcItem, hBrushBg);

            Graphics graphics(dis->hDC);
            graphics.DrawImage(imgDep,
                               static_cast<INT>(dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.top),
                               static_cast<INT>(dis->rcItem.right - dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.bottom - dis->rcItem.top));

            return TRUE;
        }

        if (dis->CtlID == ID_BTN_TRANSFER_DO)
        {
            FillRect(dis->hDC, &dis->rcItem, hBrushBg);

            Graphics graphics(dis->hDC);
            graphics.DrawImage(imgDep,
                               static_cast<INT>(dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.top),
                               static_cast<INT>(dis->rcItem.right - dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.bottom - dis->rcItem.top));

            return TRUE;
        }

        if (dis->CtlID == ID_BTN_STATEMENT)
        {
            FillRect(dis->hDC, &dis->rcItem, hBrushBg);

            Graphics graphics(dis->hDC);
            graphics.DrawImage(imgStatement,
                               static_cast<INT>(dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.top),
                               static_cast<INT>(dis->rcItem.right - dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.bottom - dis->rcItem.top));

            return TRUE;
        }

        if (dis->CtlID == ID_BTN_LOGIN_DO)
        {
            FillRect(dis->hDC, &dis->rcItem, hBrushBg);

            Graphics graphics(dis->hDC);
            graphics.DrawImage(imgLogin_do,
                               static_cast<INT>(dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.top),
                               static_cast<INT>(dis->rcItem.right - dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.bottom - dis->rcItem.top));

            return TRUE;
        }

        if (dis->CtlID == ID_BTN_SIGN_IN_DO)
        {
            FillRect(dis->hDC, &dis->rcItem, hBrushBg);

            Graphics graphics(dis->hDC);
            graphics.DrawImage(imgSignin_do,
                               static_cast<INT>(dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.top),
                               static_cast<INT>(dis->rcItem.right - dis->rcItem.left),
                               static_cast<INT>(dis->rcItem.bottom - dis->rcItem.top));

            return TRUE;
        }

        break;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT r;

        // ===== USER BOX =====
        if (IsWindowVisible(hEditUser))
        {
            GetWindowRect(hEditUser, &r);
            MapWindowPoints(NULL, hwnd, (LPPOINT)&r, 2);

            SelectObject(hdc, focusedEdit == hEditUser ? hEditBorderFocus : hEditBorder);
            SelectObject(hdc, GetStockObject(NULL_BRUSH));
            RoundRect(hdc, r.left - 2, r.top - 2, r.right + 2, r.bottom + 2, 10, 10);
        }

        // ===== PASS BOX =====
        if (IsWindowVisible(hEditPass))
        {
            GetWindowRect(hEditPass, &r);
            MapWindowPoints(NULL, hwnd, (LPPOINT)&r, 2);

            SelectObject(hdc, focusedEdit == hEditPass ? hEditBorderFocus : hEditBorder);
            SelectObject(hdc, GetStockObject(NULL_BRUSH));
            RoundRect(hdc, r.left - 2, r.top - 2, r.right + 2, r.bottom + 2, 10, 10);
        }

        if (IsWindowVisible(hEditName))
        {
            GetWindowRect(hEditPass, &r);
            MapWindowPoints(NULL, hwnd, (LPPOINT)&r, 2);

            SelectObject(hdc, focusedEdit == hEditName ? hEditBorderFocus : hEditBorder);
            SelectObject(hdc, GetStockObject(NULL_BRUSH));
            RoundRect(hdc, r.left - 2, r.top - 2, r.right + 2, r.bottom + 2, 10, 10);
        }

        if (IsWindowVisible(hEditAmount))
        {
            GetWindowRect(hEditAmount, &r);
            MapWindowPoints(NULL, hwnd, (LPPOINT)&r, 2);

            SelectObject(hdc, focusedEdit == hEditAmount ? hEditBorderFocus : hEditBorder);
            SelectObject(hdc, GetStockObject(NULL_BRUSH));
            RoundRect(hdc, r.left - 2, r.top - 2, r.right + 2, r.bottom + 2, 10, 10);
        }

        if (IsWindowVisible(hEditAmount_tran))
        {
            GetWindowRect(hEditAmount_tran, &r);
            MapWindowPoints(NULL, hwnd, (LPPOINT)&r, 2);

            SelectObject(hdc, focusedEdit == hEditAmount_tran ? hEditBorderFocus : hEditBorder);
            SelectObject(hdc, GetStockObject(NULL_BRUSH));
            RoundRect(hdc, r.left - 2, r.top - 2, r.right + 2, r.bottom + 2, 10, 10);
        }

        if (IsWindowVisible(hEditPass_Ac))
        {
            GetWindowRect(hEditPass_Ac, &r);
            MapWindowPoints(NULL, hwnd, (LPPOINT)&r, 2);

            SelectObject(hdc, focusedEdit == hEditPass_Ac ? hEditBorderFocus : hEditBorder);
            SelectObject(hdc, GetStockObject(NULL_BRUSH));
            RoundRect(hdc, r.left - 2, r.top - 2, r.right + 2, r.bottom + 2, 10, 10);
        }

        if (IsWindowVisible(hEditPass_tran))
        {
            GetWindowRect(hEditPass_tran, &r);
            MapWindowPoints(NULL, hwnd, (LPPOINT)&r, 2);

            SelectObject(hdc, focusedEdit == hEditPass_tran ? hEditBorderFocus : hEditBorder);
            SelectObject(hdc, GetStockObject(NULL_BRUSH));
            RoundRect(hdc, r.left - 2, r.top - 2, r.right + 2, r.bottom + 2, 10, 10);
        }

        if (IsWindowVisible(hEditTo_user))
        {
            GetWindowRect(hEditTo_user, &r);
            MapWindowPoints(NULL, hwnd, (LPPOINT)&r, 2);

            SelectObject(hdc, focusedEdit == hEditTo_user ? hEditBorderFocus : hEditBorder);
            SelectObject(hdc, GetStockObject(NULL_BRUSH));
            RoundRect(hdc, r.left - 2, r.top - 2, r.right + 2, r.bottom + 2, 10, 10);
        }

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_LBUTTONDOWN:
    {
        POINT pt;
        pt.x = LOWORD(lp);
        pt.y = HIWORD(lp);

        RECT rc;
        GetWindowRect(btnLoginDo, &rc);
        ScreenToClient(hwnd, (LPPOINT)&rc);
        ScreenToClient(hwnd, ((LPPOINT)&rc) + 1);

        if (PtInRect(&rc, pt))
        {
            MoveWindow(btnLoginDo, 302, 252, 200, 40, TRUE);
            loginPressed = true;
        }
    }
    break;

    case WM_LBUTTONUP:
    {
        if (loginPressed)
        {
            MoveWindow(btnLoginDo, 300, 250, 200, 40, TRUE);
            loginPressed = false;
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
        return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

LRESULT CALLBACK AmountProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    if (msg == WM_CHAR)
    {
        char ch = (char)wp;

        if (ch == 8) // Backspace
            return CallWindowProc(oldAmountProc, hwnd, msg, wp, lp);

        char text[50];
        GetWindowText(hwnd, text, sizeof(text));

        std::string s = text;

        // อนุญาตเฉพาะตัวเลข
        if (ch >= '0' && ch <= '9')
        {
            size_t dot = s.find('.');
            if (dot != std::string::npos)
            {
                int decimals = s.length() - dot - 1;
                if (decimals >= 2)
                    return 0; // ห้ามเกิน 2 ตำแหน่ง
            }

            return CallWindowProc(oldAmountProc, hwnd, msg, wp, lp);
        }

        // จุดทศนิยม
        if (ch == '.')
        {
            if (s.find('.') != std::string::npos)
                return 0; // มีจุดแล้ว

            if (s.length() == 0)
            {
                SetWindowText(hwnd, "0.");
                SendMessage(hwnd, EM_SETSEL, 2, 2);
                return 0;
            }

            return CallWindowProc(oldAmountProc, hwnd, msg, wp, lp);
        }

        return 0; // block ตัวอื่น
    }

    return CallWindowProc(oldAmountProc, hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
    WNDCLASS wc = {0};
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(101));

    wc.hInstance = hInst;
    wc.lpszClassName = "BankClass";
    wc.lpfnWndProc = WindowProcedure;

    g_hInstance = hInst;


    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    hBrushBg = CreateSolidBrush(RGB(1, 50, 32));
    wc.hbrBackground = hBrushBg;

    RegisterClass(&wc);

    CreateWindow("BankClass", "FAM SOD BANK",
                 WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
                     WS_MINIMIZEBOX | WS_VISIBLE,
                 200, 100, 800, 500,
                 NULL, NULL, hInst, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}