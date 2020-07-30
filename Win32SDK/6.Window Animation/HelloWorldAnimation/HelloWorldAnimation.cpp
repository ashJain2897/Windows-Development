//Including Header Files
#include<Windows.h>

int iPaintFlag=0;

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
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	
	//Registering above class
	RegisterClassEx(&wndclass);
	
	//Creating Window
	hwnd = CreateWindow(szAppName,
		TEXT("AsH1"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
		
	ShowWindow(hwnd, SW_MAXIMIZE);	//Boolean Type
	UpdateWindow(hwnd);			//Boolean Type

	//ShowWindow(hwnd1, SW_MAXIMIZE);	//Boolean Type
	//UpdateWindow(hwnd1);			//Boolean Type


	//Message Loop
	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);

}

//Callback Function
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	//Handle to device context of your window
	HDC hdc;
	//RECT struct for specifying rectangle area in Client area
	RECT rc;
	//PaintStruct to paint in client area
	PAINTSTRUCT ps;
	TCHAR str1[] = TEXT(" Hello World!!! ");

	switch (iMsg) {

		
		case WM_CREATE:
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(0, 255, 0));
			DrawText(hdc, str1, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hwnd, &ps);
			break;
			
		//Handles Character pressed using Ascii value and sts value to iPaintFlag	
		case WM_CHAR:
			switch(wParam){
				case 'R':
				case 'r':
					iPaintFlag=1;
					break;
				
				case 'G':
				case 'g':
					iPaintFlag=2;
					break;
				
				case 'B':
				case 'b':
					iPaintFlag=3;
					break;
					
				case 'Y':
				case 'y':
					iPaintFlag=4;
					break;
					
				case 'C':
				case 'c':
					iPaintFlag=5;
					break;
			}
			//Used to synthethically/partially call WM_PAINT so that color is set using iPaintFlag
			InvalidateRect(hwnd,NULL,true);
			break;
			
		case WM_RBUTTONDOWN:
			iPaintFlag=6;
			InvalidateRect(hwnd,NULL,true);
			break;
		
		case WM_LBUTTONDOWN:
			iPaintFlag=7;
			InvalidateRect(hwnd,NULL,true);
			break;
			
		case WM_PAINT:
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			SetBkColor(hdc, RGB(0, 0, 0));
			//SetTextColor(hdc, RGB(255, 255, 255));
			//Sets colors on different character press
			if(iPaintFlag==1)
					SetTextColor(hdc, RGB(255,0, 0));
			if(iPaintFlag==2)
					SetTextColor(hdc, RGB(0, 255, 0));
			if(iPaintFlag==3)
					SetTextColor(hdc, RGB(0, 0, 255));
			if(iPaintFlag==4)
					SetTextColor(hdc, RGB(255, 255, 0));
			if(iPaintFlag==5)
					SetTextColor(hdc, RGB(0, 255, 255));
			if(iPaintFlag==6)
					SetTextColor(hdc, RGB(255, 128, 0));
			if(iPaintFlag==7)
					SetTextColor(hdc, RGB(255, 255, 255));
			DrawText(hdc, str1, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hwnd, &ps);
			break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

