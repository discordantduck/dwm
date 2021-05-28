/* APPEARANCE -------------------------------------------------------------- */

static const unsigned int borderpx = 0; /* border pixel of windows */
static const unsigned int snap = 32; /* snap pixel */
static const int showbar = 1; /* 0 means no bar */
static const int topbar = 1; /* 0 means bottom bar */
static const char *fonts[] = {"B&H LucidaTypewriter:size=12"};
//static const char *fonts[] = {"monospace:size=14"};
static const char dmenufont[] = "B&H LucidaTypewriter:size=12";
//static const char dmenufont[] = {"monospace:size=14"};

static const char col_1[] = "#ffffff"; // white
static const char col_2[] = "#000000"; // black
static const char col_3[] = "#000000"; // black
static const char col_4[] = "#ffffff"; // white
static const char col_5[] = "#005577"; // dark red
static const char col_6[] = "#005577"; // red
static const char *colors[][3] =
{
/*                  FG      BG      BORDER */
    [SchemeNorm] = {col_1,  col_2,  col_3},
    [SchemeSel]  = {col_4,  col_5,  col_6},
};

/* STATIC STATUS ----------------------------------------------------------- */
static const int statmonval = 0;

/* TAGGING ----------------------------------------------------------------- */

static const char *tags[] = {"", "", "", "4", "5", "6", "7", "8", ""};

static const Rule rules[] =
{
    /*  xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
    */
/*  CLASS           INSTANCE    TITLE   TAGS MASK   FLOATING    MONITOR */
    {"Alacritty",   NULL,       NULL,   0,          0,          -1},
    {"Code",        NULL,       NULL,   0,          0,          -1},
    {"Firefox",     NULL,       NULL,   0,          0,          -1},
    {"Gimp",        NULL,       NULL,   0,          0,          -1},
    {"Keepassxc",   NULL,       NULL,   0,          0,          -1},
    {"OBS",         NULL,       NULL,   0,          0,          -1},
};

/* LAYOUT ------------------------------------------------------------------ */

static const float mfact = 0.50; /* factor of master area size [0.05..0.95] */
/* number of clients in master area */
static const int nmaster = 1;
/* 1 means respect size hints in tiled resizals */
static const int resizehints = 1;

static const Layout layouts[] =
{
/*  symbol arrange function */
    /* first entry is default */
    {"[]", tile},
    /* no layout function means floating behavior */
    {"[]", NULL},
    {"[]", monocle},
};

/* KEY DEFINITIONS --------------------------------------------------------- */

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    {MODKEY,                        KEY,    view,       {.ui = 1 << TAG}}, \
    {MODKEY|ControlMask,            KEY,    toggleview, {.ui = 1 << TAG}}, \
    {MODKEY|ShiftMask,              KEY,    tag,        {.ui = 1 << TAG}}, \
    {MODKEY|ControlMask|ShiftMask,  KEY,    toggletag,  {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd){.v = (const char*[]){"/bin/sh", "-c", cmd, NULL}}

/* COMMANDS ---------------------------------------------------------------- */

/* component of dmenucmd, manipulated in spawn() */
static char dmenumon[2] = "0";
static const char *dmenucmd[] = {"dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_1, "-nf", col_3, "-sb", col_6, "-sf", col_4, NULL};
static const char *termcmd[] = {"alacritty", NULL};

static Key keys[] =
{
/*  MODIFIER            KEY         FUNCTION        ARGUMENT */
    {MODKEY,            XK_space,   spawn,          {.v = dmenucmd}},
    {MODKEY,            XK_b,       togglebar,      {0}},
    {MODKEY,            XK_j,       focusstack,     {.i = +1}},
    {MODKEY,            XK_k,       focusstack,     {.i = -1}},
    {MODKEY|ShiftMask,  XK_j,       incnmaster,     {.i = +1}},
    {MODKEY|ShiftMask,  XK_k,       incnmaster,     {.i = -1}},
    {MODKEY,            XK_h,       setmfact,       {.f = -0.05}},
    {MODKEY,            XK_l,       setmfact,       {.f = +0.05}},
    {MODKEY,            XK_z,       zoom,           {0}},
    {MODKEY,            XK_0,       view,           {0}},
    {MODKEY|ShiftMask,  XK_c,       killclient,     {0}},
    {MODKEY,            XK_t,       setlayout,      {.v = &layouts[0]}},
    {MODKEY,            XK_f,       setlayout,      {.v = &layouts[1]}},
    {MODKEY,            XK_m,       setlayout,      {.v = &layouts[2]}},
    {MODKEY,            XK_Tab,     setlayout,      {0}},
    {MODKEY|ShiftMask,  XK_Tab,     togglefloating, {0}},
    {MODKEY,            XK_0,       view,           {.ui = ~0}},
    {MODKEY|ShiftMask,  XK_0,       tag,            {.ui = ~0}},
    {MODKEY,            XK_Left,    focusmon,       {.i = -1}},
    {MODKEY,            XK_Right,   focusmon,       {.i = +1}},
    {MODKEY|ShiftMask,  XK_Left,    tagmon,         {.i = -1}},
    {MODKEY|ShiftMask,  XK_Right,   tagmon,         {.i = +1}},
    TAGKEYS(            XK_1,       0)
    TAGKEYS(            XK_2,       1)
    TAGKEYS(            XK_3,       2)
    TAGKEYS(            XK_4,       3)
    TAGKEYS(            XK_5,       4)
    TAGKEYS(            XK_6,       5)
    TAGKEYS(            XK_7,       6)
    TAGKEYS(            XK_8,       7)
    TAGKEYS(            XK_9,       8)
    {MODKEY|ShiftMask,  XK_q,       quit,           {0}},
};

/* BUTTON DEFINITIONS ------------------------------------------------------ */

/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] =
{
/*  CLICK           EVENT MASK  BUTTON      FUNCTION        ARGUMENT */
    {ClkLtSymbol,   0,          Button1,    setlayout,      {0}},
    {ClkLtSymbol,   0,          Button3,    setlayout,      {.v = &layouts[2]}},
    {ClkStatusText, 0,          Button2,    spawn,          {.v = termcmd}},
    {ClkClientWin,  MODKEY,     Button1,    movemouse,      {0}},
    {ClkClientWin,  MODKEY,     Button2,    togglefloating, {0}},
    {ClkClientWin,  MODKEY,     Button3,    resizemouse,    {0}},
    {ClkTagBar,     0,          Button1,    view,           {0}},
    {ClkTagBar,     0,          Button3,    toggleview,     {0}},
    {ClkTagBar,     MODKEY,     Button1,    tag,            {0}},
    {ClkTagBar,     MODKEY,     Button3,    toggletag,      {0}},
};
