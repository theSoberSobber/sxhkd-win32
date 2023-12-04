# sxhkd-win32
sxhkd impl for windows, cus why not.

# Instructions
- Edit config.h and actions.h according to what you want
- Build using `make all` or `make`
- Copy the produced `sxhkd-win32.exe` to your location of choice
- Run `make clean` in the working directory to clean it

# Virtual Desktop Features
Please see [VD-Action.md](./VD-action.md).

# Sample config.h

```c
#define MODKEY 		(MOD_ALT)
// options: MOD_WIN | MOD_CTRL | MOD_SHIFT | MOD_ALT
// can be combined by binary OR operator

// Use MODKEY | MOD_SHIFT for mod + shift
// VK_RETURN == RETURN KEY on Keyboard
// VK_TAB == TAB KEY on Keyboard

// command, argument
static const char *termcmd[]  = { "wt.exe", NULL };
static const char *vscode[] = {"code", "D:/code"};

#define NUMKEY(x) \
		{MODKEY,	x+'0',	GoToDesktopNumberW, 	{.i= x ? x : 10}}, \
		{MODKEY|MOD_SHIFT, x+'0', MoveWindowToDesktopNumberW, {.i= x ? x : 10}}

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       'B',       test,          {0} },
	{ MODKEY,                       'P',       spawn,      	  {.v = vscode} },
	{ MODKEY,                     VK_RETURN, spawn,         {.v = termcmd } },
	{ MODKEY,                       'E',       toggleexplorer, {0} },
	{ MODKEY | MOD_SHIFT,                       'Q',       quit,          {0} },
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
