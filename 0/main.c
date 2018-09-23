#include <windows.h>


// Global variable
HINSTANCE hInst;


// Function prototypes.
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);


// Application entry point.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	BOOL bRet;
	WNDCLASS wcx; // register class
	HWND hWnd;

	hInst = hInstance; // Save the application-instance handle.

	// Fill in the window class structure with parameters that describe the main window.
	wcx.style = CS_HREDRAW | CS_VREDRAW; // redraw if size changes
	wcx.lpfnWndProc = MainWndProc; // points to window procedure
	wcx.cbClsExtra = 0; // no extra class memory
	wcx.cbWndExtra = 0; // no extra window memory
	wcx.hInstance = hInstance; // handle to instance
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION); // predefined app. icon
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW); // predefined arrow
	wcx.hbrBackground = GetStockObject(WHITE_BRUSH); // white background brush
	wcx.lpszMenuName =  (LPCSTR) "MainMenu"; // name of menu resource
	wcx.lpszClassName = (LPCSTR) "MainWClass"; // name of window class

	// Register the window class.
	if (!RegisterClass(&wcx)) return 0;

	// Create window of registered class.
	hWnd = CreateWindow(
		(LPCSTR) "MainWClass", // name of window class
		(LPCSTR) "Hello FIT!", // title-bar string
		WS_OVERLAPPEDWINDOW, // top-level window
		150, // default horizontal position
		150, // default vertical position
		750, // default width
		150, // default height
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
	while((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
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

	return msg.wParam;
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
		case WM_DESTROY:
			// Clean up window-specific data objects.
			PostQuitMessage(0);
			return 0;

		// Process other messages.
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}
