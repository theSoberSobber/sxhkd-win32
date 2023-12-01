#include <windows.h>
#include <winuser.h>
#include <stdlib.h>
#include <stdio.h>
#include <shellapi.h>
#include <stdbool.h>

#define NAME   "sxhkd-win32" 	/* Used for window name/class */

// options: MOD_CTRL | MOD_SHIFT | MOD_ALT
#define MODKEY MOD_WIN
#define HOTKEY_ID 1

void eprint(const char *errstr, ...) {
	va_list ap;
	va_start(ap, errstr);
	vfprintf(stdout, errstr, ap);
	fflush(stdout);
	va_end(ap);
}

HWND dwmhwnd;

#ifdef DEBUG
#define dbg eprint
#else
#define dbg
#endif

void quit(const Arg *arg) {
	PostMessage(dwmhwnd, WM_CLOSE, 0, 0);
}

void test() {
	dbg("Toggling Explorer!");
}

void cleanup() {
	UnregisterHotKey(dwmhwnd, HOTKEY_ID);
	DestroyWindow(dwmhwnd);
}

void die(const char *errstr, ...) {
	va_list ap;
	va_start(ap, errstr);
	vfprintf(stdout, errstr, ap);
	fflush(stdout);
	va_end(ap);
	cleanup();
	exit(EXIT_FAILURE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CREATE:
		break;
	case WM_CLOSE:
		cleanup();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_HOTKEY:
		if (wParam == HOTKEY_ID) {
			dbg("\nHotkey was pressed!\n");
			test();
		}
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}


void setup(HINSTANCE hInstance) {
	WNDCLASSEX winClass;

	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.style = 0;
	winClass.lpfnWndProc = WndProc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = hInstance;
	winClass.hIcon = NULL;
	winClass.hIconSm = NULL;
	winClass.hCursor = NULL;
	winClass.hbrBackground = NULL;
	winClass.lpszMenuName = NULL;
	winClass.lpszClassName = NAME;

	if (!RegisterClassEx(&winClass)) die("Error registering window class\n");
	dwmhwnd = CreateWindowEx(0, NAME, NAME, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, hInstance, NULL);
	if (!dwmhwnd) die("Error creating window\n");

	RegisterHotKey(dwmhwnd, HOTKEY_ID, MODKEY, (unsigned int)'4');
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

#ifdef DEBUG
	extern char ** __argv;
	extern int __argc;

	// This attaches a console to the parent process if it has a console
	if (AttachConsole(ATTACH_PARENT_PROCESS)) {
		// reopen stout handle as console window output
		freopen("CONOUT$", "wb", stdout);
		// reopen stderr handle as console window output
		freopen("CONOUT$", "wb", stderr);
	}
#endif

	dbg("Hello!! :))\n");

	MSG msg;

	setup(hInstance);

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	cleanup();

	return msg.wParam;
}
