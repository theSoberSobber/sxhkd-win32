HWND topmost = NULL;

BOOL CALLBACK CurrVDTopMostFinder(HWND hwnd, LPARAM lParam) {
    char windowTitle[256];
    GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
    if (IsWindowVisible(hwnd) && IsWindowOnCurrentVirtualDesktopFunc(hwnd) && windowTitle[0] != '\0') {
        printf("windowTitle: %s %d\n", windowTitle);
        topmost = hwnd;
        return FALSE;
    }
    return TRUE;
}

HWND GetTopmostWindowOnCurrentVD(){
    topmost=NULL;
    EnumWindows(CurrVDTopMostFinder, 0);
    return topmost;
}

void MoveWindowToDesktopNumberW(const Arg* arg){
    printf("%d\n", arg->i - 1);
    HWND fgwhwnd = (HWND)GetForegroundWindow();
    MoveWindowToDesktopNumberFunc(fgwhwnd, arg->i - 1);
    lastActive[arg->i - 1] = fgwhwnd;
    // now who to focus on this desktop? focus NEEDS to shifted right now otherwise movewindow 
    // can be called again with the same foreground window that isn't even ahead right now
    SetForegroundWindow(GetTopmostWindowOnCurrentVD());
}

void GoToDesktopNumberW(const Arg* arg){
    lastActive[GetCurrentDesktopFunc()] = GetForegroundWindow();
    GoToDesktopNumberFunc((arg->i - 1 + 10)%10);
    SetForegroundWindow(lastActive[(arg->i - 1 + 10)%10]);
}