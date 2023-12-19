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

#ifdef VDA_FEATURES
HMODULE VDA;

typedef int(*GoToDesktopNumber)(int);
typedef int(*MoveWindowToDesktopNumber)(HWND, int);
typedef int(*GetCurrentDesktop)();
typedef int(*GetWindowDesktopNumber)(HWND);
typedef int(*GetCurrentDesktopNumber)();
typedef int(*IsWindowOnCurrentVirtualDesktop)(HWND);

GetCurrentDesktop GetCurrentDesktopFunc;
MoveWindowToDesktopNumber MoveWindowToDesktopNumberFunc;
GoToDesktopNumber GoToDesktopNumberFunc;
GetWindowDesktopNumber GetWindowDesktopNumberFunc;
GetCurrentDesktopNumber GetCurrentDesktopNumberFunc;
IsWindowOnCurrentVirtualDesktop IsWindowOnCurrentVirtualDesktopFunc;

HWND lastActive[10]; // 0 to 9 index
#endif

#include "actions.c"

void cleanup() {
	for (int i = 0; i < LENGTH(keys); i++) UnregisterHotKey(dwmhwnd, i + 1);
	DestroyWindow(dwmhwnd);
	#ifdef VDA_FEATURES
	FreeLibrary(VDA);
	#endif
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

#ifdef VDA_FEATURES
BOOL CALLBACK initEnumCall(HWND hwnd, LPARAM lParam) {
    char windowTitle[256];
    GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
    if (IsWindowVisible(hwnd) && windowTitle[0] != '\0') {
		if(lastActive[GetWindowDesktopNumberFunc(hwnd)]!=NULL) return TRUE;
        printf("windowTitle: %s %d\n", windowTitle, GetWindowDesktopNumberFunc(hwnd));
		lastActive[GetWindowDesktopNumberFunc(hwnd)]=hwnd;
    }
    return TRUE;
}

HWND initLastActive(){
    EnumWindows(initEnumCall, 0);
    return topmost;
}
#endif

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
	#ifdef VDA_FEATURES
	char* libName = "\\VirtualDesktopAccessor.dll";
	TCHAR libFullPath[MAX_PATH + 1] = { 0 };
	GetCurrentDirectory(MAX_PATH, libFullPath);
	// for(int i=0; libFullPath[i]; i++) if(libFullPath[i]=='\\') libFullPath[i]='/';
	strcat_s(libFullPath, sizeof libFullPath, libName);
	VDA = LoadLibrary(libFullPath);
	if (VDA == NULL){
    	printf("Failed to load the DLL, VD Features will not work");
	};
	MoveWindowToDesktopNumberFunc = (MoveWindowToDesktopNumber)GetProcAddress(VDA, "MoveWindowToDesktopNumber");
	GoToDesktopNumberFunc = (GoToDesktopNumber)GetProcAddress(VDA, "GoToDesktopNumber");
	GetCurrentDesktopFunc = (GetCurrentDesktop)GetProcAddress(VDA, "GetCurrentDesktopNumber");
	GetWindowDesktopNumberFunc = (GetWindowDesktopNumber)GetProcAddress(VDA, "GetWindowDesktopNumber");
	GetCurrentDesktopNumberFunc = (GetCurrentDesktopNumber)GetProcAddress(VDA, "GetCurrentDesktopNumber");
	IsWindowOnCurrentVirtualDesktopFunc = (IsWindowOnCurrentVirtualDesktop)GetProcAddress(VDA, "IsWindowOnCurrentVirtualDesktop");
	for(int i=0; i<10; i++) lastActive[i]=NULL;
	// init with topmost windows of all VDs is essential for when not launched at startup
	initLastActive();
	#endif
	MSG msg;
	setup(hInstance);

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	cleanup();

	return msg.wParam;
}