/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const int smartgaps                 = 1;  /* 1 means no outer gap when there is only one window */
static int gaps                            = 1;  /* 1 means gaps between windows are added */
static const unsigned int gappx            = 4;  /* gap pixel between windows */
static const unsigned int borderpx         = 2;  /* border pixel of windows */
static const int showbar                   = 1;  /* 0 means no bar */
static const int topbar                    = 1;  /* 0 means bottom bar */
static const char *fonts[]                 = {"Saucecodepronf:size=9"};
static const float rootcolor[]             = COLOR(0x000000ff);
/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.1f, 0.1f, 0.1f, 1.0f}; /* You can also use glsl colors */
static uint32_t colors[][3]                = {
	/*               fg          bg          border    */
	[SchemeNorm] = { 0xcdd6f4ff, 0x11111bff, 0x1e1e2eff },
	[SchemeSel]  = { 0xcdd6f4ff, 0x1e1e2eff, 0xfab387ff },
	[SchemeUrg]  = { 0,          0,          0x770000ff },
};

/* tagging - TAGCOUNT must be no greater than 31 */
static char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};

/* logging */
static int log_level = WLR_ERROR;

/* Autostart */
static const char *const autostart[] = {
	"dbus-update-activation-environment", "--systemd", "WAYLAND_DISPLAY", "XDG_CURRENT_DESKTOP=wlroots", NULL,
	"sh", "-c", "pidof /usr/lib/hyprpolkitagent || /usr/lib/hyprpolkitagent", NULL,
	"wl-paste", "--type", "image", "--watch", "cliphist", "store", NULL,
	"wl-paste", "--type", "text", "--watch", "cliphist", "store", NULL,
	"sh", "-c", "pidof hypridle || hypridle", NULL,
	"sh", "-c", "pgrep lowbat || lowbat", NULL,
	"syncthing", "serve", "--no-browser", NULL,
	"kdeconnect-indicator", NULL,
	"sh", "-c", "wbg_wall ~/Pictures/wallpapers/wallpaper_21.jpg", NULL,
	"dunst", NULL,
	NULL /* terminate */
};


/* NOTE: ALWAYS keep a rule declared even if you don't use rules (e.g leave at least one example) */
static const Rule rules[] = {
	/* app_id             title       tags mask     isfloating  isterm  noswallow  monitor */
	/* examples: */
	{ "Gimp_EXAMPLE",     NULL,       0,            1,          0,      0,         -1 }, /* Start on currently visible tags floating, not tiled */
	{ "firefox_EXAMPLE",  NULL,       1 << 8,       0,          0,      0,         -1 }, /* Start on ONLY tag "9" */
	{ "foot",             NULL,       0,            0,          1,      1,         -1 }, /* make foot swallow clients that are not foot */
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "[M]",      monocle },
};

/* monitors */
/* (x=-1, y=-1) is reserved as an "autoconfigure" monitor position indicator
 * WARNING: negative values other than (-1, -1) cause problems with Xwayland clients
 * https://gitlab.freedesktop.org/xorg/xserver/-/issues/899
*/
/* NOTE: ALWAYS add a fallback rule, even if you are completely sure it won't be used */
static const MonitorRule monrules[] = {
	/* name       mfact  nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	*/
	/* defaults */
	{ NULL,       0.55f, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.layout = "vmk",
	.options = NULL,
};

static const int repeat_rate = 50;
static const int repeat_delay = 300;

/* Trackpad */
static const int tap_to_click =0;
static const int tap_and_drag = 0;
static const int drag_lock = 0;
static const int natural_scrolling = 0;
static const int disable_while_typing = 0;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    -1, KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  -1, KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, -1, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,-1,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]    = { "foot", NULL };
static const char *menucmd[]    = { "rofi", "-show", "drun", NULL };
static const char *menualtcmd[] = { "wmenu-run", NULL };
static const char *browsercmd[] = { "firefox", NULL };
static const char *clipbcmd[]   = { "sh", "-c", "cliphist list | rofi -dmenu | cliphist decode | wl-copy", NULL };

static const char *plistcmd[]     = { "plist", NULL };
static const char *bmcmd[]        = { "bm", NULL };
static const char *tmuxrrcmd[]    = { "foot", "sh", "-c", "tmux attach -t rr || tmux new -s rr", NULL };

static const char *areascrscmd[] = { "sh", "-c", "filename=$HOME/Pictures/grim/$(date +%F_%T).png && slurp | grim -g - $filename && wl-copy -t image/png < $filename", NULL };
static const char *fullscrscmd[] = { "sh", "-c", "filename=$HOME/Pictures/grim/$(date +%F_%T).png && grim $filename && wl-copy -t image/png < $filename", NULL };

static const char *volupcmd[]      = { "sh", "-c", "pactl set-sink-volume 0 +5% && kill -44 $(pidof slstatus)", NULL };
static const char *voldowncmd[]    = { "sh", "-c", "pactl set-sink-volume 0 -5% && kill -44 $(pidof slstatus)", NULL };
static const char *volupaltcmd[]   = { "sh", "-c", "pactl set-sink-volume 0 +1% && kill -44 $(pidof slstatus)", NULL };
static const char *voldownaltcmd[] = { "sh", "-c", "pactl set-sink-volume 0 -1% && kill -44 $(pidof slstatus)", NULL };
static const char *volmutecmd[]    = { "sh", "-c", "pactl set-sink-mute 0 toggle && kill -44 $(pidof slstatus)", NULL };

static const char *micupcmd[]      = { "sh", "-c", "pactl set-source-volume 0 +5% && kill -44 $(pidof slstatus)", NULL };
static const char *micdowncmd[]    = { "sh", "-c", "pactl set-source-volume 0 -5% && kill -44 $(pidof slstatus)", NULL };
static const char *micupaltcmd[]   = { "sh", "-c", "pactl set-source-volume 0 +1% && kill -44 $(pidof slstatus)", NULL };
static const char *micdownaltcmd[] = { "sh", "-c", "pactl set-source-volume 0 -1% && kill -44 $(pidof slstatus)", NULL };
static const char *micmutecmd[]    = { "sh", "-c", "pactl set-source-mute 0 toggle && kill -44 $(pidof slstatus)", NULL };

static const char *mpdtogglecmd[]  = { "mpc", "toggle",  NULL };
static const char *mpdnextcmd[]    = { "mpc", "next",    NULL };
static const char *mpdprevcmd[]    = { "mpc", "prev",    NULL };
static const char *mpdshufflecmd[] = { "mpc", "shuffle", NULL };
static const char *mpdrandomcmd[]  = { "mpc", "random",  NULL };
static const char *mpdvolupcmd[]   = { "sh", "-c", "mpc volume +10 && notify-send -t 300 $(mpc volume)", NULL };
static const char *mpdvoldowncmd[] = { "sh", "-c", "mpc volume -10 && notify-send -t 300 $(mpc volume)", NULL };
static const char *mpdloopcmd[]    = { "sh", "-c", "mpc repeat && mpc single", NULL };
static const char *mpdqueuecmd[]   = { "foot", "mpq", NULL };
static const char *mpdaddallcmd[]  = { "foot", "mqa", NULL };
static const char *mpdaddsubcmd[]  = { "foot", "mqp", NULL };
static const char *mpdadddircmd[]  = { "foot", "mqd", NULL };

static const char *mediaplaycmd[] = { "playerctl", "play-pause", NULL };
static const char *medianextcmd[] = { "playerctl", "next",       NULL };
static const char *mediaprevcmd[] = { "playerctl", "previous",   NULL };

static const char *brupcmd[]       = { "brightnessctl", "set", "10%+", NULL };
static const char *brdowncmd[]     = { "brightnessctl", "set", "10%-", NULL };
static const char *brupaltcmd[]    = { "brightnessctl", "set", "1%+",  NULL };
static const char *brdownaltcmd[]  = { "brightnessctl", "set", "1%-",  NULL };

static const char *shutdowncmd[] = { "systemctl", "poweroff",    NULL };
static const char *rebootcmd[]   = { "systemctl", "reboot",      NULL };
static const char *srebootcmd[]  = { "systemctl", "soft-reboot", NULL };
static const char *suspendcmd[]  = { "systemctl", "suspend",     NULL };
static const char *lockcmd[]     = { "hyprlock", NULL, };

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */
	{ MODKEY,                    -1, XKB_KEY_p,          spawn,          {.v = menucmd} },
	{ MODKEY|WLR_MODIFIER_ALT,   -1, XKB_KEY_p,          spawn,          {.v = menualtcmd} },
	{ MODKEY,                    -1, XKB_KEY_Return,     spawn,          {.v = termcmd} },
	{ MODKEY,                    -1, XKB_KEY_v,          spawn,          {.v = browsercmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, -1, XKB_KEY_V,          spawn,          {.v = clipbcmd} },
	{ 0,                         -1, XKB_KEY_Print,      spawn,          {.v = areascrscmd} },
	{ WLR_MODIFIER_SHIFT,        -1, XKB_KEY_Print,      spawn,          {.v = fullscrscmd} },
	{ MODKEY,                    -1, XKB_KEY_o,          spawn,          {.v = plistcmd} },
	{ MODKEY,                    -1, XKB_KEY_n,          spawn,          {.v = bmcmd} },
	{ MODKEY|WLR_MODIFIER_ALT,   -1, XKB_KEY_Return,     spawn,          {.v = tmuxrrcmd} },
	{ MODKEY,                    -1, XKB_KEY_b,          togglebar,      {0} },
	{ MODKEY,                    -1, XKB_KEY_j,          focusstack,     {.i = +1} },
	{ MODKEY,                    -1, XKB_KEY_k,          focusstack,     {.i = -1} },
	{ MODKEY,                    -1, XKB_KEY_i,          incnmaster,     {.i = +1} },
	{ MODKEY,                    -1, XKB_KEY_d,          incnmaster,     {.i = -1} },
	{ MODKEY,                    -1, XKB_KEY_h,          setmfact,       {.f = -0.05f} },
	{ MODKEY,                    -1, XKB_KEY_l,          setmfact,       {.f = +0.05f} },
	{ MODKEY,                    -1, XKB_KEY_Tab,        zoom,           {0} },
	{ MODKEY,                    -1, XKB_KEY_g,          togglegaps,     {0} },
	{ MODKEY,                    -1, XKB_KEY_x,          killclient,     {0} },
	{ MODKEY,                    -1, XKB_KEY_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    -1, XKB_KEY_m,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                    -1, XKB_KEY_space,      togglefloating, {0} },
	{ MODKEY,                    -1, XKB_KEY_f,          togglefullscreen, {0} },
	{ MODKEY,                    -1, XKB_KEY_0,          view,           {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, -1, XKB_KEY_parenright, tag,            {.ui = ~0} },
	{ MODKEY,                    -1, XKB_KEY_comma,      focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    -1, XKB_KEY_period,     focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, -1, XKB_KEY_less,       tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, -1, XKB_KEY_greater,    tagmon,         {.i = WLR_DIRECTION_RIGHT} },
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                         1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                 2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                  6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                   7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                  8),
	TAGKEYS(          XKB_KEY_q, XKB_KEY_Q,                          5),
	TAGKEYS(          XKB_KEY_w, XKB_KEY_W,                          6),
	TAGKEYS(          XKB_KEY_e, XKB_KEY_E,                          7),
	TAGKEYS(          XKB_KEY_r, XKB_KEY_R,                          8),
	TAGKEYS(          XKB_KEY_grave, XKB_KEY_asciitilde,             9),
	{ MODKEY,                    XKB_KEY_s, XKB_KEY_space,      spawn,          {.v = mpdtogglecmd}  },
	{ MODKEY,                    XKB_KEY_s, XKB_KEY_n,          spawn,          {.v = mpdnextcmd}    },
	{ MODKEY,                    XKB_KEY_s, XKB_KEY_p,          spawn,          {.v = mpdprevcmd}    },
	{ MODKEY,                    XKB_KEY_s, XKB_KEY_s,          spawn,          {.v = mpdshufflecmd} },
	{ MODKEY,                    XKB_KEY_s, XKB_KEY_r,          spawn,          {.v = mpdrandomcmd}  },
	{ MODKEY,                    XKB_KEY_s, XKB_KEY_equal,      spawn,          {.v = mpdvolupcmd}   },
	{ MODKEY,                    XKB_KEY_s, XKB_KEY_minus,      spawn,          {.v = mpdvoldowncmd} },
	{ MODKEY,                    XKB_KEY_s, XKB_KEY_l,          spawn,          {.v = mpdloopcmd}    },
	{ MODKEY,                    XKB_KEY_s, XKB_KEY_q,          spawn,          {.v = mpdqueuecmd}   },
	{ MODKEY,                    XKB_KEY_s, XKB_KEY_g,          spawn,          {.v = mpdaddallcmd}  },
	{ MODKEY,                    XKB_KEY_s, XKB_KEY_a,          spawn,          {.v = mpdaddsubcmd}  },
	{ MODKEY,                    XKB_KEY_s, XKB_KEY_d,          spawn,          {.v = mpdadddircmd}  },
	{ 0,                                   -1, XKB_KEY_XF86AudioRaiseVolume,     spawn,    {.v = volupcmd}      },
	{ 0,                                   -1, XKB_KEY_XF86AudioLowerVolume,     spawn,    {.v = voldowncmd}    },
	{ WLR_MODIFIER_SHIFT,                  -1, XKB_KEY_XF86AudioRaiseVolume,     spawn,    {.v = volupaltcmd}   },
	{ WLR_MODIFIER_SHIFT,                  -1, XKB_KEY_XF86AudioLowerVolume,     spawn,    {.v = voldownaltcmd} },
	{ 0,                                   -1, XKB_KEY_XF86AudioMute,            spawn,    {.v = volmutecmd}    },
	{ WLR_MODIFIER_ALT,                    -1, XKB_KEY_XF86AudioRaiseVolume,     spawn,    {.v = micupcmd}      },
	{ WLR_MODIFIER_ALT,                    -1, XKB_KEY_XF86AudioLowerVolume,     spawn,    {.v = micdowncmd}    },
	{ WLR_MODIFIER_ALT|WLR_MODIFIER_SHIFT, -1, XKB_KEY_XF86AudioRaiseVolume,     spawn,    {.v = micupaltcmd}   },
	{ WLR_MODIFIER_ALT|WLR_MODIFIER_SHIFT, -1, XKB_KEY_XF86AudioLowerVolume,     spawn,    {.v = micdownaltcmd} },
	{ 0,                                   -1, XKB_KEY_XF86AudioMicMute,         spawn,    {.v = micmutecmd}    },
	{ 0,                                   -1, XKB_KEY_XF86MonBrightnessUp,      spawn,    {.v = brupcmd}       },
	{ 0,                                   -1, XKB_KEY_XF86MonBrightnessDown,    spawn,    {.v = brdowncmd}     },
	{ 0,                                   -1, XKB_KEY_XF86MonBrightnessUp,      spawn,    {.v = brupaltcmd}    },
	{ 0,                                   -1, XKB_KEY_XF86MonBrightnessDown,    spawn,    {.v = brdownaltcmd}  },
	{ 0,                                   -1, XKB_KEY_XF86AudioPlay,            spawn,    {.v = mediaplaycmd}  },
	{ 0,                                   -1, XKB_KEY_XF86AudioNext,            spawn,    {.v = medianextcmd}  },
	{ 0,                                   -1, XKB_KEY_XF86AudioPrev,            spawn,    {.v = mediaprevcmd}  },
	{ 0,                                   -1, XKB_KEY_Cancel,                   spawn,    {.v = mediaplaycmd}  },
	{ 0,                                   -1, XKB_KEY_XF86Favorites,            spawn,    {.v = medianextcmd}  },
	{ 0,                                   -1, XKB_KEY_XF86Go,                   spawn,    {.v = mediaprevcmd}  },
	{ MODKEY,                    -1, XKB_KEY_F12,        spawn,          {.v = shutdowncmd} },
	{ MODKEY,                    -1, XKB_KEY_F11,        spawn,          {.v = rebootcmd}   },
	{ MODKEY|WLR_MODIFIER_ALT,   -1, XKB_KEY_F11,        spawn,          {.v = srebootcmd}  },
	{ MODKEY,                    -1, XKB_KEY_F10,        spawn,          {.v = suspendcmd}  },
	{ MODKEY,                    -1, XKB_KEY_F9,         spawn,          {.v = lockcmd}     },
	{ MODKEY|WLR_MODIFIER_SHIFT, -1, XKB_KEY_T,           quit,          {0} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,-1,XKB_KEY_Terminate_Server, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,-1,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Key lockedkeys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */
	{ 0,                                   -1, XKB_KEY_XF86AudioRaiseVolume,     spawn,    {.v = volupcmd}      },
	{ 0,                                   -1, XKB_KEY_XF86AudioLowerVolume,     spawn,    {.v = voldowncmd}    },
	{ WLR_MODIFIER_SHIFT,                  -1, XKB_KEY_XF86AudioRaiseVolume,     spawn,    {.v = volupaltcmd}   },
	{ WLR_MODIFIER_SHIFT,                  -1, XKB_KEY_XF86AudioLowerVolume,     spawn,    {.v = voldownaltcmd} },
	{ 0,                                   -1, XKB_KEY_XF86AudioMute,            spawn,    {.v = volmutecmd}    },
	{ WLR_MODIFIER_ALT,                    -1, XKB_KEY_XF86AudioRaiseVolume,     spawn,    {.v = micupcmd}      },
	{ WLR_MODIFIER_ALT,                    -1, XKB_KEY_XF86AudioLowerVolume,     spawn,    {.v = micdowncmd}    },
	{ WLR_MODIFIER_ALT|WLR_MODIFIER_SHIFT, -1, XKB_KEY_XF86AudioRaiseVolume,     spawn,    {.v = micupaltcmd}   },
	{ WLR_MODIFIER_ALT|WLR_MODIFIER_SHIFT, -1, XKB_KEY_XF86AudioLowerVolume,     spawn,    {.v = micdownaltcmd} },
	{ 0,                                   -1, XKB_KEY_XF86AudioMicMute,         spawn,    {.v = micmutecmd}    },
	{ 0,                                   -1, XKB_KEY_XF86MonBrightnessUp,      spawn,    {.v = brupcmd}       },
	{ 0,                                   -1, XKB_KEY_XF86MonBrightnessDown,    spawn,    {.v = brdowncmd}     },
	{ 0,                                   -1, XKB_KEY_XF86MonBrightnessUp,      spawn,    {.v = brupaltcmd}    },
	{ 0,                                   -1, XKB_KEY_XF86MonBrightnessDown,    spawn,    {.v = brdownaltcmd}  },
	{ 0,                                   -1, XKB_KEY_XF86AudioPlay,            spawn,    {.v = mediaplaycmd}  },
	{ 0,                                   -1, XKB_KEY_XF86AudioNext,            spawn,    {.v = medianextcmd}  },
	{ 0,                                   -1, XKB_KEY_XF86AudioPrev,            spawn,    {.v = mediaprevcmd}  },
	{ 0,                                   -1, XKB_KEY_Cancel,                   spawn,    {.v = mediaplaycmd}  },
	{ 0,                                   -1, XKB_KEY_XF86Favorites,            spawn,    {.v = medianextcmd}  },
	{ 0,                                   -1, XKB_KEY_XF86Go,                   spawn,    {.v = mediaprevcmd}  },
	{ MODKEY,                    -1, XKB_KEY_F12,        spawn,          {.v = shutdowncmd} },
	{ MODKEY,                    -1, XKB_KEY_F11,        spawn,          {.v = rebootcmd}   },
	{ MODKEY|WLR_MODIFIER_ALT,   -1, XKB_KEY_F11,        spawn,          {.v = srebootcmd}  },
	{ MODKEY,                    -1, XKB_KEY_F10,        spawn,          {.v = suspendcmd}  },
};

static const Button buttons[] = {
	{ ClkLtSymbol, 0,      BTN_LEFT,   setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol, 0,      BTN_RIGHT,  setlayout,      {.v = &layouts[2]} },
	{ ClkTitle,    0,      BTN_MIDDLE, zoom,           {0} },
	{ ClkStatus,   0,      BTN_MIDDLE, spawn,          {.v = termcmd} },
	{ ClkClient,   MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ ClkClient,   MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ ClkClient,   MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
	{ ClkTagBar,   0,      BTN_LEFT,   view,           {0} },
	{ ClkTagBar,   0,      BTN_RIGHT,  toggleview,     {0} },
	{ ClkTagBar,   MODKEY, BTN_LEFT,   tag,            {0} },
	{ ClkTagBar,   MODKEY, BTN_RIGHT,  toggletag,      {0} },
};

