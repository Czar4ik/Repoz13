// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"
#include "iostream"
#include "time.h"

#define MAX_LOADSTRING 100
int num = 0;
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ChildProc(HWND, UINT, WPARAM, LPARAM);
HWND hWnd2[7];
RECT lpRect;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_WIN32PROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}



BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	/*HWND hWnd2;*/
	hInst = hInstance; // Store instance handle in our global variable
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	SetWindowText(hWnd, L"MainWindow");
	return TRUE;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	/*LPCTSTR s = L"char";*/
	LPCWSTR titles[7] = { L"1", L"2", L"3", L"4", L"5", L"6", L"7" };
	LPCWSTR title_2[2] = { L"Window 1", L"Window 2" };

	PAINTSTRUCT ps;
	HDC hdc;


	switch (message)
	{

	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
			default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	

	case WM_RBUTTONDOWN:
	{ 
		int i;
		i = rand() % 700;
		SetWindowText(hWnd, title_2[rand() % 2]);

		GetWindowRect(hWnd, &lpRect);

		int x = lpRect.left;/* + rand() % 100*/;
		int y = lpRect.top;/* + rand() % 100*/;
		int Width = 600 + rand() % 100;
		int Height = 600 + rand() % 100;

		MoveWindow(hWnd, x, y, Width, Height, TRUE);

		if (num <= 6)
			{
				hWnd2[num] = CreateWindow(
				szWindowClass, 
				szTitle,
				WS_CAPTION | WS_MINIMIZEBOX | WS_CHILD, 
				50, 
				50, 
				200, 
				200, 
				hWnd,
				NULL,
				hInst, 
				NULL);

				x = 100;
				y = 100;
				Width = 200;
				Height = 200;

				SetWindowText(hWnd2[num], titles[num]);

				ShowWindow(hWnd2[num], SW_SHOW);
				MoveWindow(hWnd2[num], x + num * 100, y + num * 100, Width, Height, TRUE);
				num++;

			}
	break;
	}

	case WM_MBUTTONDOWN:
	{
		DestroyWindow(hWnd2[--num]);
		break;
	}

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;

	case WM_CLOSE:
	{
		 //EnableWindow(hWnd, IDCANCEL);
		 int msg = MessageBox
			 (
			 hWnd,
			 L"Click OK to stop program.",
			 L"Window closed.",
			
			 MB_OKCANCEL | MB_ICONSTOP | MB_DEFBUTTON1
			 );
		 switch (msg)
		 {
		case IDOK:
				 int msg2 = MessageBox
					 (
					 hWnd,
					 L"You shure want to close program?.",
					 L"Window closed.",

					MB_OKCANCEL | MB_ICONSTOP | MB_DEFBUTTON1
					 );
					 switch (msg2)
					 {
					 case IDOK: PostQuitMessage(0); break;

					 } break;

		 break;

		 }
		 break;
	}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK ChildProc(HWND hWnd2, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_KEYUP:
	{

		 PostQuitMessage(0);
		 break;
	}


	case WM_LBUTTONUP:
	{
		 
		 PostQuitMessage(0);
		 break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd2, message, wParam, lParam);
	}
	return 0;
}