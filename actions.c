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
#ifdef VDA_FEATURES
#include "VD/VD.c"
#endif

/* Actions End here */