void MoveWindowToDesktopNumberW(const Arg* arg){
    printf("%d", arg->i - 1);
    HWND fgwhwnd = (HWND)GetForegroundWindow();
    if(GetCurrentDesktopFunc()==GetWindowDesktopNumberFunc(fgwhwnd)) MoveWindowToDesktopNumberFunc(fgwhwnd, arg->i - 1);
    SetForegroundWindow(NULL);
}

void GoToDesktopNumberW(const Arg* arg){
    GoToDesktopNumberFunc((arg->i - 1 + 10)%10);
}