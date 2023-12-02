#define MODKEY 		(MOD_ALT)
// options: MOD_WIN | MOD_CTRL | MOD_SHIFT | MOD_ALT
// can be combined by binary OR operator

// Use MODKEY | MOD_SHIFT for mod + shift
// VK_RETURN == RETURN KEY on Keyboard

// command, argument
static const char *termcmd[]  = { "wt.exe", NULL };
static const char *vscode[] = {"code", "D:/code"};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       'B',       test,          {0} },
	{ MODKEY,                       'P',       spawn,      	  {.v = vscode} },
	{ MODKEY,                     VK_RETURN, spawn,         {.v = termcmd } },
	{ MODKEY,                       'E',       toggleexplorer, {0} },
	{ MODKEY | MOD_SHIFT,                       'Q',       quit,          {0} }
};
