# sxhkd-win32
Sxhkd impl for Windows with Optional UNIX like workspace support through Native VirtualDesktops!

# Instructions
- Local Enviornment Method
    - Edit config.h and actions.h according to what you want
    - Build using `make all` or `make`
    - Copy the produced `sxhkd-win32.exe` to your location of choice
    - Run `make clean` in the working directory to clean it
- Github Actions Method (Easier)
    - Fork the repository
    - Change config.h or any other code as you want
    - Go to actions tab and dispatch the build workflow
    - Download the built exe and dll from releases, Enjoy!

# Virtual Desktop Features
- Please see [VD-Action.md](./VD-action.md).
- Note that the VirtualDesktopAccessor DLL used right now is broken on some newer builds of Windows, if other hotkeys are working, then you might wanna download the latest release of VirtualDesktopAccessor.dll from [here](https://github.com/Ciantic/VirtualDesktopAccessor).
- The optimal way of using VDA with sxhkd is after setting the taskbar as hidden and toggling explorer by Alt+E (see config), this prevents any weird flickering behaviour that the taskbar has when VDs are switched too fast
- PS: You can use Bing Wallpaper and set on every VD for a truly awesome VD experience!

# Sample config.h

```c
#define MODKEY 		(MOD_ALT)
// options: MOD_WIN | MOD_CTRL | MOD_SHIFT | MOD_ALT
// can be combined by binary OR operator

// Use MODKEY | MOD_SHIFT for mod + shift
// VK_RETURN == RETURN KEY on Keyboard
// VK_TAB == TAB KEY on Keyboard

// command, argument
static const char *termcmd[]  = {NULL, "wt.exe", NULL };
static const char *adminCmd[] = {"runas", "wt.exe", NULL};
static const char *vscode[] = {NULL, "code", "D:/code"};
static const char *codeforces[] = {"open", "https://codeforces.com", NULL};
static const char *leetcode[] = {"open", "https://leetcode.com", NULL};
static const char *explorer[] = {NULL, "explorer.exe", NULL};
static const char *taskManager[] = {NULL, "Taskmgr.exe", NULL};
static const char *adbConnect[] = {NULL, "D:/win32/ADB-Connect/adb-tcpip-connect.exe", NULL};
static const char *scrcpy[] = {NULL, "D:/win32/ADB-Connect/launch-scrcpy.vbs", NULL};

#define NUMKEY(x) \
		{MODKEY,	x+'0',	GoToDesktopNumberW, 	{.i= x ? x : 10}}, \
		{MODKEY|MOD_SHIFT, x+'0', MoveWindowToDesktopNumberW, {.i= x ? x : 10}}

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       'B',       test,          {0} },
	{ MODKEY,                       'O',       spawn,      	  {.v = vscode} },
	{ MODKEY,                     VK_RETURN,   spawn,         {.v = termcmd } },
	{ MODKEY | MOD_SHIFT,         VK_RETURN,   spawn,         {.v = adminCmd } },
	{ MODKEY,                     	'C',       spawn,         {.v = codeforces } },
	{ MODKEY,                     	'L',       spawn,         {.v = leetcode } },
	{ MODKEY | MOD_SHIFT,           'E',       toggleexplorer,              {0} },
	{ MODKEY,                       'Q',       killForeground,              {0} },
	{ MODKEY | MOD_SHIFT,           'Q',       killMacForeground,           {0} },
  { MODKEY,                       'E',       spawn,         {.v = explorer}},
	{ MODKEY | MOD_SHIFT,           'Q',       quit,                        {0} },
  { MODKEY,                       'T',       spawn,         {.v = taskManager } },
  { MODKEY,                       'D',       spawn,         {.v = adbConnect  } },
  { MODKEY,                       'F',       spawn,         {.v = scrcpy      } },
  #ifdef VDA_FEATURES
	NUMKEY(1),
	NUMKEY(2),
	NUMKEY(3),
	NUMKEY(4),
	NUMKEY(5),
	NUMKEY(6),
	NUMKEY(7),
	NUMKEY(8),
	NUMKEY(9),
	NUMKEY(0),
	#endif
};
```

# TODO
- Installer (or start menu + program files)
- Scheduler
