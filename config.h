#include <X11/XF86keysym.h>

/* appearance */
static const char font[]            = "Terminus:size=9" "Kochi Gothic:size=9" "Baekmuk Gulim:size=9";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int progpx    = 50;       /* progress bar width */
static const unsigned int progh     = 2;        /* progress bar height */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = False;     /* False means bottom bar */

#define CYAN  "#133B47"
#define BLACK "#131416"
#define DGRAY "#303030"
#define LGRAY "#666666"
#define RED   "#CF6171"
#define WHITE "#FFFFFF"

static const char color[NUMCOL][ColLast][8] = {
    /* border foreground background */
    { DGRAY,  WHITE,     BLACK     }, /* 0 = unselected, unoccupied */
    { CYAN,   WHITE,     CYAN      }, /* 1 = selected, occupied */
    { RED,    RED,       BLACK     }, /* 2 = urgent */
    { DGRAY,  WHITE,     BLACK     }, /* 3 = unselected, occupied */
    { DGRAY,  WHITE,     CYAN      }, /* 4 = selected, unoccupied */
};

static const char clock_fmt[] = "%a, %I:%M %p";

/* tagging */
#define NTAGS 6

static const Rule rules[] = {
    /* xprop(1):
     *    WM_CLASS(STRING) = instance, class
     *    WM_NAME(STRING) = title
     */
    /* class     instance    title         tags mask     isfloating   monitor */
    { "Firefox",  NULL,       NULL,       1 << 1,       False,        -1 },
    { "Firefox",  NULL,  "Downloads",       NULL,            True,        -1 },
    { "Mpv",      NULL,       NULL,       1 << 3,          True,        -1 },
    { "LxPanel",  NULL,       NULL,       1 << 4,          True,        -1 },
    { "Gimp",     NULL,       NULL,       1 << 4,          True,        -1 },
    { "Audacity", NULL,       NULL,       1 << 4,          False,        -1 },
    { "Evince",   NULL,       NULL,       1 << 4,          True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
    { tile      },    /* first entry is default */
    { bstack    },
    { grid      },
    { monocle   },
    { NULL      },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", color[0][ColBG], "-nf", color[0][ColFG], "-sb", color[1][ColBG], "-sf", color[1][ColFG], NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *surfcmd[]  = { "firefox", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_f,      spawn,          {.v = surfcmd } },
    { MODKEY,                       XK_n,      togglebar,      {-1} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.i = 0} },
    { MODKEY,                       XK_b,      setlayout,      {.i = 1} },
    { MODKEY,                       XK_g,      setlayout,      {.i = 2} },
    { MODKEY,                       XK_m,      setlayout,      {.i = 3} },
    { MODKEY,                       XK_f,      setlayout,      {.i = 4} },
    { MODKEY,                       XK_space,  setlayout,      {.i = -1} },
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
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};
