#include <windows.h>
#include <stdlib.h>


#define BUFSIZE 65535


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
	static PTCHAR pchInputBuf; // input buffer
	static int nchLast; // amount of chars in the input buffer
	int nVirtKey; // virtual-key code
	static RECT textArea; // client area
	HDC hdc; // handle to device context
	PAINTSTRUCT ps; // required by BeginPaint

	switch (uMsg)
	{
		case WM_CREATE:
			// Allocate a buffer to store keyboard input.
			pchInputBuf = (LPTSTR) GlobalAlloc(GPTR, BUFSIZE * sizeof(TCHAR));
			nchLast = 0;
			pchInputBuf[nchLast] = TEXT('\0');
			return 0;

		case WM_KEYDOWN:
			switch (wParam) {
				case VK_LEFT: // LEFT ARROW
					break;

				case VK_RIGHT: // RIGHT ARROW
					nVirtKey = GetKeyState(VK_SHIFT);
					if (nVirtKey & 0x8000) {
					}
					break;
			}
			return 0;

		case WM_CHAR:
			switch (wParam) {
				case 0x08: // backspace
				case 0x0A: // linefeed
				case 0x1B: // escape
					MessageBeep((UINT) -1);
					break;

				case 0x09: // tab
					// Convert tabs to four consecutive spaces.
					for (int i = 0; i < 4; i++) {
						SendMessage(hWnd, WM_CHAR, 0x20, 0);
					}
					break;

				case 0x0D: // carriage return
					// Record the carriage return and position the caret at the beginning of the new line.
					pchInputBuf[nchLast++] = 0x0D;
					break;

				default: // displayable character
					// Store the character in the buffer.
					pchInputBuf[nchLast++] = (TCHAR) wParam;
					break;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;

		case WM_SIZE:
			GetClientRect(hWnd, &textArea);
			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// Set the clipping rectangle, and then draw the text into it.
			DrawText(hdc, pchInputBuf, nchLast, &textArea, DT_LEFT);
			EndPaint(hWnd, &ps);
			return 0;

		case WM_DESTROY:
			// Clean up window-specific data objects.
			PostQuitMessage(0);
			// Free the input buffer
			GlobalFree((HGLOBAL) pchInputBuf);
			return 0;

		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}
