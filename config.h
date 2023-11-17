/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */

static const unsigned int systraypinning = 0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
// static const unsigned int systrayonleft =
//     1; /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst = 1; /* 1: if pinning fails, display systray on the first monitor, False:display systray on the last monitor*/
static const int showsystray = 1; /* 0 means no systray */

static const char *fonts[] = {"jetbrains-mono:size=11", "monospace:size=10"};
static const char dmenufont[] = "jetbrains-mono:size=11";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;

static const char norm_fg[] = "#dedfe0"; // Text color 
static const char norm_bg[] = "#14191e"; // Bar color
static const char norm_border[] = "#9b9c9c"; // Unselected border
//
static const char sel_fg[] = "#7c8386"; // Selected Text color 
static const char sel_bg[] = "#14191e"; // Selected Background
static const char sel_border[] = "#252525"; //selected border; selected background dmenu 

static const char urg_fg[] = "#dedfe0";
static const char urg_bg[] = "#9A7A84";
static const char urg_border[] = "#9A7A84";

static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {norm_fg, norm_bg, norm_border},
    [SchemeSel] = {sel_fg, sel_bg, sel_border},
    [SchemeUrg] = {urg_fg, urg_bg, urg_border},
};

// #include "/home/janico/.cache/wal/colors-wal-dwm.h"

static const unsigned int alphas[][3] = {
    /*               fg      bg        border*/
    [SchemeNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeSel] = {OPAQUE, baralpha, borderalpha},
};
/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    // {"Gimp", NULL, NULL, 0, 1, -1},
    // { "Brave",  NULL,       NULL,       1 << 8,       0,           -1 },
    // { "Blueman-manager",  NULL,       NULL,       0,       1,           -1 },
    {"Pavucontrol", NULL, NULL, 0, 1, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"", tile}, /* first entry is default */
    {"💩", NULL},  /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},
/* Backlight controls. */
#define XF86XK_MonBrightnessUp 0x1008FF02   /* Monitor/panel brightness */
#define XF86XK_MonBrightnessDown 0x1008FF03 /* Monitor/panel brightness */
#define XF86XK_KbdLightOnOff 0x1008FF04     /* Keyboards may be lit     */
#define XF86XK_KbdBrightnessUp 0x1008FF05   /* Keyboards may be lit     */
#define XF86XK_KbdBrightnessDown 0x1008FF06 /* Keyboards may be lit     */

/* Audio controls. */
#define XF86XK_AudioMute 0x1008FF12        /* Mute sound from the system */
#define XF86XK_AudioRaiseVolume 0x1008FF13 /* Volume control up          */
#define XF86XK_AudioLowerVolume 0x1008FF11 /* Volume control down        */
#define XF86XK_AudioPlay 0x1008FF14        /* Start playing of audio >   */
#define XF86XK_AudioStop 0x1008FF15        /* Stop playing audio         */
#define XF86XK_AudioPrev 0x1008FF16        /* Previous track             */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
/* #define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } } */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "usr/bin/kitty", "-c", cmd, NULL }                 \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     norm_bg,
    "-nf",       norm_fg, "-sb",    sel_border, "-sf",     sel_fg, NULL};
static const char *termcmd[] = {"kitty", NULL};
static const char *filemgr[] = {"thunar", NULL};
static const char *browser[] = {"firefox", NULL};
static const char *screenshot_gui[] = {"flameshot", "gui", NULL};
static const char *screenshot_screen[] = {"flameshot", "screen", NULL};
static const char *brightinc[] = {"brightnessctl", "set", "5%+", NULL};
static const char *brightdec[] = {"brightnessctl", "set", "5%-", NULL};
static const char *volinc[] = {"wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@",
                               "5%+", NULL};
static const char *voldec[] = {"wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@",
                               "5%-", NULL};
static const char *volmut[] = {"wpctl", "set-mute", "@DEFAULT_SINK@", "toggle",
                               NULL};

static const Key keys[] = {
    /* modifier                     key
       function argument */
    {0, XF86XK_MonBrightnessUp, spawn, {.v = brightinc}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = brightdec}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = volinc}},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = voldec}},
    {0, XF86XK_AudioMute, spawn, {.v = volmut}},
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_e, spawn, {.v = filemgr}},
    {MODKEY, XK_w, spawn, {.v = browser}},
    {MODKEY | ShiftMask, XK_s, spawn, {.v = screenshot_gui}},
    {MODKEY | ControlMask | ShiftMask, XK_s, spawn, {.v = screenshot_screen}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8)
    // { MODKEY|ShiftMask,             XK_q,
    // quit, {0}
    // },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
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
};
