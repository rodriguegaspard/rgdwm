/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int startwithgaps	    = 1;	 /* 1 means gaps are used by default */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[] = { 
    "Iosevka Nerd Font:style=Medium:pixelsize=16", 
    "Sarasa Gothic J:style=Medium:pixelsize=16",
    "Noto Color Emoji:pixelsize=14",
};
static const char dmenufont[] = "Iosevka Nerd Font:style=Medium:pixelsize=16";

// Blue theme colors
static const char col_fg_norm[]		    = "#b0e0e6"; // Powder Blue
static const char col_fg_sel[]		    = "#e7feff"; // Bubbles
static const char col_bg_norm[]		    = "#23297a"; // St. Patrick Blue
static const char col_bg_sel[]		    = "#318ce7"; // Bleu De France
static const char col_border_norm[]	  = "#73a9c2"; // Moonstone Blue
static const char col_border_sel[]	  = "#0f52ba"; // Sapphire

static const unsigned int baralpha = 150; // 0xd0 for opaque
static const unsigned int borderalpha = 150; // OPAQUE for opaque
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg_norm, col_bg_norm, col_border_norm },
	[SchemeSel]  = { col_fg_sel, col_bg_sel,  col_border_sel },
};
static const unsigned int alphas[][3]      = {
    /*               fg      bg        border*/
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	  [SchemeSel]  = { OPAQUE, 200, 200 },
};

/* tagging */
static const char *tags[] = { "書", "記", "網", "話", "聞", "郵", "楽", "映", "遊" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "並",      tile },    /* first entry is default */
	{ "浮",      NULL },    /* no layout function means floating behavior */
	{ "独",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg_norm, "-nf", col_fg_norm, "-sb", col_bg_sel, "-sf", col_fg_sel, NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *voltoggle[]  = { "volumecontrol", "-t", NULL };
static const char *voldown[]  = { "volumecontrol", "-d", NULL };
static const char *volup[]  = { "volumecontrol", "-i", NULL };
static const char *brightness_down[]  = { "xbacklight", "-dec", "5", NULL };
static const char *brightness_up[]  = { "xbacklight", "-inc", "5", NULL };
static const char *filepicker[]  = { "openfilepicker", NULL };
static const char *screenshot[] = { "snapshot", "-s", NULL };
static const char *videocapture[] = {"snapshot", "-v", NULL};
static const char *omniclip_general[] = {"omniclip", "-g", NULL};
static const char *omniclip_browse[] = {"omniclip", "-b", NULL};
static const char *omniclip_french_lowercase[] = {"omniclip", "-q", "french.txt", "lowercase", NULL};
static const char *omniclip_french_uppercase[] = {"omniclip", "-q", "french.txt", "uppercase", NULL};
static const char *vpn_toggle[] = {"vpn", "-t", NULL};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  { MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	{ MODKEY,                       XK_F1,     spawn,          {.v = voltoggle } },
	{ MODKEY,                       XK_F2,     spawn,          {.v = voldown } },
	{ MODKEY,                       XK_F3,     spawn,          {.v = volup } },
	{ MODKEY,                       XK_F11,    spawn,          {.v = brightness_down } },
	{ MODKEY,                       XK_F12,    spawn,          {.v = brightness_up } },
	{ MODKEY,                       XK_r,      spawn,          {.v = filepicker } },
	{ 0     ,                       XK_Print,  spawn,          {.v = screenshot } },
	{ MODKEY,			                  XK_Print,  spawn,	         {.v = videocapture } },
	{ MODKEY,                       XK_o,      spawn,          {.v = omniclip_general } },
	{ MODKEY|ShiftMask,             XK_o,      spawn,          {.v = omniclip_browse } },
  { MODKEY,                       XK_f,      spawn,          {.v = omniclip_french_lowercase } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = omniclip_french_uppercase } },
	{ MODKEY,                       XK_v,      spawn,          {.v = vpn_toggle } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
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

