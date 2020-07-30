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
		WS_OVERLAPPEDWINDOW,
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

	static HBRUSH hBrush[3];
	HDC hdc;
    RECT rect;
	GetClientRect(hwnd1, &rect);
	PAINTSTRUCT pstr;
	LONG top = rect.top;
	LONG btm = rect.bottom;

	switch (iMsg) {
	
	case WM_CREATE:
		//Saffron
		hBrush[0] = CreateSolidBrush(RGB(255,153,51));
		//White
		hBrush[1] = CreateSolidBrush(RGB(255,255,255));
		//Green
		hBrush[2] = CreateSolidBrush(RGB(19,136,8));
		break;

	case WM_PAINT:
		GetClientRect(hwnd1, &rect);
		hdc = BeginPaint(hwnd1, &pstr);

		SelectObject(hdc, hBrush[0]);
		//Saffron
		//GetClientRect(hwnd1, &rect);
		rect.top = top;
		rect.bottom = (btm-top) / 3;
		FillRect(hdc, &rect, hBrush[0]);
		
		SelectObject(hdc, hBrush[1]);
		//White
		//GetClientRect(hwnd1, &rect);
		rect.top = ((btm-top) / 3);
		rect.bottom = (2*(btm-top))/3;
		FillRect(hdc, &rect, hBrush[1]);
		
		SelectObject(hdc, hBrush[2]);
		//Green
		//GetClientRect(hwnd1, &rect);
		rect.top = (2*(btm-top)) / 3;
		rect.bottom = btm;
		FillRect(hdc, &rect, hBrush[2]);

		EndPaint(hwnd1, &pstr);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return(DefWindowProc(hwnd1, iMsg, wparam, lparam));

}

