//Including Header Files
#include<Windows.h>
UINT MYTIMER=102;
UINT iPaintFlag = 0;
//Declaring Global Functions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain Standard (int_stdcall)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	//Declaration of variables
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	//Initializing WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//Registering above class
	RegisterClassEx(&wndclass);

	//CCreating Window
	hwnd = CreateWindow(szAppName,
		TEXT("ASH"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);	//Boolean Type
	UpdateWindow(hwnd);			//Boolean Type

	//Message Loop
	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	

	return((int)msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	static HBRUSH hbrush[8];
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;

	switch (iMsg) {

	//Set Solid brushes with different colors
	case WM_CREATE:
		hbrush[0] = CreateSolidBrush(RGB(255, 0, 0));
		hbrush[2] = CreateSolidBrush(RGB(0, 255, 0));
		hbrush[3] = CreateSolidBrush(RGB(0, 0, 255));
		hbrush[4] = CreateSolidBrush(RGB(124, 0, 0));
		hbrush[5] = CreateSolidBrush(RGB(0, 124, 0));
		hbrush[6] = CreateSolidBrush(RGB(0, 0, 124));
		hbrush[7] = CreateSolidBrush(RGB(255, 255, 0));
		hbrush[1] = CreateSolidBrush(RGB(255, 0, 255));
		SetTimer(hwnd, MYTIMER, 1000, NULL);
		break;
	
	//Right Click to Stop Animation
	case WM_RBUTTONDOWN:
		KillTimer(hwnd, MYTIMER);
		InvalidateRect(hwnd,NULL,true);
		break;
		
	//Left Click to Start Animation	
	case WM_LBUTTONDOWN:
		SetTimer(hwnd,MYTIMER,1000,NULL);
		break;
		
	//Paint window with with the current brush with respect to value of iPaintFlag
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, hbrush[iPaintFlag]);
		FillRect(hdc, &rc, hbrush[iPaintFlag]);
		//SetBkColor(hdc, RGB(0, 0, 0));
		//SetTextColor(hdc, RGB(0, 255, 0));
		//DrawText(hdc, str1, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		break;

	//Increement iPaintFlag by 1 at a timelapse of 1  second
	case WM_TIMER:
		KillTimer(hwnd, MYTIMER);
		if (iPaintFlag <= 7)
			iPaintFlag++;
		else
			iPaintFlag = 0;
		InvalidateRect(hwnd, NULL, true);
		SetTimer(hwnd, MYTIMER, 1000, NULL);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
