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

#define NUMKEY(x) \
		{MODKEY,	x+'0',	GoToDesktopNumberW, 	{.i= x ? x : 10}}, \
		{MODKEY|MOD_SHIFT, x+'0', MoveWindowToDesktopNumberW, {.i= x ? x : 10}}

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       'B',       test,          {0} },
	{ MODKEY,                       'P',       spawn,      	  {.v = vscode} },
	{ MODKEY,                     VK_RETURN, spawn,         {.v = termcmd } },
	{ MODKEY | MOD_SHIFT,         VK_RETURN, spawn,         {.v = adminCmd } },
	{ MODKEY,                     	'C', spawn,         {.v = codeforces } },
	{ MODKEY,                     	'L', spawn,         {.v = leetcode } },
	{ MODKEY,                       'E',       toggleexplorer, {0} },
	{ MODKEY,                       'Q',       killForeground,          {0} },
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
