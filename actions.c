/* Actions Implementation */

void quit(const Arg* arg) {
	PostMessage(dwmhwnd, WM_CLOSE, 0, 0);
}

void test(const Arg* arg) {
	dbg("Hello from handler!\n");
}

void spawn(const Arg *arg) {
	ShellExecute(NULL, ((char **)arg->v)[0], ((char **)arg->v)[1], ((char **)arg->v)[2], NULL, SW_SHOWDEFAULT);
}

void toggleexplorer(const Arg *arg) {
#define setvisibility(x, y) SetWindowPos(x, 0, 0, 0, 0, 0, (y ? SWP_SHOWWINDOW : SWP_HIDEWINDOW) | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	HWND hwnd = FindWindow("Progman", "Program Manager");
	if (hwnd) setvisibility(hwnd, !IsWindowVisible(hwnd));

	hwnd = FindWindow("Shell_TrayWnd", NULL);
	if (hwnd) setvisibility(hwnd, !IsWindowVisible(hwnd));
}

void killForeground(const Arg* arg){
	HWND curr = GetForegroundWindow();
	PostMessage(curr, WM_CLOSE, 0, 0);
}

void killMacForeground(const Arg* arg) {
    HWND curr = GetForegroundWindow();
    DWORD pid;
    GetWindowThreadProcessId(curr, &pid);
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    TerminateProcess(hProcess, 0);
    CloseHandle(hProcess);
}

#ifdef VDA_FEATURES
#include "VD/VD.c"
#endif

/* Actions End here */
