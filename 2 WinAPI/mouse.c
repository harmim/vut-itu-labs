#include <windows.h>
#include <stdlib.h>


// Global variable.
HINSTANCE hInst;


// Function prototypes.
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);


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
	POINT ReleasePoint; // point where mouse button was released
	HWND hwndTmp; // window handle where mouse button was released

	switch (uMsg)
	{
		case WM_LBUTTONDOWN:
			SetCapture(hWnd);
			return 0;

		case WM_LBUTTONUP:
			ReleasePoint.x = (int) LOWORD(lParam);
			ReleasePoint.y = (int) HIWORD(lParam);
			if (ReleasePoint.x > 0x7FFF) ReleasePoint.x -= (long) 0xFFFF;
			if (ReleasePoint.y > 0x7FFF) ReleasePoint.y -= (long) 0xFFFF;
			ClientToScreen(hWnd, &ReleasePoint);
			hwndTmp = WindowFromPoint(ReleasePoint);
			// SetWindowText(hwndTmp, ...);
			ReleaseCapture();
			return 0;

		case WM_DESTROY:
			// Clean up window-specific data objects.
			PostQuitMessage(0);
			return 0;

		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}
