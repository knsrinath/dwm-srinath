// INCLUDES
#include <X11/XF86keysym.h>

// APPEARANCE
static const unsigned int borderpx  = 2;
static const unsigned int snap      = 32;
static const unsigned int gappx     = 10;
static const int showbar            = 1;
static const int topbar             = 1;
static const char buttonbar[]       = "DWM";
static const char *fonts[]          = { "JetBrains Mono:weight=bold:size=10:antialias=true:autohint=true" };
static const char dmenufont[]       = "Jetbrains Mono:size=10:weight=Bold:antialias=true:autohint=true";
static const char col_bg[]          = "#282a36";
static const char col_fg[]          = "#ff79c6";
static const char *colors[][3]      = {
	/*                 fg      bg    border   */
	[SchemeNorm] = { col_fg, col_bg, col_bg },
	[SchemeSel]  = { col_bg, col_fg, col_fg },
};

// TAGGING
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	// CLASS                         INSTANCE     TITLE         TAGS            FLOAT        MONITOR
	{ "Gimp",                          NULL,       NULL,       1 << 8,            0,           -1 },
	{ "Firefox",                       NULL,       NULL,       2,                 0,           -1 },
	{ "Tor Browser",                   NULL,       NULL,       1 << 8,            0,           -1 },	
	{ "Chromium",                      NULL,       NULL,       2,                 0,           -1 },
	{ "Google-chrome",                 NULL,       NULL,       2,                 0,           -1 },
	{ "Vivaldi-stable",                NULL,       NULL,       2,                 0,           -1 },
	{ "Brave-browser",                 NULL,       NULL,       2,                 0,           -1 },
	{ "zoom",                          NULL,       NULL,       1 << 3,            0,           -1 },
	{ "whatsapp-nativefier-d40211",    NULL,       NULL,       1 << 3,            0,           -1 },
	{ "Signal",                        NULL,       NULL,       1 << 3,            0,           -1 },
	{ "Spotify",                       NULL,       NULL,       1 << 5,            0,           -1 },
	{ "Pcmanfm",                       NULL,       NULL,       1 << 2,            0,           -1 },
	{ "Thunar",                        NULL,       NULL,       1 << 2,            0,           -1 },
	{ "Geany",                         NULL,       NULL,       1 << 4,            0,           -1 },
	{ "code-oss",                      NULL,       NULL,       1 << 4,            0,           -1 },
	{ "Minetest",                      NULL,       NULL,       1 << 6,            0,           -1 },
	{ "chromium-bsu",                  NULL,       NULL,       1 << 6,            0,           -1 },
	{ "supertuxkart",                  NULL,       NULL,       1 << 6,            0,           -1 },
	{ "VirtualBox Manager",            NULL,       NULL,       1 << 7,            0,           -1 },
	{ "Pavucontrol",                   NULL,       NULL,       1 << 9,            1,           -1 },
	{ "Pqiv",                          NULL,       NULL,       1 << 9,            1,           -1 },
	{ "scratchpad",                    NULL,       NULL,       1 << 9,            1,           -1 },
};

// LAYOUT
static const float mfact     = 0.5;
static const int nmaster     = 1;
static const int resizehints = 0;

static const Layout layouts[] = {
	//SYMBOL     FUNCTOIN
	{ "[]=",      tile },
	{ "<><",      NULL },
	{ "[M]",      monocle },
};

// KEY DEFINETIONS
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

// helper for spawning shell commands in the pre dwm-5.0 fashion
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

// COMMANDS
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = 		{ "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[] = 			{ "alacritty", "-e", "fish", NULL };
static const char *scratchpadcmd[] = 	{ "tdrop", "-am", "-w", "60%", "-h", "60%", "-y", "20%", "-x", "20%", "alacritty", "--class", "scratchpad,scratchpad", "-e", "fish", NULL };
static const char *clip[]  = 			{ "clipmenu", NULL };
static const char *scrshot[]  = 		{ "scrot", "/home/srinath/Pictures/%Y-%m-%d.png", NULL };

// VOLUME
static const char *upvol[] = 	{ "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *downvol[] = 	{ "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *mutevol[] = 	{ "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };

// MEDIA
static const char *playpause[] = 	{ "playerctl", "play-pause", NULL };
static const char *next[] = 		{ "playerctl", "next", NULL };
static const char *prev[] = 		{ "playerctl", "previous", NULL };

// KEY BINDINGS
static Key keys[] = {
	//MODIFIER                      KEY       FUNCTION          ARGUMENT
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  spawn,          {.v = scratchpadcmd } },
	{ MODKEY,                       XK_v,      spawn,          {.v = clip } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },
	{ 0,            		XF86XK_AudioLowerVolume,    spawn,          {.v = downvol} },
	{ 0,            		XF86XK_AudioRaiseVolume,    spawn,          {.v = upvol}  },
	{ 0,            		XF86XK_AudioMute,           spawn,          {.v = mutevol} },
	{ 0,            		XF86XK_AudioPlay,           spawn,          {.v = playpause} },
	{ 0,            		XF86XK_AudioPause,          spawn,          {.v = playpause} },
	{ 0,            		XF86XK_AudioNext,           spawn,          {.v = next} },
	{ 0,            		XF86XK_AudioPrev,           spawn,          {.v = prev} },
	{ 0,            		XK_Print,           		spawn,          {.v = scrshot} },
};

// BUTTONS
// click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin
static Button buttons[] = {
	//CLICK                 EVENT           BUTTON          FUNCTION        ARGUMENT
	{ ClkButton,			0,				Button1,		spawn,			{.v = termcmd } },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

