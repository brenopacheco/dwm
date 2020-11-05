/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const char *xres = "/home/breno/.Xresources";
/* using nerdfonts for icons */
static const char *fonts[] = {
    "JetBrainsMono Nerd Font:size=11",
    // "UbuntuMono Nerd Font:size=12",
};
// static const char dmenufont[] = "JetBrainsMono Nerd Font:size=12";
static const char dmenufont[] = "ubuntumono:size=12";
static char normbordercolor[] = "#444444";
static char normbgcolor[] = "#222222";
static char normfgcolor[] = "#bbbbbb";
static char selbordercolor[] = "#005577";
static char selbgcolor[] = "#005577";
static char selfgcolor[] = "#eeeeee";
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int gappx = 10;   /* gaps between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const double defaultopacity = 1; // old .9

/* tagging */
static const char *tags[] = {"", "", "", "", "", "", "漣", "", ""};

/*   Display modes of the tab bar: never shown, always shown, shown only in */
/*   monocle mode in presence of several windows.                           */
/*   Modes after showtab_nmodes are disabled                                */
enum showtab_modes {
  showtab_never,
  showtab_auto,
  showtab_nmodes,
  showtab_always
};
static const int showtab = showtab_auto; /* Default tab bar show mode */
static const Bool toptab = False;        /* False means bottom tab bar */

/* default layout per tags */
/* The first element is for all-tag view, following i-th element corresponds to
 */
/* tags[i]. Layout is referred using the layouts array index.*/
static int def_layouts[1 + LENGTH(tags)] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* xprop(1):
 *	WM_CLASS(STRING) = instance, class
 *	WM_NAME(STRING) = title
 */
/*class, instance, title, tagsmask, iscentered, isfloating, monitor */
static const Rule rules[] = {
    {"Firefox", NULL, NULL, 0, 1, 0, -1},
    {"whatsdesk", NULL, "WhatsDesk", 1 << 8, 1, 0, -1},
    {"Skype", NULL, NULL, 1 << 8, 1, 0, -1},
    {"java-lang-Thread", "sun-awt-X11-XFramePeer",
     "Starting Apache NetBeans IDE", 1 << 4, 1, 0, -1},
    {"Apache NetBeans 11.1", "sun-awt-X11-XFramePeer", "Apache NetBeans 11.1",
     1 << 4, 1, 0, -1},
    {"Gnome-calculator", NULL, NULL, 0, 1, 1, -1},
    {"Sxiv", "sxiv", "sxiv", 0, 1, 1, -1},
    {"File-roller", "file-roller", NULL, 0, 1, 1, -1},
    {"Nemo", "nemo", NULL, 0, 1, 1, -1},
    {"URxvt", "urxvt", NULL, 0, 1, 0, -1},
    {"Emacs", "emacs", NULL, 0, 1, 0, -1},
    {"kitty", "kitty", NULL, 0, 1, 0, -1},
    {"st-256color", "st-256color", "st", 0, 1, 0, -1},
    {"Gvim", "gvim", NULL, 0, 1, 1, -1},
    {"Peek", "peek", "Peek", 0, 1, 1, -1},
    {"Xfce4-appfinder", "xfce4-appfinder", NULL, 0, 1, 1, -1}};

    /* {"Zathura", "zathura", NULL, 0, 1, 1, -1}, */

/* layout(s) */
static const float mfact = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints = 0; /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle}, {"TTT", bstack}, {"===", bstackhoriz},
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/bash", "-c", cmd, NULL }                     \
  }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_dwm", "-m", dmenumon, NULL};
static const char *termcmd[] = {"kitty", NULL};
static const char *browsercmd[] = {"browse", NULL};
static const char *emacscmd[] = {"emacsclient", "-c", NULL};
static const char *appfinder[] = {"xfce4-appfinder", NULL};
static const char *dpdf[] = {"dpdf", NULL};

static Key keys[] = {
					 /* modifier,                       key,                      function,
						argument */
					 {MODKEY, XK_F5, xrdb, {.v = NULL}},
					 {MODKEY, XK_d, spawn, {.v = dmenucmd}},
					 {MODKEY, XK_apostrophe, spawn, {.v = appfinder}},
					 {MODKEY, XK_w, spawn, {.v = browsercmd}},
					 {MODKEY, XK_Return, spawn, {.v = termcmd}},
					 {MODKEY, XK_z, spawn, {.v = dpdf}},
					 {MODKEY | ShiftMask, XK_s, spawn, SHCMD("transset-df -a --dec .05")},
					 {MODKEY | ShiftMask, XK_d, spawn, SHCMD("transset-df -a --inc .05")},
					 {MODKEY | ShiftMask, XK_f, spawn, SHCMD("transset-df -a 1")},
					 {MODKEY, XK_b, togglebar, {0}},
					 {MODKEY, XK_e, spawn, {.v = emacscmd}},
					 {MODKEY, XK_v, tabmode, {-1}},
					 {MODKEY, XK_j, focusstack, {.i = +1}},
					 {MODKEY, XK_k, focusstack, {.i = -1}},
					 {MODKEY, XK_n, focusstack, {.i = +1}},
					 {MODKEY, XK_p, focusstack, {.i = -1}},
					 {MODKEY, XK_o, incnmaster, {.i = +1}},
					 {MODKEY, XK_i, incnmaster, {.i = -1}},
					 {MODKEY, XK_h, setmfact, {.f = -0.05}},
					 {MODKEY, XK_l, setmfact, {.f = +0.05}},
					 {MODKEY, XK_BackSpace, zoom, {0}},
					 {MODKEY, XK_Tab, view, {0}},
					 {MODKEY, XK_q, killclient, {0}},
					 {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
					 {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
					 {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
					 {MODKEY, XK_y, setlayout, {.v = &layouts[3]}},
					 {MODKEY, XK_u, setlayout, {.v = &layouts[4]}},
					 {MODKEY, XK_space, setlayout, {0}},
					 {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
					 {MODKEY, XK_0, view, {.ui = ~0}},
					 {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
					 {MODKEY, XK_comma, focusmon, {.i = -1}},
					 {MODKEY, XK_period, focusmon, {.i = +1}},
					 {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
					 {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
					 {MODKEY, XK_minus, setgaps, {.i = -1}},
					 {MODKEY, XK_plus, setgaps, {.i = +1}},
					 {MODKEY | ShiftMask, XK_equal, setgaps, {.i = 0}},
					 {MODKEY, XK_F5, xrdb, {.v = NULL}},
					 {MODKEY | ShiftMask, XK_q, quit, {0}},
					 {MODKEY | ControlMask | ShiftMask, XK_q, quit, {1}},
					 {MODKEY | ShiftMask, XK_j, pushdown, {0}},
					 {MODKEY | ShiftMask, XK_k, pushup, {0}},
					 TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
					 TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
					 TAGKEYS(XK_9, 8)};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or
 * ClkRootWin */
static Button buttons[] = {
						   /* click                event mask      button          function argument
							*/
						   {ClkLtSymbol, 0, Button1, setlayout, {0}},
						   {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
						   {ClkWinTitle, 0, Button2, zoom, {0}},
						   {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
						   {ClkClientWin, MODKEY, Button1, movemouse, {0}},
						   {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
						   {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
						   {ClkTagBar, 0, Button1, view, {0}},
						   {ClkTagBar, 0, Button3, toggleview, {0}},
						   {ClkTagBar, MODKEY, Button1, tag, {0}},
						   {ClkTagBar, MODKEY, Button3, toggletag, {0}},
						   {ClkTabBar, 0, Button1, focuswin, {0}},
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
static Signal signals[] = {
						   /* signum       function        argument  */
						   {1, setlayout, {.v = 0}},
};
