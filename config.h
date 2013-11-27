#include <X11/XF86keysym.h>

/* appearance */
static const char font[]            = "Terminus:size=8" "Kochi Gothic:size=9" "Baekmuk Gulim:size=9";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const unsigned int progpx    = 50;       /* progress bar width */
static const unsigned int progh     = 2;        /* progress bar height */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

#define CYAN  "#6AA9B0"
#define BLACK "#373737"
#define DGRAY "#575757"
#define LGRAY "#666666"
#define PINK "#FCC1A2"
#define YELLOW "#7882BF"
#define WHITE "#F0F0F0"

static const char color[NUMCOL][ColLast][8] = {
    /* border foreground background */
    { LGRAY,  DGRAY,     WHITE     }, /* 0 = unselected, unoccupied */
    { YELLOW, DGRAY,     YELLOW    }, /* 1 = selected, occupied */
    { PINK,   PINK,      WHITE     }, /* 2 = urgent */
    { LGRAY,  DGRAY,     WHITE     }, /* 3 = unselected, occupied */
    { LGRAY,  WHITE,     CYAN      }, /* 4 = selected, unoccupied */
};

static const char clock_fmt[] = "%a, %m/%d (%H:%M)";

/* tagging */
#define NTAGS 5

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
    { "Evince",   NULL,       NULL,       1 << 4,          False,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
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
static const char *mpdnext[]  = { "mpc next", NULL };
static const char *mpdvolup[] = { "mpc volume +5", NULL};
static const char *mpdvoldn[] = { "mpc volume -5", NULL};
static const char *scrotcmd[] = { "scrot", NULL};
static const char *mpdprev[]  = { "mpc prev", NULL };
static const char *mpdmute[]  = { "mpc stop", NULL };
static const char *mpdplay[]  = { "mpc play", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_f,      spawn,          {.v = surfcmd } },
    { 0,                            0x1008ff13,       spawn,          {.v = mpdvolup } },
    { 0,                            0x1008ff11,       spawn,          {.v = mpdvoldn} },
    { 0,                            0x1008ff17,       spawn,          {.v = mpdnext } },
    { 0,                            0xff61,       spawn,          {.v = scrotcmd } },
    { 0,                            0x1008ff14,       spawn,          {.v = mpdplay} },
    { 0,                            0x1008ff12,       spawn,          {.v = mpdmute } },
    { 0,                            0x1008ff16,       spawn,          {.v = mpdprev } },
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

