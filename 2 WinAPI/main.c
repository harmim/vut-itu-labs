#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define COLOR_RED 0b00
#define COLOR_GREEN 0b01
#define COLOR_BLUE 0b10


// Global variable.
HINSTANCE hInst;
int color;
COLORREF rgbColor;


// Function prototypes.
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
void onPaint(HWND hWnd);
void changeRgbColor();


// Application entry point. This is the same as main() in standart C.
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	hInst = hInstance; // Save the application-instance handle.

	WNDCLASS wcx; // register class

	// Fill in the window class structure with parameters that describe the main window.
	wcx.style = CS_HREDRAW | CS_VREDRAW; // redraw if size changes
	wcx.lpfnWndProc = (WNDPROC) MainWndProc; // points to window procedure
	wcx.cbClsExtra = 0; // no extra class memory
	wcx.cbWndExtra = 0; // no extra window memory
	wcx.hInstance = hInstance; // handle to instance
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION); // predefined app. icon
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW); // predefined arrow
	wcx.hbrBackground = GetStockObject(WHITE_BRUSH); // white background brush
	wcx.lpszMenuName = (LPCSTR) "MainMenu"; // name of menu resource
	wcx.lpszClassName = (LPCSTR) "MainWClass"; // name of window class

	// Register the window class.
	if (!RegisterClass(&wcx)) return 0;

	// Create window of registered class.
	HWND hWnd = CreateWindow(
		(LPCSTR) "MainWClass", // name of window class
		(LPCSTR) "ITU", // title-bar string
		WS_OVERLAPPEDWINDOW, // top-level window
		50, // default horizontal position
		100, // default vertical position
		640, // default width
		480, // default height
		(HWND) NULL, // no owner window
		(HMENU) NULL, // use class menu
		hInstance, // handle to application instance
		(LPVOID) NULL // no window-creation data
	);
	if (!hWnd) return 0;

	// Show the window and send a WM_PAINT message to the window procedure.
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Loop of message processing.
	MSG msg;
	BOOL bRet;
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			// Handle the error and possibly exit.
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}


LRESULT CALLBACK MainWndProc(
	HWND hWnd, // handle to window
	UINT uMsg, // message identifier
	WPARAM wParam, // first message parameter
	LPARAM lParam // second message parameter
)
{
	switch (uMsg)
	{
		case WM_CREATE:
			changeRgbColor();
			return 0;

		case WM_PAINT:
			onPaint(hWnd);
			return 0;

		case WM_MOUSEMOVE:
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;

		case WM_LBUTTONDOWN:
			changeRgbColor();
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;

		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_RETURN:
					changeRgbColor();
					InvalidateRect(hWnd, NULL, TRUE);
					break;
			}
			return 0;

		case WM_DESTROY:
			// Clean up window-specific data objects.
			PostQuitMessage(0);
			return 0;

		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}


void onPaint(HWND hWnd)
{
	PAINTSTRUCT ps; // information can be used to paint the client area of a window owned by that application
	HDC hDC = BeginPaint(hWnd, &ps); // prepares the specified window for painting (device context)

	// print mouse coords
	POINT mousePoint;
	GetCursorPos(&mousePoint);
	ScreenToClient(hWnd, &mousePoint);
	char text[256]; // buffer to store an output text
	sprintf(text, "Mouse X: %ld, Y: %ld", (long) mousePoint.x, (long) mousePoint.y);
	TextOut(
		hDC, // handle to device context
		1,
		1,
		text, // character string
		(int) strlen(text) // number of characters
	);

	// print ellipse
	HBRUSH brush = CreateSolidBrush(rgbColor);
	HBRUSH oldbrush = SelectObject(hDC, brush);
	Ellipse(hDC, 100, 100, 200, 200);
	SelectObject(hDC, oldbrush);

	DeleteDC(hDC); // deletes the specified device context
	EndPaint(hWnd, &ps); // marks the end of painting in the specified window
}


void changeRgbColor()
{
	switch (color)
	{
		case COLOR_RED:
			color = COLOR_GREEN;
			rgbColor = RGB(0, 255, 0);
			return;

		case COLOR_GREEN:
			color = COLOR_BLUE;
			rgbColor = RGB(0, 0, 255);
			return;

		case COLOR_BLUE:
		default:
			color = COLOR_RED;
			rgbColor = RGB(255, 0, 0);
			return;
	}
}
