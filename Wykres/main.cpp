#include <windows.h>
#include <cmath>

HPEN hpen;
HBRUSH hbrush;

void onCreate(HWND hwnd, WPARAM wp, LPARAM lp)
{
	hpen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	hbrush = CreateSolidBrush(RGB(0, 255, 0));
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
	if (wp == 1)
	{
		InvalidateRect(hwnd, NULL, TRUE);
		UpdateWindow(hwnd);
	}
}

double minx = -14, maxx = +14, miny = -2, maxy = +2;

void paint(HDC hdc, double ux, double uy, int w, int h)
{
	static PAINTSTRUCT ps;
	static RECT r;

	BeginPaint(hwnd, &ps);

	SelectObject(ps.hdc, hpen);
	SelectObject(ps.hdc, hbrush);

	GetClientRect(hwnd, &r);

	int margin = 20;
	int x0 = r.left + margin;
	int y0 = r.top + margin;
	int x1 = r.right - margin;
	int y1 = r.bottom - margin;
	Rectangle(ps.hdc, x0, y0, x1, y1);

	int w = x1 - x0;
	int h = y1 - y0;
	int xo = h / 2 + margin;
	int yo = h / 2 + margin;
	MoveToEx(ps.hdc, xo, yo, NULL); LineTo(ps.hdc, x1, yo);
	MoveToEx(ps.hdc, xo, yo, NULL); LineTo(ps.hdc, xo, y1);

	int sx = (ux - minx) * w / (maxx - minx);
	int sy = (-uy - miny) * h / (maxy - miny);
	SetPixel(hdc, sx, sy, RGB(0, 0, 255));
	//LineTo(hdc, sx, sy);
}


void draw(HDC hdc, int w, int h)
{
	double step = (maxx - minx) / w;
	for (double x = minx; x<maxx; x += step)
	{
		double y = sin(x);
		paint(hdc, x, y, w, h);
	}
}

LRESULT CALLBACK wnd_proc(HWND hwnd, UINT message, WPARAM wp, LPARAM lp)
{
	switch (message)
	{
	case WM_SIZE:
	case WM_SIZING:
		InvalidateRect(hwnd, NULL, TRUE);
		UpdateWindow(hwnd);
		break;

	case WM_PAINT:
	{
					 static RECT r;
					 GetClientRect(hwnd, &r);

					 static PAINTSTRUCT ps;
					 BeginPaint(hwnd, &ps);
					 draw(ps.hdc, r.right - r.left, r.bottom - r.top);
					 EndPaint(hwnd, &ps);
	}
		break;

	case WM_DESTROY:
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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "NAZWA_KLASY";

	RegisterClassEx(&wc);

	HWND window = CreateWindowEx(0, "NAZWA_KLASY", "Tytu³",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);
	if (!window) return -1;
	onCreate(window, 0, 0);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}
