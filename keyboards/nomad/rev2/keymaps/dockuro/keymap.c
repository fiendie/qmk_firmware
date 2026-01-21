/* Copyright 2024 Andreas Tacke
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define MY_SBRO ALGR(KC_LBRC)
#define MY_SBRC ALGR(KC_RBRC)
#define MY_CBRO RSA(KC_LBRC)
#define MY_CBRC RSA(KC_RBRC)
#define MY_AT ALGR(KC_SCLN)
#define MY_HASH ALGR(KC_QUOT)

#include QMK_KEYBOARD_H
#include "suspend.h"
#include "gpio.h"
#include "bitmaps.h"
#include "ledmap.h"

extern rgb_config_t rgb_matrix_config;

enum layers {
    BASE,
    SYMBOLS,
    MEDIA_FN,
    KB_SETTINGS
};

/*
enum {
    LGUI_LBRC,
    LALT_LCBR,
    SPC_ENT,
    CT_CLN
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [LGUI_LBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, ALGR(KC_LBRC)),
    [LALT_LCBR] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, RSA(KC_LBRC)),
    [SPC_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT),
    [CT_CLN] = ACTION_TAP_DANCE_TAP_HOLD(KC_COLN, KC_SCLN),
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            QK_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    MY_SBRO,                        MY_SBRC, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        // +--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    MY_CBRO,                        MY_CBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,
        // +--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            KC_NUBS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME,                        KC_END,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_SLSH,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
			SC_LSPO,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_DEL,       KC_ENT,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   SC_RSPC,
        // +--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            KC_LCTL,  MO(3),   MO(2),   KC_LGUI, KC_LALT,                   KC_SPC,       KC_SPC,                    MO(1),   KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
        // `--------+--------+--------+--------+--------+--------+--------+--------'    `--------+--------+--------+--------+--------+--------+--------+--------'
    ),

    [SYMBOLS] = LAYOUT( // greens
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            _______, _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______, _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            _______, _______, _______, KC_LBRC, _______, _______, _______,                        _______, _______, KC_BSLS, KC_EQL,  KC_SCLN, _______, _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            XXXXXXX, KC_QUOT, _______, _______, KC_TILD, KC_NUHS, _______,                        _______, _______, _______, _______, _______, _______, _______,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
            _______, MY_AT,   MY_HASH,S(KC_EQL),KC_RBRC, KC_MINS,         S(KC_BSLS),     _______,          _______,_______, _______, _______, KC_PGUP, _______,
        // |--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, XXXXXXX, _______, _______,                  S(KC_SCLN),     _______,                  _______, _______, KC_HOME, KC_PGDN, KC_END
        // `--------+--------+--------+--------+--------+--------+--------+--------'    `--------+--------+--------+--------+--------+--------+--------+--------'
    ),

    [MEDIA_FN] = LAYOUT( // blues
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                          KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            _______, MS_BTN1, MS_UP,   MS_BTN2, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            XXXXXXX, MS_LEFT, MS_DOWN, MS_RGHT, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, KC_P4,   KC_P5,   KC_P6,   KC_PAST,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
            _______, MS_WHLL, MS_BTN3, MS_WHLR, XXXXXXX, XXXXXXX,          KC_MUTE,      KC_MPRV,          XXXXXXX, XXXXXXX, KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        // |--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, _______, _______, _______,                   KC_MPLY,      KC_MNXT,                   XXXXXXX, KC_P0,   KC_PDOT, KC_PENT, KC_PPLS
        // `--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------'
    ),

    [KB_SETTINGS] = LAYOUT( // reds
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        KC_BRIU, XXXXXXX, RM_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            _______, QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        KC_BRID, XXXXXXX, RM_PREV, RM_NEXT, XXXXXXX, XXXXXXX, KC_SLEP,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            EE_CLR,  QK_RBT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, RM_HUED, RM_HUEU, XXXXXXX, XXXXXXX, KC_WAKE,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
            _______, DB_TOGG, XXXXXXX, XXXXXXX, KC_WHOM, XXXXXXX,          GU_TOGG,      XXXXXXX,          XXXXXXX, RM_SATD, RM_SATU, XXXXXXX, XXXXXXX, _______,
        // |--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            _______, _______, XXXXXXX, _______, KC_MYCM,                   AS_TOGG,      XXXXXXX,                   RM_VALD, RM_VALU, XXXXXXX, XXXXXXX, XXXXXXX
        // `--------+--------+--------+--------+--------+--------+--------+--------'    `--------+--------+--------+--------+--------+--------+--------+--------'
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] =        { ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [SYMBOLS] =     { ENCODER_CCW_CW(KC_RIGHT, KC_LEFT), ENCODER_CCW_CW(KC_UP, KC_DOWN)   },
    [MEDIA_FN] =    { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(MS_WHLL, MS_WHLR) },
    [KB_SETTINGS] = { ENCODER_CCW_CW(RM_SPDU, RM_SPDD),  ENCODER_CCW_CW(RM_VALD, RM_VALU) },
};

void keyboard_pre_init_user(void) {
    // Disable Liatris power LED
    gpio_set_pin_output(24);
    gpio_write_pin_high(24);
}

void suspend_power_down_user(void) {
    rgb_matrix_disable_noeeprom();
    oled_off();
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_enable_noeeprom();
    oled_on();
}

void render_logo (void) {
    oled_write_raw_P(nomad_logo, sizeof(nomad_logo));
}

void render_layer_state (void) {
    oled_set_cursor(0, 10);
    int state = get_highest_layer(layer_state);
    switch (state) {
        case 0:
            oled_write_raw_P(base_layer, sizeof(base_layer));
            break;
        case 1:
            oled_write_raw_P(symbols_layer, sizeof(symbols_layer));
            break;
        case 2:
            oled_write_raw_P(media_layer, sizeof(media_layer));
            break;
        case 3:
            oled_write_raw_P(settings_layer, sizeof(settings_layer));
            break;
    }
}

void render_kuro_logo (void) {
    oled_set_cursor(0, 10);
    oled_write_raw_P(kuro_icon, sizeof(kuro_icon));
}

bool oled_task_user(void) {
    oled_clear();

    render_logo();

    if (is_keyboard_master()) {
        render_kuro_logo();
    } else {
        render_layer_state();
        oled_scroll_left();
    }

    return false;
}

void oled_render_boot(bool bootloader) {
    oled_clear();
    for (int i = 0; i < 16; i+=4) {
        oled_set_cursor(0, i);
        if (bootloader) {
            oled_write_raw_P(skull, sizeof(skull));
        } else {
            oled_write_P(PSTR("Rebooting "), false);
        }
    }

    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    if (jump_to_bootloader) {
        rgb_matrix_set_color_all(RGB_RED);
        rgb_matrix_update_pwm_buffers();
    }
    oled_render_boot(jump_to_bootloader);
    return false;
}

void set_layer_color(int layer) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer-1][i][0]),
            .s = pgm_read_byte(&ledmap[layer-1][i][1]),
            .v = pgm_read_byte(&ledmap[layer-1][i][2]),
        };

        if (!hsv.h && !hsv.s && !hsv.v) {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
        else {
            rgb_t rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

bool rgb_matrix_indicators_user(void) {
    int state = biton32(layer_state);
    if (state == 0) {
        rgb_matrix_enable();
    } else {
        set_layer_color(state);
    }
    return true;
}

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
}

// necessary with layouts differents from en_US as the keys are different
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_SLSH:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

/*
#pragma region TapDance

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    uint8_t mod = mod_config(QK_MOD_TAP_GET_MODS(keycode));
    if (mod) {
        return TAPPING_TERM;
    }
    return 0;
}

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold)                                        \
    {                                                                               \
        .fn        = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, \
        .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}),               \
    }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;
    tap_dance_state_t* state;

    switch (keycode) {
        case TD(CT_CLN):
            action = tap_dance_get(QK_TAP_DANCE_GET_INDEX(keycode));
            state = tap_dance_get_state(QK_TAP_DANCE_GET_INDEX(keycode));
            if (!record->event.pressed && state != NULL && state->count && !state->finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
    }
    return true;
}

#pragma endregion
*/
