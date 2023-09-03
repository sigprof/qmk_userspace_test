// Copyright 2023 Sergey Vlasov <sigprof@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _QWERTY,
    _NUMPAD,
    _FN,
    _FN_CTL,
    _ADJUST,
};

enum custom_keycodes {
    U_LSW = QK_USER, // Language switch key (intended to be modified by Shift)
    U_LSWM0,         // Set language switch mode 0 (Caps Lock)
    U_LSWM1,         // Set language switch mode 1 (Ctrl+F15)
    U_LSFTL,         // Left Shift with language switch on double tap
    U_RSFTL,         // Right Shift with language switch on double tap
};

enum tap_dance_ids {
    TD_RALT, // Right Alt combined with Right GUI
    TD_RCTL, // MO(_FN) combined with App on tap and Right Ctrl
    TD_LSFT, // Left Shift with language switch on double tap
    TD_RSFT, // Right Shift with language switch on double tap
};

typedef union {
    uint32_t raw;
    struct {
        uint32_t lang_switch_mode : 1;
    };
} user_config_t;

static user_config_t user_config;

#define U_FESC LT(_FN, KC_ESC)
#define U_TRALT TD(TD_RALT)
#define U_TRCTL TD(TD_RCTL)
#define U_NBSLS LT(_NUMPAD, KC_BSLS)
#define U_MOADJ MO(_ADJUST)
#define U_TGNUM TG(_NUMPAD)
#define U_OSRGU OSM(MOD_RGUI)
#define U_OSRCT OSM(MOD_RCTL)
#define U_CPGUP RCTL(KC_PGUP)
#define U_CPGDN RCTL(KC_PGDN)
#define U_FNCTL LM(_FN_CTL, MOD_LCTL)
#define U_TLSFT TD(TD_LSFT)
#define U_TRSFT TD(TD_RSFT)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │Ins│Del│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ Bsp │PgU│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │EscFn │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │PgD│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │ ShiftL │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ShiftL│ ↑ │TRC│
     * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬─┬───┼───┼───┤
     * │Ctrl │GUI│Alt  │                           │TRAlt│ │ ← │ ↓ │ → │
     * └─────┴───┴─────┴───────────────────────────┴─────┘ └───┴───┴───┘
     */
    [_QWERTY] = LAYOUT_65_ansi_blocker_tsangan_split_bs(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  U_NBSLS, KC_INS,  KC_DEL,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,      KC_PGUP,
        U_FESC,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,              KC_PGDN,
        U_TLSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, U_TRSFT,        KC_UP,   U_TRCTL,
        KC_LCTL,     KC_LGUI, KC_LALT,                                 KC_SPC,                             U_TRALT,          KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │P0 │P1 │P2 │P3 │P4 │P5 │P6 │P7 │P8 │P9 │P0 │P- │P+ │   │   │   │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
     * │     │   │   │   │   │   │   │P4 │P5 │P6 │P* │PEn│Num│     │   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │      │   │   │   │   │   │   │P1 │P2 │P3 │P+ │P* │ PEnter │   │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │        │   │   │   │   │   │   │P0 │P, │P. │P/ │      │   │   │
     * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬─┬───┼───┼───┤
     * │     │   │     │                           │     │ │   │   │   │
     * └─────┴───┴─────┴───────────────────────────┴─────┘ └───┴───┴───┘
     */
    [_NUMPAD] = LAYOUT_65_ansi_blocker_tsangan_split_bs(
        KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_PMNS, KC_PPLS, _______, _______, _______,
        _______,     _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PAST, KC_PENT, KC_NUM,  _______,      _______,
        _______,       _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, KC_PAST, KC_PENT,             _______,
        _______,            _______, _______, _______, _______, _______, _______, KC_P0,   KC_PCMM, KC_PDOT, KC_PSLS, _______,        _______, _______,
        _______,     _______, _______,                                 _______,                            _______,          _______, _______, _______
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ ` │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│TgN│Hom│End│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
     * │LngSw│MB1│Ms↑│MB2│Wh↑│DM1│Ins│Hom│ ↑ │End│PgU│V+ │Mut│ Del │CPU│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │Caps  │Ms←│Ms↓│Ms→│Wh↓│DM2│Del│ ← │ ↓ │ → │PgD│V- │ PEnter │CPD│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │        │MB3│MB4│MB5│Wh←│Wh→│PSc│ScL│Pau│ORG│ORC│      │PgU│   │
     * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬─┬───┼───┼───┤
     * │FnCtl│   │     │        MO(_ADJUST)        │     │ │Hom│PgD│End│
     * └─────┴───┴─────┴───────────────────────────┴─────┘ └───┴───┴───┘
     */
    [_FN] = LAYOUT_65_ansi_blocker_tsangan_split_bs(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  U_TGNUM, KC_HOME, KC_END,
        U_LSW,       KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, DM_PLY1, KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_VOLU, KC_MUTE, KC_DEL,       U_CPGUP,
        KC_CAPS,       KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, DM_PLY2, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_VOLD, KC_PENT,             U_CPGDN,
        _______,            KC_BTN3, KC_BTN4, KC_BTN5, KC_WH_L, KC_WH_R, KC_PSCR, KC_SCRL, KC_PAUS, U_OSRGU, U_OSRCT, _______,        KC_PGUP, _______,
        U_FNCTL,     _______, _______,                                 U_MOADJ,                            _______,          KC_HOME, KC_PGDN, KC_END
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │DRS│   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
     * │     │   │   │   │   │DR1│   │   │   │   │   │   │   │     │   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │      │   │   │   │   │DR2│   │   │   │   │   │   │        │   │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │        │   │   │   │   │   │   │   │   │   │   │      │   │   │
     * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬─┬───┼───┼───┤
     * │     │   │     │                           │     │ │   │   │   │
     * └─────┴───┴─────┴───────────────────────────┴─────┘ └───┴───┴───┘
     */
    [_FN_CTL] = LAYOUT_65_ansi_blocker_tsangan_split_bs(
        DM_RSTP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,     _______, _______, _______, _______, DM_REC1, _______, _______, _______, _______, _______, _______, _______, _______,      _______,
        _______,       _______, _______, _______, _______, DM_REC2, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______, _______,
        _______,     _______, _______,                                 _______,                            _______,          _______, _______, _______
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │BLd│LS0│LS1│   │   │   │   │   │   │   │   │NKT│Dbg│   │   │Rst│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
     * │     │BTg│BL-│BL+│BBr│   │   │   │   │   │   │NK-│NK+│EEClr│   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │      │RTg│RM+│Hu+│Sa+│Va+│Sp+│   │   │   │   │   │        │   │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │        │RMP│RM-│Hu-│Sa-│Va-│Sp-│   │   │   │   │      │   │   │
     * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬─┬───┼───┼───┤
     * │     │   │     │                           │     │ │   │   │   │
     * └─────┴───┴─────┴───────────────────────────┴─────┘ └───┴───┴───┘
     */
    [_ADJUST] = LAYOUT_65_ansi_blocker_tsangan_split_bs(
        QK_BOOT, U_LSWM0, U_LSWM1, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NK_TOGG, DB_TOGG, XXXXXXX, XXXXXXX, QK_RBT,
        XXXXXXX,     BL_TOGG, BL_DOWN, BL_UP,   BL_BRTG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NK_OFF,  NK_ON,   EE_CLR,       XXXXXXX,
        _______,       RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX,
        _______,            RGB_M_P, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,        XXXXXXX, _______,
        _______,     _______, _______,                                 _______,                            _______,          XXXXXXX, XXXXXXX, XXXXXXX
    ),

    /*
    [_] = LAYOUT_65_ansi_blocker_tsangan_split_bs(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,
        _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______, _______,
        _______,     _______, _______,                                 _______,                            _______,          _______, _______, _______
    ),
    */
};
// clang-format on

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case U_FESC:
            return true;

        default:
            return false;
    }
}

// Tap dance for the “Right Alt” key:
// - hold: KC_RALT
// - tap: KC_RALT
// - tap and hold: KC_RGUI
// - double tap: KC_RGUI
// - double tap and hold: KC_RGUI+KC_RALT
// - triple tap: KC_RGUI+KC_RALT
enum td_ralt_state {
    TD_RALT_NOOP,
    TD_RALT_RALT,
    TD_RALT_RGUI,
    TD_RALT_RGUI_RALT,
};

static enum td_ralt_state td_ralt_state;

static void td_ralt_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            td_ralt_state = TD_RALT_RALT;
            break;
        case 2:
            td_ralt_state = TD_RALT_RGUI;
            break;
        case 3:
            td_ralt_state = TD_RALT_RGUI_RALT;
            break;
        default:
            td_ralt_state = TD_RALT_NOOP;
            break;
    }

    switch (td_ralt_state) {
        case TD_RALT_NOOP:
            break;
        case TD_RALT_RALT:
            register_code(KC_RALT);
            break;
        case TD_RALT_RGUI:
            register_code(KC_RGUI);
            break;
        case TD_RALT_RGUI_RALT:
            register_code(KC_RGUI);
            register_code(KC_RALT);
            break;
    }
}

static void td_ralt_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_ralt_state) {
        case TD_RALT_NOOP:
            break;
        case TD_RALT_RALT:
            unregister_code(KC_RALT);
            break;
        case TD_RALT_RGUI:
            unregister_code(KC_RGUI);
            break;
        case TD_RALT_RGUI_RALT:
            unregister_code(KC_RALT);
            unregister_code(KC_RGUI);
            break;
    }
}

// Tap dance for the “Right Ctrl” key:
// - hold: MO(_FN)
// - tap: KC_APP
// - tap and hold: KC_RCTL
// - double tap: KC_RCTL
// - double tap and hold: KC_APP
// - triple tap: KC_APP
enum td_rctl_state {
    TD_RCTL_NOOP,
    TD_RCTL_MO_FN,
    TD_RCTL_APP,
    TD_RCTL_RCTL,
};

static enum td_rctl_state td_rctl_state;

static void td_rctl_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            if (state->pressed) {
                td_rctl_state = TD_RCTL_MO_FN;
            } else {
                td_rctl_state = TD_RCTL_APP;
            };
            break;
        case 2:
            td_rctl_state = TD_RCTL_RCTL;
            break;
        case 3:
            td_rctl_state = TD_RCTL_APP;
            break;
        default:
            td_rctl_state = TD_RCTL_NOOP;
            break;
    }

    switch (td_rctl_state) {
        case TD_RCTL_NOOP:
            break;
        case TD_RCTL_MO_FN:
            layer_on(_FN);
            break;
        case TD_RCTL_APP:
            register_code(KC_APP);
            break;
        case TD_RCTL_RCTL:
            register_code(KC_RCTL);
            break;
    }
}

static void td_rctl_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_rctl_state) {
        case TD_RCTL_NOOP:
            break;
        case TD_RCTL_MO_FN:
            layer_off(_FN);
            break;
        case TD_RCTL_APP:
            unregister_code(KC_APP);
            break;
        case TD_RCTL_RCTL:
            unregister_code(KC_RCTL);
            break;
    }
}

static uint16_t get_lsw_keycode(void) {
    switch (user_config.lang_switch_mode) {
        case 0:
        default:
            return KC_CAPS;

        case 1:
            return C(KC_F15);
    }
}

static void td_lang_shift_on_each_tap(tap_dance_state_t *state, void *user_data) {
    // Clear any captured modifier state which ends up including the just
    // registered Shift modifier, otherwise that state will be applied before
    // calling the `finished` handler.
    state->weak_mods    = 0;
    state->oneshot_mods = 0;
}

static void td_lang_shift_finished(tap_dance_state_t *state, uint16_t lsw_keycode) {
    // If this was a clean double tap, send the language switch keycode.
    if (state->count == 2 && !state->pressed) {
        tap_code16(lsw_keycode);
    }
}

static void td_lsft_finished(tap_dance_state_t *state, void *user_data) {
    td_lang_shift_finished(state, get_lsw_keycode());
}

static void td_rsft_finished(tap_dance_state_t *state, void *user_data) {
    td_lang_shift_finished(state, RSFT(get_lsw_keycode()));
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_RALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_ralt_finished, td_ralt_reset),
    [TD_RCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_rctl_finished, td_rctl_reset),
    [TD_LSFT] = ACTION_TAP_DANCE_FN_ADVANCED(td_lang_shift_on_each_tap, td_lsft_finished, NULL),
    [TD_RSFT] = ACTION_TAP_DANCE_FN_ADVANCED(td_lang_shift_on_each_tap, td_rsft_finished, NULL),
};

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
}

enum td_mod_lsw_state {
    TD_MOD_LSW_NOOP,
    TD_MOD_LSW_MOD,
    TD_MOD_LSW_LSW,
};

struct td_mod_lsw_data {
    enum td_mod_lsw_state state;
};

struct td_mod_lsw_global_data {
    uint16_t td_kc;
    uint16_t time;
    uint8_t  tap_count;
};

struct td_mod_lsw_global_data td_mod_lsw;

static void td_mod_lsw_handle(bool pressed, uint16_t mod_kc, uint16_t lsw_kc, struct td_mod_lsw_data *data) {
    if (pressed) {
        switch (td_mod_lsw.tap_count) {
            case 1:
                data->state = TD_MOD_LSW_MOD;
                break;
            case 2:
                data->state          = TD_MOD_LSW_LSW;
                td_mod_lsw.tap_count = 0;
                break;
            default:
                data->state = TD_MOD_LSW_NOOP;
                break;
        }
    }

    uint16_t kc;
    switch (data->state) {
        case TD_MOD_LSW_NOOP:
            kc = KC_NO;
            break;
        case TD_MOD_LSW_MOD:
            kc = mod_kc;
            break;
        case TD_MOD_LSW_LSW:
            kc = lsw_kc;
            break;
    }
    if (pressed) {
        register_code16(kc);
    } else {
        unregister_code16(kc);
    }
}

static void process_td_mod_lsw(uint16_t td_kc, bool pressed, uint16_t mod_kc, uint16_t lsw_kc, struct td_mod_lsw_data *data) {
    if (pressed) {
        td_mod_lsw.td_kc = td_kc;
        if (td_mod_lsw.tap_count > 0) {
            if (timer_elapsed(td_mod_lsw.time) > TAPPING_TERM) {
                td_mod_lsw.tap_count = 0;
            }
        }
        td_mod_lsw.time = timer_read();
        td_mod_lsw.tap_count++;
    }
    td_mod_lsw_handle(pressed, mod_kc, lsw_kc, data);
}

static struct td_mod_lsw_data u_lsftl_data;
static struct td_mod_lsw_data u_rsftl_data;

static bool process_record_td_mod_lsw(uint16_t keycode, keyrecord_t *record) {
    if ((td_mod_lsw.td_kc != KC_NO) && (keycode != td_mod_lsw.td_kc)) {
        td_mod_lsw.td_kc     = KC_NO;
        td_mod_lsw.tap_count = 0;
    }
    switch (keycode) {
        case U_LSFTL:
            process_td_mod_lsw(keycode, record->event.pressed, KC_LSFT, get_lsw_keycode(), &u_lsftl_data);
            break;
        case U_RSFTL:
            process_td_mod_lsw(keycode, record->event.pressed, KC_RSFT, S(get_lsw_keycode()), &u_rsftl_data);
            break;
    }
    return true;
}

#ifdef CONSOLE_ENABLE
static uint16_t last_keycode;
static uint16_t last_keycode_timestamps[4];
static uint8_t last_keycode_index;

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == last_keycode) {
        if (last_keycode_index == ARRAY_SIZE(last_keycode_timestamps)) {
            --last_keycode_index;
            memmove(last_keycode_timestamps, last_keycode_timestamps + 1, sizeof(last_keycode_timestamps) - sizeof(last_keycode_timestamps[0]));
        }
        last_keycode_timestamps[last_keycode_index++] = timer_read();
        if (last_keycode_index >= 3) {
            uprintf("chatter(%u, %u):", (unsigned)keycode, (unsigned)record->event.pressed);
            for (uint8_t i = 1; i < last_keycode_index; ++i) {
                uprintf(" %u", (unsigned)(uint16_t)(last_keycode_timestamps[i] - last_keycode_timestamps[i-1]));
            }
            uprintf("\n");
        }
    } else {
        last_keycode = keycode;
        last_keycode_timestamps[0] = timer_read();
        last_keycode_index = 1;
    }
    return true;
}
#endif /* CONSOLE_ENABLE */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_td_mod_lsw(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case U_LSW:
            if (record->event.pressed) {
                register_code16(get_lsw_keycode());
            } else {
                unregister_code16(get_lsw_keycode());
            }
            return false;

        case U_LSWM0:
            if (record->event.pressed) {
                user_config.lang_switch_mode = 0;
                eeconfig_update_user(user_config.raw);
            }
            return false;

        case U_LSWM1:
            if (record->event.pressed) {
                user_config.lang_switch_mode = 1;
                eeconfig_update_user(user_config.raw);
            }
            return false;

        case U_TLSFT:
            // This is actually a tap dance keycode; make it also register the
            // left Shift keycode immediately (this is impossible to implement
            // using just the Tap Dance feature currently, because there is no
            // callback that is called on every release of the tap dance key).
            if (record->event.pressed) {
                register_code(KC_LSFT);
            } else {
                unregister_code(KC_LSFT);
            }
            return true; // Pass the keycode to the tap dance handler.

        case U_TRSFT:
            // Same as above, but for the right Shift.
            if (record->event.pressed) {
                register_code(KC_RSFT);
            } else {
                unregister_code(KC_RSFT);
            }
            return true; // Pass the keycode to the tap dance handler.

        default:
            return true;
    }
}

/* vim:set sw=4 sta et: */
