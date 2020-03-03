#include "fsuae-action.h"
#include "fsuae.h"

#define ALL 0

static fsemu_input_configure_keyboard_t keyboard_mapping[] = {
    { FSEMU_KEYBOARD_ESCAPE, ALL, ACTION_KEY_ESCAPE },

    { FSEMU_KEYBOARD_F1, ALL, ACTION_KEY_F1 },
    { FSEMU_KEYBOARD_F2, ALL, ACTION_KEY_F2 },
    { FSEMU_KEYBOARD_F3, ALL, ACTION_KEY_F3 },
    { FSEMU_KEYBOARD_F4, ALL, ACTION_KEY_F4 },
    { FSEMU_KEYBOARD_F5, ALL, ACTION_KEY_F5 },
    { FSEMU_KEYBOARD_F6, ALL, ACTION_KEY_F6 },
    { FSEMU_KEYBOARD_F7, ALL, ACTION_KEY_F7 },
    { FSEMU_KEYBOARD_F8, ALL, ACTION_KEY_F8 },
    { FSEMU_KEYBOARD_F9, ALL, ACTION_KEY_F9 },
    { FSEMU_KEYBOARD_F10, ALL, ACTION_KEY_F10 },

    { FSEMU_KEYBOARD_1, ALL, ACTION_KEY_1 },
    { FSEMU_KEYBOARD_2, ALL, ACTION_KEY_2 },
    { FSEMU_KEYBOARD_3, ALL, ACTION_KEY_3 },
    { FSEMU_KEYBOARD_4, ALL, ACTION_KEY_4 },
    { FSEMU_KEYBOARD_5, ALL, ACTION_KEY_5 },
    { FSEMU_KEYBOARD_6, ALL, ACTION_KEY_6 },
    { FSEMU_KEYBOARD_7, ALL, ACTION_KEY_7 },
    { FSEMU_KEYBOARD_8, ALL, ACTION_KEY_8 },
    { FSEMU_KEYBOARD_9, ALL, ACTION_KEY_9 },
    { FSEMU_KEYBOARD_0, ALL, ACTION_KEY_0 },

    { FSEMU_KEYBOARD_TAB, ALL, ACTION_KEY_TAB },

    { FSEMU_KEYBOARD_A, ALL, ACTION_KEY_A },
    { FSEMU_KEYBOARD_B, ALL, ACTION_KEY_B },
    { FSEMU_KEYBOARD_C, ALL, ACTION_KEY_C },
    { FSEMU_KEYBOARD_D, ALL, ACTION_KEY_D },
    { FSEMU_KEYBOARD_E, ALL, ACTION_KEY_E },
    { FSEMU_KEYBOARD_F, ALL, ACTION_KEY_F },
    { FSEMU_KEYBOARD_G, ALL, ACTION_KEY_G },
    { FSEMU_KEYBOARD_H, ALL, ACTION_KEY_H },
    { FSEMU_KEYBOARD_I, ALL, ACTION_KEY_I },
    { FSEMU_KEYBOARD_J, ALL, ACTION_KEY_J },
    { FSEMU_KEYBOARD_K, ALL, ACTION_KEY_K },
    { FSEMU_KEYBOARD_L, ALL, ACTION_KEY_L },
    { FSEMU_KEYBOARD_M, ALL, ACTION_KEY_M },
    { FSEMU_KEYBOARD_N, ALL, ACTION_KEY_N },
    { FSEMU_KEYBOARD_O, ALL, ACTION_KEY_O },
    { FSEMU_KEYBOARD_P, ALL, ACTION_KEY_P },
    { FSEMU_KEYBOARD_Q, ALL, ACTION_KEY_Q },
    { FSEMU_KEYBOARD_R, ALL, ACTION_KEY_R },
    { FSEMU_KEYBOARD_S, ALL, ACTION_KEY_S },
    { FSEMU_KEYBOARD_T, ALL, ACTION_KEY_T },
    { FSEMU_KEYBOARD_U, ALL, ACTION_KEY_U },
    { FSEMU_KEYBOARD_W, ALL, ACTION_KEY_W },
    { FSEMU_KEYBOARD_V, ALL, ACTION_KEY_V },
    { FSEMU_KEYBOARD_X, ALL, ACTION_KEY_X },
    { FSEMU_KEYBOARD_Y, ALL, ACTION_KEY_Y },
    { FSEMU_KEYBOARD_Z, ALL, ACTION_KEY_Z },

    /* FIXME:  ID_FLAG_TOGGLE */
    { FSEMU_KEYBOARD_CAPSLOCK, ALL, ACTION_KEY_CAPSLOCK },
    { FSEMU_KEYBOARD_KP1, ALL, ACTION_KEY_KP1 },
    { FSEMU_KEYBOARD_KP2, ALL, ACTION_KEY_KP2 },
    { FSEMU_KEYBOARD_KP3, ALL, ACTION_KEY_KP3 },
    { FSEMU_KEYBOARD_KP4, ALL, ACTION_KEY_KP4 },
    { FSEMU_KEYBOARD_KP5, ALL, ACTION_KEY_KP5 },
    { FSEMU_KEYBOARD_KP6, ALL, ACTION_KEY_KP6 },
    { FSEMU_KEYBOARD_KP7, ALL, ACTION_KEY_KP7 },
    { FSEMU_KEYBOARD_KP8, ALL, ACTION_KEY_KP8 },
    { FSEMU_KEYBOARD_KP9, ALL, ACTION_KEY_KP9 },
    { FSEMU_KEYBOARD_KP0, ALL, ACTION_KEY_KP0 },
    { FSEMU_KEYBOARD_KPPERIOD, ALL, ACTION_KEY_KPPERIOD },
    { FSEMU_KEYBOARD_KPPLUS, ALL, ACTION_KEY_KPPLUS },
    { FSEMU_KEYBOARD_KPMINUS, ALL, ACTION_KEY_KPMINUS },
    { FSEMU_KEYBOARD_KPMULTIPLY, ALL, ACTION_KEY_KPMUL },
    { FSEMU_KEYBOARD_KPDIVIDE, ALL, ACTION_KEY_KPDIV },
    { FSEMU_KEYBOARD_KPENTER, ALL, ACTION_KEY_KPENTER },

    { FSEMU_KEYBOARD_MINUS, ALL, ACTION_KEY_MINUS },
    { FSEMU_KEYBOARD_EQUALS, ALL, ACTION_KEY_EQUALS },
    { FSEMU_KEYBOARD_BACKSPACE, ALL, ACTION_KEY_BACKSPACE },
    { FSEMU_KEYBOARD_RETURN, ALL, ACTION_KEY_RETURN },
    { FSEMU_KEYBOARD_SPACE, ALL, ACTION_KEY_SPACE },
    { FSEMU_KEYBOARD_LSHIFT, ALL, ACTION_KEY_LSHIFT },
    { FSEMU_KEYBOARD_RSHIFT, ALL, ACTION_KEY_RSHIFT },
    { FSEMU_KEYBOARD_LCTRL, ALL, ACTION_KEY_CTRL },

    { FSEMU_KEYBOARD_COMMA, ALL, ACTION_KEY_COMMA },
    { FSEMU_KEYBOARD_PERIOD, ALL, ACTION_KEY_PERIOD },
    { FSEMU_KEYBOARD_SLASH, ALL, ACTION_KEY_SLASH },

    { FSEMU_KEYBOARD_UP, ALL, ACTION_KEY_UP },
    { FSEMU_KEYBOARD_DOWN, ALL, ACTION_KEY_DOWN },
    { FSEMU_KEYBOARD_LEFT, ALL, ACTION_KEY_LEFT },
    { FSEMU_KEYBOARD_RIGHT, ALL, ACTION_KEY_RIGHT },

    { FSEMU_KEYBOARD_HOME, ALL, ACTION_KEY_KPLPAREN },
    { FSEMU_KEYBOARD_PAGEUP, ALL, ACTION_KEY_KPRPAREN },

    { FSEMU_KEYBOARD_DELETE, ALL, ACTION_KEY_DEL },
    { FSEMU_KEYBOARD_END, ALL, ACTION_KEY_HELP },
    { FSEMU_KEYBOARD_PAGEDOWN, ALL, ACTION_KEY_RAMIGA },
    { FSEMU_KEYBOARD_LEFTBRACKET, ALL, ACTION_KEY_LBRACKET },
    { FSEMU_KEYBOARD_RIGHTBRACKET, ALL, ACTION_KEY_RBRACKET },
    { FSEMU_KEYBOARD_SEMICOLON, ALL, ACTION_KEY_SEMICOLON },
    { FSEMU_KEYBOARD_APOSTROPHE,
      ALL,
      ACTION_KEY_HASH },  // FIXME: ACTION_KEY_SINGLEQUOTE ?
    { FSEMU_KEYBOARD_GRAVE, ALL, ACTION_KEY_BACKTICK },  // FIXME

    /* FIXME */
    { FSEMU_KEYBOARD_LGUI, ALL, ACTION_KEY_LAMIGA },
#if 0
    { FS_ML_KEY_LMETA,        ALL, INPUTEVENT_KEY_AMIGA_LEFT },
#endif
    { FSEMU_KEYBOARD_LALT, ALL, ACTION_KEY_LALT },
    { FSEMU_KEYBOARD_RALT, ALL, ACTION_KEY_LALT },
    /* FIXME */
    { FSEMU_KEYBOARD_RGUI, ALL, ACTION_KEY_RAMIGA },
#if 0
    { FS_ML_KEY_RMETA,        ALL, INPUTEVENT_KEY_AMIGA_RIGHT },
#endif
    { FSEMU_KEYBOARD_MENU, ALL, ACTION_KEY_RAMIGA },
#if 0
    { FSEMU_KEYBOARD_RCTRL,        ALL, INPUTEVENT_KEY_CTRL_RIGHT },
#endif

#if 1
    // 0x2B is the number (hash) key on some international keyboards.
    { FSEMU_KEYBOARD_INSERT, ALL, ACTION_KEY_2B },
    { FSEMU_KEYBOARD_BACKSLASH, ALL, ACTION_KEY_BACKSLASH },
#else
    { FSEMU_KEYBOARD_INSERT, ALL, INPUTEVENT_KEY_BACKSLASH },
    { FSEMU_KEYBOARD_BACKSLASH, ALL, ACTION_KEY_2B },
#endif

    // 0x30 is the key to the left of Z.
    { FSEMU_KEYBOARD_NONUSBACKSLASH, ALL, ACTION_KEY_30 },

    {
        0,
        0,
        0,
    },
};

static fsemu_input_configure_keyboard_t keyboard_shortcuts_mapping[] = {
    { FSEMU_KEYBOARD_F11, 0, FSEMU_ACTION_OSKEYBOARD },
#if 0
    { FSEMU_KEYBOARD_F12, 0, FSEMU_ACTION_OSMENU },
#endif

#if 0
    { FSEMU_KEYBOARD_A,            MOD, FSE_ACTION_CYCLE_STRETCH_MODE },
    { FSEMU_KEYBOARD_B,            MOD, FS_EMU_ACTION_ZOOM_BORDER },
    { FSEMU_KEYBOARD_C,            MOD, INPUTEVENT_SPC_FREEZEBUTTON },
    { FSEMU_KEYBOARD_D,            MOD, FS_UAE_ACTION_ENTER_DEBUGGER },
    { FSEMU_KEYBOARD_F,            MOD, FS_EMU_ACTION_FULLSCREEN },
    { FSEMU_KEYBOARD_G,            MOD, FS_EMU_ACTION_GRAB_INPUT },
    { FSEMU_KEYBOARD_K,            MOD, FS_EMU_ACTION_FULL_KEYBOARD },
    { FSEMU_KEYBOARD_M,            MOD, FS_EMU_ACTION_VOLUME_MUTE },
    { FSEMU_KEYBOARD_N,            MOD, INPUTEVENT_UAE_MUTE_FLOPPY_SOUNDS },
    { FSEMU_KEYBOARD_P,            MOD, FS_EMU_ACTION_PAUSE },
    { FSEMU_KEYBOARD_Q,            MOD, FS_EMU_ACTION_QUIT },
    { FSEMU_KEYBOARD_R,            MOD, INPUTEVENT_SPC_SOFTRESET },
    { FSEMU_KEYBOARD_S,            MOD, FS_EMU_ACTION_SCREENSHOT },
    { FSEMU_KEYBOARD_T,            MOD, INPUTEVENT_SPC_HARDRESET },
    { FSEMU_KEYBOARD_Z,            MOD, FS_EMU_ACTION_ZOOM },
    { FSEMU_KEYBOARD_X,            MOD, FS_EMU_ACTION_SPECIAL },
    { FSEMU_KEYBOARD_W,            MOD, FS_EMU_ACTION_WARP },

    // { FSEMU_KEYBOARD_1,            MOD, INPUTEVENT_SPC_RTG_C },
    // { FSEMU_KEYBOARD__2,            MOD, INPUTEVENT_SPC_RTG_0 },

#ifdef USE_NFD
    { FSEMU_KEYBOARD_F1,           MOD, FS_UAE_ACTION_DRIVE_0_BROWSE },
    { FSEMU_KEYBOARD_F2,           MOD, FS_UAE_ACTION_DRIVE_1_BROWSE },
    { FSEMU_KEYBOARD_F3,           MOD, FS_UAE_ACTION_DRIVE_2_BROWSE },
    { FSEMU_KEYBOARD_F4,           MOD, FS_UAE_ACTION_DRIVE_3_BROWSE },
#endif

    { FSEMU_KEYBOARD_F4,           MOD, FS_EMU_ACTION_QUIT },
    { FSEMU_KEYBOARD_F5,           MOD, INPUTEVENT_SPC_STATESAVE1 },
    { FSEMU_KEYBOARD_F9,           MOD, INPUTEVENT_SPC_TOGGLERTG },
    { FSEMU_KEYBOARD_F11,           -1, FS_UAE_ACTION_TOGGLE_AUTO_ZOOM },
    { FSEMU_KEYBOARD_F12,           -1, FS_EMU_ACTION_MENU_ALT },

    { FSEMU_KEYBOARD_UP,           MOD, INPUTEVENT_KEY_CURSOR_UP },
    { FSEMU_KEYBOARD_DOWN,         MOD, INPUTEVENT_KEY_CURSOR_DOWN },
    { FSEMU_KEYBOARD_LEFT,         MOD, INPUTEVENT_KEY_CURSOR_LEFT },
    { FSEMU_KEYBOARD_RIGHT,        MOD, INPUTEVENT_KEY_CURSOR_RIGHT },
    // FIXME: Mod + RALT
    // FIXME: Mod + RCTRL

    { FSEMU_KEYBOARD_AUDIOPLAY,     -1, INPUTEVENT_SPC_DISKSWAPPER_INSERT0 },
    { FSEMU_KEYBOARD_AUDIONEXT,     -1, INPUTEVENT_SPC_DISKSWAPPER_NEXT },
    { FSEMU_KEYBOARD_AUDIOPREV,     -1, INPUTEVENT_SPC_DISKSWAPPER_PREV },
    { FSEMU_KEYBOARD_COMMA,        MOD, FS_EMU_ACTION_VOLUME_DOWN },
    { FSEMU_KEYBOARD_MUTE,          -1, FS_EMU_ACTION_VOLUME_MUTE },
    { FSEMU_KEYBOARD_PAUSE,         -1, FS_EMU_ACTION_PAUSE },
    { FSEMU_KEYBOARD_PERIOD,       MOD, FS_EMU_ACTION_VOLUME_UP },
    { FSEMU_KEYBOARD_PRINT,         -1, FS_EMU_ACTION_SCREENSHOT },
    { FSEMU_KEYBOARD_RETURN,       MOD, FS_EMU_ACTION_FULLSCREEN },
    { FSEMU_KEYBOARD_TAB,          MOD, FS_EMU_ACTION_SWITCH_WINDOW },
    { FSEMU_KEYBOARD_VOLUMEDOWN,    -1, FS_EMU_ACTION_VOLUME_DOWN },
    { FSEMU_KEYBOARD_VOLUMEUP,      -1, FS_EMU_ACTION_VOLUME_UP },
#endif
    {

        0,
        0,
        0,
    },
};

void fsuae_keyboard_init(void)
{
    printf("[FSUAE] fsuae_keyboard_init\n");
    fsemu_input_configure_keyboard(keyboard_mapping);
    fsemu_input_configure_keyboard(keyboard_shortcuts_mapping);
}

// ----------------------------------------------------------------------------

#undef ALL

// ----------------------------------------------------------------------------

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <fs/emu.h>
#include <fs/emu/actions.h>
#include <uae/uae.h>

#include "fs-uae.h"

#define ALL -1
#define MOD FS_ML_KEY_MOD_SPECIAL

static fs_emu_key_translation g_default_keymap[] = {
    { FS_ML_KEY_ESCAPE, ALL, INPUTEVENT_KEY_ESC },

    { FS_ML_KEY_F1, ALL, INPUTEVENT_KEY_F1 },
    { FS_ML_KEY_F2, ALL, INPUTEVENT_KEY_F2 },
    { FS_ML_KEY_F3, ALL, INPUTEVENT_KEY_F3 },
    { FS_ML_KEY_F4, ALL, INPUTEVENT_KEY_F4 },
    { FS_ML_KEY_F5, ALL, INPUTEVENT_KEY_F5 },
    { FS_ML_KEY_F6, ALL, INPUTEVENT_KEY_F6 },
    { FS_ML_KEY_F7, ALL, INPUTEVENT_KEY_F7 },
    { FS_ML_KEY_F8, ALL, INPUTEVENT_KEY_F8 },
    { FS_ML_KEY_F9, ALL, INPUTEVENT_KEY_F9 },
    { FS_ML_KEY_F10, ALL, INPUTEVENT_KEY_F10 },

    { FS_ML_KEY_1, ALL, INPUTEVENT_KEY_1 },
    { FS_ML_KEY_2, ALL, INPUTEVENT_KEY_2 },
    { FS_ML_KEY_3, ALL, INPUTEVENT_KEY_3 },
    { FS_ML_KEY_4, ALL, INPUTEVENT_KEY_4 },
    { FS_ML_KEY_5, ALL, INPUTEVENT_KEY_5 },
    { FS_ML_KEY_6, ALL, INPUTEVENT_KEY_6 },
    { FS_ML_KEY_7, ALL, INPUTEVENT_KEY_7 },
    { FS_ML_KEY_8, ALL, INPUTEVENT_KEY_8 },
    { FS_ML_KEY_9, ALL, INPUTEVENT_KEY_9 },
    { FS_ML_KEY_0, ALL, INPUTEVENT_KEY_0 },

    { FS_ML_KEY_TAB, ALL, INPUTEVENT_KEY_TAB },

    { FS_ML_KEY_A, ALL, INPUTEVENT_KEY_A },
    { FS_ML_KEY_B, ALL, INPUTEVENT_KEY_B },
    { FS_ML_KEY_C, ALL, INPUTEVENT_KEY_C },
    { FS_ML_KEY_D, ALL, INPUTEVENT_KEY_D },
    { FS_ML_KEY_E, ALL, INPUTEVENT_KEY_E },
    { FS_ML_KEY_F, ALL, INPUTEVENT_KEY_F },
    { FS_ML_KEY_G, ALL, INPUTEVENT_KEY_G },
    { FS_ML_KEY_H, ALL, INPUTEVENT_KEY_H },
    { FS_ML_KEY_I, ALL, INPUTEVENT_KEY_I },
    { FS_ML_KEY_J, ALL, INPUTEVENT_KEY_J },
    { FS_ML_KEY_K, ALL, INPUTEVENT_KEY_K },
    { FS_ML_KEY_L, ALL, INPUTEVENT_KEY_L },
    { FS_ML_KEY_M, ALL, INPUTEVENT_KEY_M },
    { FS_ML_KEY_N, ALL, INPUTEVENT_KEY_N },
    { FS_ML_KEY_O, ALL, INPUTEVENT_KEY_O },
    { FS_ML_KEY_P, ALL, INPUTEVENT_KEY_P },
    { FS_ML_KEY_Q, ALL, INPUTEVENT_KEY_Q },
    { FS_ML_KEY_R, ALL, INPUTEVENT_KEY_R },
    { FS_ML_KEY_S, ALL, INPUTEVENT_KEY_S },
    { FS_ML_KEY_T, ALL, INPUTEVENT_KEY_T },
    { FS_ML_KEY_U, ALL, INPUTEVENT_KEY_U },
    { FS_ML_KEY_W, ALL, INPUTEVENT_KEY_W },
    { FS_ML_KEY_V, ALL, INPUTEVENT_KEY_V },
    { FS_ML_KEY_X, ALL, INPUTEVENT_KEY_X },
    { FS_ML_KEY_Y, ALL, INPUTEVENT_KEY_Y },
    { FS_ML_KEY_Z, ALL, INPUTEVENT_KEY_Z },

    /* FIXME:  ID_FLAG_TOGGLE */
    { FS_ML_KEY_CAPSLOCK, ALL, INPUTEVENT_KEY_CAPS_LOCK },

    { FS_ML_KEY_KP1, ALL, INPUTEVENT_KEY_NP_1 },
    { FS_ML_KEY_KP2, ALL, INPUTEVENT_KEY_NP_2 },
    { FS_ML_KEY_KP3, ALL, INPUTEVENT_KEY_NP_3 },
    { FS_ML_KEY_KP4, ALL, INPUTEVENT_KEY_NP_4 },
    { FS_ML_KEY_KP5, ALL, INPUTEVENT_KEY_NP_5 },
    { FS_ML_KEY_KP6, ALL, INPUTEVENT_KEY_NP_6 },
    { FS_ML_KEY_KP7, ALL, INPUTEVENT_KEY_NP_7 },
    { FS_ML_KEY_KP8, ALL, INPUTEVENT_KEY_NP_8 },
    { FS_ML_KEY_KP9, ALL, INPUTEVENT_KEY_NP_9 },
    { FS_ML_KEY_KP0, ALL, INPUTEVENT_KEY_NP_0 },
    { FS_ML_KEY_KP_PERIOD, ALL, INPUTEVENT_KEY_NP_PERIOD },
    { FS_ML_KEY_KP_PLUS, ALL, INPUTEVENT_KEY_NP_ADD },
    { FS_ML_KEY_KP_MINUS, ALL, INPUTEVENT_KEY_NP_SUB },
    { FS_ML_KEY_KP_MULTIPLY, ALL, INPUTEVENT_KEY_NP_MUL },
    { FS_ML_KEY_KP_DIVIDE, ALL, INPUTEVENT_KEY_NP_DIV },
    { FS_ML_KEY_KP_ENTER, ALL, INPUTEVENT_KEY_ENTER },

    { FS_ML_KEY_MINUS, ALL, INPUTEVENT_KEY_SUB },
    { FS_ML_KEY_EQUALS, ALL, INPUTEVENT_KEY_EQUALS },
    { FS_ML_KEY_BACKSPACE, ALL, INPUTEVENT_KEY_BACKSPACE },
    { FS_ML_KEY_RETURN, ALL, INPUTEVENT_KEY_RETURN },
    { FS_ML_KEY_SPACE, ALL, INPUTEVENT_KEY_SPACE },

    { FS_ML_KEY_LSHIFT, ALL, INPUTEVENT_KEY_SHIFT_LEFT },
    { FS_ML_KEY_LCTRL, ALL, INPUTEVENT_KEY_CTRL },
    /* FIXME */
    { FS_ML_KEY_LSUPER, ALL, INPUTEVENT_KEY_AMIGA_LEFT },
#if 0
    { FS_ML_KEY_LMETA,        ALL, INPUTEVENT_KEY_AMIGA_LEFT },
#endif
    { FS_ML_KEY_LALT, ALL, INPUTEVENT_KEY_ALT_LEFT },
    { FS_ML_KEY_RALT, ALL, INPUTEVENT_KEY_ALT_RIGHT },
    /* FIXME */
    { FS_ML_KEY_RSUPER, ALL, INPUTEVENT_KEY_AMIGA_RIGHT },
#if 0
    { FS_ML_KEY_RMETA,        ALL, INPUTEVENT_KEY_AMIGA_RIGHT },
#endif
    { FS_ML_KEY_MENU, ALL, INPUTEVENT_KEY_AMIGA_RIGHT },
#if 0
    { FS_ML_KEY_RCTRL,        ALL, INPUTEVENT_KEY_CTRL_RIGHT },
#endif
    { FS_ML_KEY_RSHIFT, ALL, INPUTEVENT_KEY_SHIFT_RIGHT },

    { FS_ML_KEY_UP, ALL, INPUTEVENT_KEY_CURSOR_UP },
    { FS_ML_KEY_DOWN, ALL, INPUTEVENT_KEY_CURSOR_DOWN },
    { FS_ML_KEY_LEFT, ALL, INPUTEVENT_KEY_CURSOR_LEFT },
    { FS_ML_KEY_RIGHT, ALL, INPUTEVENT_KEY_CURSOR_RIGHT },

#if 1
    /* 0x2B is the number (hash) key on some international keyboards. */
    { FS_ML_KEY_INSERT, ALL, INPUTEVENT_KEY_2B },
#else
    { FS_ML_KEY_INSERT, ALL, INPUTEVENT_KEY_BACKSLASH },
#endif

    { FS_ML_KEY_HOME, ALL, INPUTEVENT_KEY_NP_LPAREN },
    { FS_ML_KEY_PAGEUP, ALL, INPUTEVENT_KEY_NP_RPAREN },

    { FS_ML_KEY_DELETE, ALL, INPUTEVENT_KEY_DEL },
    { FS_ML_KEY_END, ALL, INPUTEVENT_KEY_HELP },
    { FS_ML_KEY_PAGEDOWN, ALL, INPUTEVENT_KEY_AMIGA_RIGHT },

    { FS_ML_KEY_LEFTBRACKET, ALL, INPUTEVENT_KEY_LEFTBRACKET },
    { FS_ML_KEY_RIGHTBRACKET, ALL, INPUTEVENT_KEY_RIGHTBRACKET },
    { FS_ML_KEY_SEMICOLON, ALL, INPUTEVENT_KEY_SEMICOLON },
    { FS_ML_KEY_QUOTE, ALL, INPUTEVENT_KEY_SINGLEQUOTE },
    { FS_ML_KEY_BACKQUOTE, ALL, INPUTEVENT_KEY_BACKQUOTE },

#if 1
    { FS_ML_KEY_BACKSLASH, ALL, INPUTEVENT_KEY_BACKSLASH },
#else
    { FS_ML_KEY_BACKSLASH, ALL, INPUTEVENT_KEY_2B },
#endif

    { FS_ML_KEY_COMMA, ALL, INPUTEVENT_KEY_COMMA },
    { FS_ML_KEY_PERIOD, ALL, INPUTEVENT_KEY_PERIOD },
    { FS_ML_KEY_SLASH, ALL, INPUTEVENT_KEY_DIV },

    /* 0x30 is the key to the left of Z. */
    { FS_ML_KEY_LESS, ALL, INPUTEVENT_KEY_30 },

    // FIXME: international key??
    //{ DIK_OEM_102, ALL, INPUTEVENT_KEY_30 },

    // FIXME:

    //{ INPUTEVENT_KEY_30, ALL, INPUTEVENT_KEY_30 },
    //{ INPUTEVENT_SPC_MASTER_VOLUME_DOWN, ALL,
    // INPUTEVENT_SPC_MASTER_VOLUME_DOWN }, { INPUTEVENT_SPC_MASTER_VOLUME_UP,
    // ALL, INPUTEVENT_SPC_MASTER_VOLUME_UP }, {
    // INPUTEVENT_SPC_MASTER_VOLUME_MUTE, ALL,
    // INPUTEVENT_SPC_MASTER_VOLUME_MUTE
    //}, { INPUTEVENT_KEY_70, ALL, INPUTEVENT_KEY_70 }, { INPUTEVENT_KEY_71,
    // ALL, INPUTEVENT_KEY_71 },
    //    { DIK_SYSRQ, ALL, INPUTEVENT_KEY_6E },
    //    { DIK_F12, ALL, INPUTEVENT_KEY_6F },
    //{ INPUTEVENT_KEY_47, ALL, INPUTEVENT_KEY_47 },
    //    { DIK_PRIOR, ALL, INPUTEVENT_KEY_48 },
    //{ INPUTEVENT_SPC_FREEZEBUTTON, ALL, INPUTEVENT_SPC_FREEZEBUTTON },
    //{ INPUTEVENT_KEY_49, ALL, INPUTEVENT_KEY_49 },
    //{ INPUTEVENT_KEY_4B, ALL, INPUTEVENT_KEY_4B },

    //{ INPUTEVENT_KEY_CDTV_STOP, ALL, INPUTEVENT_KEY_CDTV_STOP },
    //{ INPUTEVENT_KEY_CDTV_PLAYPAUSE, ALL, INPUTEVENT_KEY_CDTV_PLAYPAUSE },
    //{ INPUTEVENT_KEY_CDTV_PREV, ALL, INPUTEVENT_KEY_CDTV_PREV },
    //{ INPUTEVENT_KEY_CDTV_NEXT, ALL, INPUTEVENT_KEY_CDTV_NEXT },

    // { FS_ML_KEY_F, FS_ML_KEY_MOD_LALT, FS_EMU_ACTION_FULLSCREEN },

    { FS_ML_KEY_A, MOD, FSE_ACTION_CYCLE_STRETCH_MODE },
    { FS_ML_KEY_B, MOD, FS_EMU_ACTION_ZOOM_BORDER },
    { FS_ML_KEY_C, MOD, INPUTEVENT_SPC_FREEZEBUTTON },
    { FS_ML_KEY_D, MOD, FS_UAE_ACTION_ENTER_DEBUGGER },
    { FS_ML_KEY_F, MOD, FS_EMU_ACTION_FULLSCREEN },
    { FS_ML_KEY_G, MOD, FS_EMU_ACTION_GRAB_INPUT },
    { FS_ML_KEY_K, MOD, FS_EMU_ACTION_FULL_KEYBOARD },
    { FS_ML_KEY_M, MOD, FS_EMU_ACTION_VOLUME_MUTE },
    { FS_ML_KEY_N, MOD, INPUTEVENT_UAE_MUTE_FLOPPY_SOUNDS },
    { FS_ML_KEY_P, MOD, FS_EMU_ACTION_PAUSE },
    { FS_ML_KEY_Q, MOD, FS_EMU_ACTION_QUIT },
    { FS_ML_KEY_R, MOD, INPUTEVENT_SPC_SOFTRESET },
    { FS_ML_KEY_S, MOD, FS_EMU_ACTION_SCREENSHOT },
    { FS_ML_KEY_T, MOD, INPUTEVENT_SPC_HARDRESET },
    { FS_ML_KEY_Z, MOD, FS_EMU_ACTION_ZOOM },
    { FS_ML_KEY_X, MOD, FS_EMU_ACTION_SPECIAL },
    { FS_ML_KEY_W, MOD, FS_EMU_ACTION_WARP },

// { FS_ML_KEY_1,            MOD, INPUTEVENT_SPC_RTG_C },
// { FS_ML_KEY_2,            MOD, INPUTEVENT_SPC_RTG_0 },

#ifdef USE_NFD
    { FS_ML_KEY_F1, MOD, FS_UAE_ACTION_DRIVE_0_BROWSE },
    { FS_ML_KEY_F2, MOD, FS_UAE_ACTION_DRIVE_1_BROWSE },
    { FS_ML_KEY_F3, MOD, FS_UAE_ACTION_DRIVE_2_BROWSE },
    { FS_ML_KEY_F4, MOD, FS_UAE_ACTION_DRIVE_3_BROWSE },
#endif

    { FS_ML_KEY_F4, MOD, FS_EMU_ACTION_QUIT },
    { FS_ML_KEY_F5, MOD, INPUTEVENT_SPC_STATESAVE1 },
    { FS_ML_KEY_F9, MOD, INPUTEVENT_SPC_TOGGLERTG },
    { FS_ML_KEY_F11, -1, FS_UAE_ACTION_TOGGLE_AUTO_ZOOM },
    { FS_ML_KEY_F12, -1, FS_EMU_ACTION_MENU_ALT },

    { FS_ML_KEY_UP, MOD, INPUTEVENT_KEY_CURSOR_UP },
    { FS_ML_KEY_DOWN, MOD, INPUTEVENT_KEY_CURSOR_DOWN },
    { FS_ML_KEY_LEFT, MOD, INPUTEVENT_KEY_CURSOR_LEFT },
    { FS_ML_KEY_RIGHT, MOD, INPUTEVENT_KEY_CURSOR_RIGHT },

    { FS_ML_KEY_AUDIOPLAY, -1, INPUTEVENT_SPC_DISKSWAPPER_INSERT0 },
    { FS_ML_KEY_AUDIONEXT, -1, INPUTEVENT_SPC_DISKSWAPPER_NEXT },
    { FS_ML_KEY_AUDIOPREV, -1, INPUTEVENT_SPC_DISKSWAPPER_PREV },
    { FS_ML_KEY_COMMA, MOD, FS_EMU_ACTION_VOLUME_DOWN },
    { FS_ML_KEY_MUTE, -1, FS_EMU_ACTION_VOLUME_MUTE },
    { FS_ML_KEY_PAUSE, -1, FS_EMU_ACTION_PAUSE },
    { FS_ML_KEY_PERIOD, MOD, FS_EMU_ACTION_VOLUME_UP },
    { FS_ML_KEY_PRINT, -1, FS_EMU_ACTION_SCREENSHOT },
    { FS_ML_KEY_RETURN, MOD, FS_EMU_ACTION_FULLSCREEN },
    { FS_ML_KEY_TAB, MOD, FS_EMU_ACTION_SWITCH_WINDOW },
    { FS_ML_KEY_VOLUMEDOWN, -1, FS_EMU_ACTION_VOLUME_DOWN },
    { FS_ML_KEY_VOLUMEUP, -1, FS_EMU_ACTION_VOLUME_UP },

    { 0, 0, 0 } /* Sentinel */
};

void fs_uae_map_keyboard(void)
{
    fs_emu_set_keyboard_translation(g_default_keymap);
}
