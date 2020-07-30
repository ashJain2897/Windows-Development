//Including Header Files
#include<Windows.h>

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

//Callback Functions
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	int a = 45;
	int b = 15;
	int c = 0;
	
	TCHAR str[225];

	switch (iMsg) {

		//On Key Pressed
		case WM_KEYDOWN:
			c = a + b;
			//Display Sum of 45 and 24
			wsprintf(str, TEXT("The sum of %d and %d is %d"), a, b, c);
			MessageBox(hwnd, str, TEXT("MSG"), MB_OK);
			break;
		
		//Left Mouse Click
		case WM_LBUTTONDOWN:
			c=a-b;
			wsprintf(str, TEXT("The subtraction of %d and %d is %d"), a, b, c);
			MessageBox(hwnd, str, TEXT("MSG"), MB_OK);
			break;
		
		//Right Mouse Click
		case WM_RBUTTONDOWN:
			c=a*b;
			wsprintf(str, TEXT("The Multiplication of %d and %d is %d"), a, b, c);
			MessageBox(hwnd, str, TEXT("MSG"), MB_OK);
			break;
		
		//For this you need to use a mouse as touchpad will not help
		//Middle Mouse Click
		case WM_MBUTTONDOWN:
			c=a/b;
			wsprintf(str, TEXT("The subtraction of %d and %d is %d"), a, b, c);
			MessageBox(hwnd, str, TEXT("MSG"), MB_OK);
			break;
		
			
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
			
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}


