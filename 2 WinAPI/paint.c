#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Global variable.
HINSTANCE hInst;
UINT messageCount = 0;


// Function prototypes.
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
void onPaint(HWND hWnd);


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
	messageCount++;
	InvalidateRect(hWnd, NULL, 0);

	switch (uMsg)
	{
		case WM_PAINT:
			onPaint(hWnd);
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

	// new large font
	HFONT font = CreateFont(
		40,
		0,
		0,
		0,
		0,
		FALSE,
		FALSE,
		FALSE,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		FF_DONTCARE,
		0
	);

	HFONT oldFont = (HFONT) SelectObject(hDC, font); // saves the previous font

	char text[256]; // buffer to store an output text
	sprintf(text, "Msg: %05u", messageCount); // output text
	// writes a character string at the specified location, using the currently selected font, background color, and text color
	TextOut(
		hDC, // handle to device context
		1,
		1,
		text, // character string
		(int) strlen(text) // number of characters
	);

	SelectObject(hDC, oldFont);

	DeleteObject(font);

	DeleteDC(hDC); // deletes the specified device context
	EndPaint(hWnd, &ps); // marks the end of painting in the specified window
}
