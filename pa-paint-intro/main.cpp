#include <windows.h>

HPEN hpen;
HBRUSH hbrush;

void onCreate(HWND hwnd, WPARAM wp, LPARAM lp)
{
	hpen = CreatePen(PS_SOLID, 3, RGB(255,0,0));
	hbrush = CreateSolidBrush(RGB(0,255,0));
	SetTimer(hwnd, 1, 100, NULL);
}

void onDestroy(HWND hwnd, WPARAM wp, LPARAM lp)
{
	DeleteObject(hpen);
	DeleteObject(hbrush);
	KillTimer(hwnd, 1);
}

void onTimer(HWND hwnd, WPARAM wp, LPARAM lp)
{
	if(wp == 1)
	{
		InvalidateRect(hwnd, NULL, TRUE);
		UpdateWindow(hwnd);
	}
}

void onPaint(HWND hwnd, WPARAM wp, LPARAM lp)
{
	static PAINTSTRUCT ps;
	static RECT r;
			
	BeginPaint(hwnd, &ps);

	SelectObject(ps.hdc, hpen);
	SelectObject(ps.hdc, hbrush);

	GetClientRect(hwnd, &r);
	Rectangle(ps.hdc, r.left + 20, r.top + 20, r.right - 20, r.bottom - 20);
	//Rectangle(ps.hdc, 10,10,200,200);
	
	MoveToEx(ps.hdc, 20, 329, NULL);
	LineTo(ps.hdc, 922, 329);
	MoveToEx(ps.hdc, 461, 20, NULL);
	LineTo(ps.hdc, 461, 658);
	
	for (double x = -3; x < 3; x += (6 / 1000))
		double y = sin(x);
		int ye = f(y; (700 / 2) + 20 + (700 / 2));
		MoveToEx(ps.hdc, 20, 329, NULL);
		LineTo(ps.hdc, );

	SelectObject(ps.hdc, GetStockObject(NULL_PEN));
	SelectObject(ps.hdc, GetStockObject(NULL_BRUSH));

			
	EndPaint(hwnd, &ps);
}
LRESULT CALLBACK wnd_proc(HWND hwnd, UINT message, WPARAM wp, LPARAM lp) 
{
	switch(message) 
	{
		case WM_TIMER:
			onTimer(hwnd, wp, lp);
			break;

		case WM_PAINT:
			onPaint(hwnd, wp, lp);
			break;

		case WM_DESTROY: 
			onDestroy(hwnd, wp, lp);
			PostQuitMessage(0); 
			break;
		
		default: 
			return DefWindowProc(hwnd, message, wp, lp);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) 
{
    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbClsExtra = 0;
    wc.style = 0;
    wc.lpfnWndProc = wnd_proc;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    //wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "NAZWA_KLASY";

    RegisterClassEx(&wc);
	
	HWND window = CreateWindowEx(0, "NAZWA_KLASY", "Tytu³", 
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
		NULL, NULL, hInstance, NULL);  
	if(!window) return -1;
	onCreate(window, 0, 0);

	MSG msg;
	while( GetMessage( &msg, 0, 0, 0 ) ) 
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
	
	return 1;
}
