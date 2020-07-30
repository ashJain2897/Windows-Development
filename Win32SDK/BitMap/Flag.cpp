#include<Windows.h>
#include"Flag.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

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
		NULL,
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
	
	HBITMAP hBitmap;
	HDC hdc,hdcMem;
	PAINTSTRUCT ps;
	RECT rect;
	BITMAP bitmap;
	static HINSTANCE hInstance=NULL;
	
	switch (iMsg) {
	
	case WM_CREATE:
		hInstance=(HINSTANCE)GetModuleHandle(NULL);
		break;
	
	//Paint window using Bitmap image
	case WM_PAINT:
		GetClientRect(hwnd1,&rect);
		hdc=BeginPaint(hwnd1,&ps);
		hBitmap=LoadBitmap(hInstance,MAKEINTRESOURCE(MYBITMAP));
		hdcMem=CreateCompatibleDC(NULL);
		SelectObject(hdcMem,hBitmap);
		GetObject(hBitmap,sizeof(BITMAP),&bitmap);
		StretchBlt(hdc,0,0,rect.right,rect.bottom,
			hdcMem,0,0,bitmap.bmWidth,bitmap.bmHeight,
			SRCCOPY);
		DeleteObject(hdcMem);
		DeleteObject(hBitmap);
		EndPaint(hwnd1,&ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return(DefWindowProc(hwnd1, iMsg, wparam, lparam));

}

