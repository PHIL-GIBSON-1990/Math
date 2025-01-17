// Math.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Math.h"
#include <windowsx.h>
#include <string>
#include "Generate.cpp"
#include <atlstr.h>
#include <sstream>

#define MAX_LOADSTRING 100
#define BTN_PRINT 101
#define BTN_EXIT 102
#define BTN_PREVIEW 103

// Global Variables:
HINSTANCE hInst;                                // Current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // The main window class name
HWND add, sub, mul, divide, low_1, high_1, low_2, high_2, hWnd; // Handles for GUI elements
Generate* gen;									// Class for generating txt file
std::string choice = " ";
TCHAR str[15];
int l1, l2, h1, h2, print_flag = 0;								// Values from text boxes

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MATH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MATH));

    MSG msg;
	LRESULT chk_add, chk_sub, chk_mul, chk_div, chk_print;
	choice = " ";
    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
		Button_GetCheck(add);
		chk_add = SendMessage(add, BM_GETCHECK, 0, 0);
		chk_sub = SendMessage(sub, BM_GETCHECK, 0, 0);
		chk_mul = SendMessage(mul, BM_GETCHECK, 0, 0);
		chk_div = SendMessage(divide, BM_GETCHECK, 0, 0);
		if (chk_add == BST_CHECKED) {
			choice = "add";
		}
		else if (chk_sub == BST_CHECKED) {
			choice = "sub";
		}
		else if (chk_mul == BST_CHECKED) {
			choice = "mul";
		}
		else if (chk_div == BST_CHECKED) {
			choice = "div";
		}
        //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        if(!IsDialogMessage(hWnd, &msg)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MATH));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(25, 47, 147));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MATH);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	int x = desktop.right;
	int y = desktop.bottom;
	DWORD dwStyle = WS_CAPTION | WS_MINIMIZEBOX;
	hWnd = CreateWindow(szWindowClass, szTitle, dwStyle,
		x/2-250, y/2-125, 520, 300,
		NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	SetMenu(hWnd, NULL);
	UpdateWindow(hWnd);
	add = CreateWindow(TEXT("button"), TEXT("Addition"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 5, 20, 120, 30, hWnd, NULL, NULL, NULL);
	sub = CreateWindow(TEXT("button"), TEXT("Subtraction"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 130, 20, 120, 30, hWnd, NULL, NULL, NULL);
	mul = CreateWindow(TEXT("button"), TEXT("Multiplication"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 255, 20, 120, 30, hWnd, NULL, NULL, NULL);
	divide = CreateWindow(TEXT("button"), TEXT("Division"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 380, 20, 120, 30, hWnd, NULL, NULL, NULL);
	CreateWindow(TEXT("STATIC"), TEXT("Enter Range For First Number:"), WS_CHILD | WS_VISIBLE, 5, 75, 198, 17, hWnd, NULL, NULL, NULL);
	CreateWindow(TEXT("STATIC"), TEXT("Min:"), WS_CHILD | WS_VISIBLE, 5, 105, 30, 20, hWnd, NULL, NULL, NULL);
	CreateWindow(TEXT("STATIC"), TEXT("Max:"), WS_CHILD | WS_VISIBLE, 107, 105, 35, 20, hWnd, NULL, NULL, NULL);
	low_1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_TABSTOP, 46, 105, 50, 20, hWnd, NULL, NULL, NULL);
	high_1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_TABSTOP, 153, 105, 50, 20, hWnd, NULL, NULL, NULL);
	CreateWindow(TEXT("STATIC"), TEXT("Enter Range For Second Number:"), WS_CHILD | WS_VISIBLE, 280, 75, 220, 17, hWnd, NULL, NULL, NULL);
	CreateWindow(TEXT("STATIC"), TEXT("Min:"), WS_CHILD | WS_VISIBLE, 280, 105, 30, 20, hWnd, NULL, NULL, NULL);
	CreateWindow(TEXT("STATIC"), TEXT("Max:"), WS_CHILD | WS_VISIBLE, 382, 105, 35, 20, hWnd, NULL, NULL, NULL);
	low_2 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_TABSTOP, 321, 105, 50, 20, hWnd, NULL, NULL, NULL);
	high_2 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_TABSTOP, 428, 105, 50, 20, hWnd, NULL, NULL, NULL);
	CreateWindow(TEXT("button"), TEXT("Preview"), WS_CHILD | WS_VISIBLE, 85, 150, 315, 30, hWnd, (HMENU)BTN_PREVIEW, NULL, NULL);
	CreateWindow(TEXT("button"), TEXT("Print"), WS_CHILD | WS_VISIBLE, 85, 200, 120, 30, hWnd, (HMENU)BTN_PRINT, NULL, NULL);
	CreateWindow(TEXT("button"), TEXT("Exit"), WS_CHILD | WS_VISIBLE, 280, 200, 120, 30, hWnd, (HMENU)BTN_EXIT, NULL, NULL);
	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	std::istringstream iss;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
			CString str1;
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case BTN_PRINT:
				if (print_flag) {
					ShellExecuteA(hWnd, "print", "quiz.txt", NULL, NULL, 10);
					ShellExecuteA(hWnd, "print", "answers.txt", NULL, NULL, 10);
					print_flag = 0;
				}
				else {
					if (choice == " ") {
						MessageBox(hWnd, TEXT("You must select problem type"), TEXT("Invalid Selection"), MB_OK);
						break;
					}
					GetWindowText(low_1, LPWSTR(str), 10);
					l1 = _ttoi(str);
					if (l1 == NULL) {
						MessageBox(hWnd, TEXT("All text boxes must contain integer values"), TEXT("Invalid Number"), MB_OK);
						break;
					}
					GetWindowText(low_2, LPWSTR(str), 10);
					l2 = _ttoi(str);
					if (l2 == NULL) {
						MessageBox(hWnd, TEXT("All text boxes must contain integer values"), TEXT("Invalid Number"), MB_OK);
						break;
					}
					GetWindowText(high_1, LPWSTR(str), 10);
					h1 = _ttoi(str);
					if (h1 == NULL) {
						MessageBox(hWnd, TEXT("All text boxes must contain integer values"), TEXT("Invalid Number"), MB_OK);
						break;
					}
					GetWindowText(high_2, LPWSTR(str), 10);
					h2 = _ttoi(str);
					if (h2 == NULL) {
						MessageBox(hWnd, TEXT("All text boxes must contain integer values"), TEXT("Invalid Number"), MB_OK);
						break;
					}

					if ((l1 >= h1) || (l2 >= h2)) {
						MessageBox(hWnd, TEXT("Low values must be less than high values"), TEXT("Invalid Number"), MB_OK);
						break;
					}
					gen = new Generate(l1, l2, h1, h2, choice, hWnd);
					gen->build();
					ShellExecuteA(hWnd, "print", "quiz.txt", NULL, NULL, 10);
					ShellExecuteA(hWnd, "print", "answers.txt", NULL, NULL, 10);
				}
				break;
			case BTN_EXIT:
				DeleteFileA("quiz.txt");
				DeleteFileA("answers.txt");
				std::exit(0);
				break;
			case BTN_PREVIEW:
				if (choice == " ") {
					MessageBox(hWnd, TEXT("You must select problem type"), TEXT("Invalid Selection"), MB_OK);
					break;
				}
				GetWindowText(low_1, LPWSTR(str), 10);
				l1 = _ttoi(str);
				if (l1 == NULL) {
					MessageBox(hWnd, TEXT("All text boxes must contain integer values"), TEXT("Invalid Number"), MB_OK);
					break;
				}
				GetWindowText(low_2, LPWSTR(str), 10);
				l2 = _ttoi(str);
				if (l2 == NULL) {
					MessageBox(hWnd, TEXT("All text boxes must contain integer values"), TEXT("Invalid Number"), MB_OK);
					break;
				}
				GetWindowText(high_1, LPWSTR(str), 10);
				h1 = _ttoi(str);
				if (h1 == NULL) {
					MessageBox(hWnd, TEXT("All text boxes must contain integer values"), TEXT("Invalid Number"), MB_OK);
					break;
				}
				GetWindowText(high_2, LPWSTR(str), 10);
				h2 = _ttoi(str);
				if (h2 == NULL) {
					MessageBox(hWnd, TEXT("All text boxes must contain integer values"), TEXT("Invalid Number"), MB_OK);
					break;
				}

				if ((l1 >= h1) || (l2 >= h2)) {
					MessageBox(hWnd, TEXT("Low values must be less than high values"), TEXT("Invalid Number"), MB_OK);
					break;
				}
				gen = new Generate(l1, l2, h1, h2, choice, hWnd);
				gen->build();
				print_flag = 1;
				ShellExecuteA(hWnd, "open", "answers.txt", NULL, NULL, 10);
				ShellExecuteA(hWnd, "open", "quiz.txt", NULL, NULL, 10);
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
