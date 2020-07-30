#include<Windows.h>
#include"Flag.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

bool CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	HMENU HMENU;
	HMENU=LoadMenu(hInstance,MAKEINTRESOURCE(IDM_MENU));
	WNDCLASSEX wndClass;
	HWND hwnd1;
	MSG msg;
	TCHAR szAppName[] = TEXT("ILoveMyIndia");

	wndClass.cbSize = sizeof(wndClass);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(INDIA));
	wndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(INDIA));
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszClassName = szAppName;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpszMenuName = NULL;

	RegisterClassEx(&wndClass);

	hwnd1 = CreateWindow(szAppName,
		TEXT("ILoveMyIndia"),
		NULL,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		HMENU,
		hInstance,
		NULL);
	ShowWindow(hwnd1, iCmdShow);
	UpdateWindow(hwnd1);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd1, UINT iMsg, WPARAM wparam, LPARAM lparam) {
	
	static int idColor[5]={WHITE_BRUSH,LTGRAY_BRUSH,GRAY_BRUSH,DKGRAY_BRUSH,BLACK_BRUSH};
	switch (iMsg) {
	
	case WM_CREATE:
		
		break;
	case WM_COMMAND:
		switch(LOWORD(wparam)){
			case IDM_WHITE:
			case IDM_LTGRAY:
			case IDM_GRAY:
			case IDM_DKGRAY:
			case IDM_BLACK:
				SetClassLong(hwnd1,GCL_HBRBACKGROUND,(LONG)GetStockObject(idColor[LOWORD(wparam)-IDM_WHITE]));
				InvalidateRect(hwnd1,NULL,true);
				break;
			case IDM_APP_ABOUT:
				DialogBox((HINSTANCE)GetModuleHandle(NULL),TEXT("ABOUTBOX"),hwnd1,(DLGPROC)AboutDlgProc);
				break;
		}
		break;		
	case WM_PAINT:
		
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return(DefWindowProc(hwnd1, iMsg, wparam, lparam));

}

//Callback function for dialog box of About
bool CALLBACK AboutDlgProc(HWND hdlg, UINT iMsg , WPARAM wparam, LPARAM lparam){
	switch(iMsg){
		
		case WM_INITDIALOG:
			return true;
			
		case WM_COMMAND:
			switch(LOWORD(wparam)){
				
				case IDOK:
				case IDCANCEL:
					EndDialog(hdlg,FALSE);
					return true;
					break;
			}
			break;
		}
	
	return false;
	
}
