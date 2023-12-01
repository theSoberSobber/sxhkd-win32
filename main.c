#include <windows.h>
#include <winuser.h>
#include <stdlib.h>
#include <stdio.h>
#include <shellapi.h>
#include <stdbool.h>

#define NAME "sxhkd-win32"
#define LENGTH(x) (sizeof x / sizeof x[0])

typedef union {
	int i;
	unsigned int ui;
	float f;
	void *v;
} Arg;

typedef struct {
	unsigned int mod;
	unsigned int key;
	void (*func)(const Arg *);
	const Arg arg;
} Key;

#include "debug.h"
#include "actions.h"
#include "config.h"

HWND dwmhwnd;

/* Actions Implementation */

void quit(const Arg* arg) {
	PostMessage(dwmhwnd, WM_CLOSE, 0, 0);
}

void test(const Arg* arg) {
	dbg("Hello from handler!\n");
}

void spawn(const Arg *arg) {
	ShellExecute(NULL, NULL, ((char **)arg->v)[0], ((char **)arg->v)[1], NULL, SW_SHOWDEFAULT);
}

void toggleexplorer(const Arg *arg) {
#define setvisibility(x, y) SetWindowPos(x, 0, 0, 0, 0, 0, (y ? SWP_SHOWWINDOW : SWP_HIDEWINDOW) | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	HWND hwnd = FindWindow("Progman", "Program Manager");
	if (hwnd) setvisibility(hwnd, !IsWindowVisible(hwnd));

	hwnd = FindWindow("Shell_TrayWnd", NULL);
	if (hwnd) setvisibility(hwnd, !IsWindowVisible(hwnd));
}

/* Actions End here */

void cleanup() {
	for (int i = 0; i < LENGTH(keys); i++) UnregisterHotKey(dwmhwnd, i + 1);
	DestroyWindow(dwmhwnd);
}

void die(const char *errstr, ...) {
	va_list ap;
	va_start(ap, errstr);
	dbg(errstr, ap);
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
		if (wParam > 0 && wParam <= LENGTH(keys)) {
			dbg("\nHotkey was pressed!\n");
			keys[wParam - 1].func(&(keys[wParam - 1].arg));
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
	for (int i = 0; i < LENGTH(keys); i++) RegisterHotKey(dwmhwnd, i + 1, keys[i].mod, keys[i].key);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

#ifdef DEBUG
	extern char ** __argv;
	extern int __argc;

	if (AttachConsole(ATTACH_PARENT_PROCESS)) {
		freopen("CONOUT$", "wb", stdout);
		freopen("CONOUT$", "wb", stderr);
	}
#endif

	dbg("Hello!! : ))\n");

	MSG msg;
	setup(hInstance);

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	cleanup();

	return msg.wParam;
}