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


#include QMK_KEYBOARD_H
#include "transactions.h"
#include "suspend.h"
#include "gpio.h"
#include "bitmaps.h"
#include "ledmap.h"
#include "my_keys.h"

extern rgb_config_t rgb_matrix_config;

enum layers {
    BASE,
    SYMBOLS,
    MEDIA_FN,
    KB_SETTINGS
};

typedef struct led_state_t {
    bool auto_shift_state;
    bool gui_key_state;
} led_state_t;

static led_state_t led_state;

enum tapdances{
  T3_SB = 0,
  T2_CB,
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

td_state_t cur_dance(tap_dance_state_t *state);

void t3_sb_finished(tap_dance_state_t *state, void *user_data);
void t3_sb_reset(tap_dance_state_t *state, void *user_data);
void t2_cb_finished(tap_dance_state_t *state, void *user_data);
void t2_cb_reset(tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            QK_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    MY_SBRO,                        MY_SBRC, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        // +--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    MY_CBRO,                        MY_CBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    QK_REP,
        // +--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            KC_NUBS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME,                        KC_END,  KC_H,    KC_J,    KC_K,    KC_L,    KC_COMM, KC_SLSH,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
			SC_LSPO,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_DEL,       KC_ENT,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   SC_RSPC,
        // +--------+--------+--------+--------+--------+--------+        +--------+    +--------+        +--------+--------+--------+--------+--------+--------|
            KC_LCTL,TD(T3_SB),TD(T2_CB),KC_LGUI, KC_LALT,                 KC_SPC,           KC_SPC,                  MO(1),   QK_AREP, KC_LEFT, KC_DOWN, KC_RGHT
        // `--------+--------+--------+--------+--------+        +      +--------'        `--------+      +        +--------+--------+--------+--------+--------'
    ),

    [SYMBOLS] = LAYOUT( // greens
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            _______, _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______, _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            _______, _______, _______, KC_LBRC, _______, _______, _______,                        _______, _______, KC_BSLS, KC_EQL,  KC_SCLN, _______, _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            XXXXXXX, KC_QUOT, _______, MY_EUR,  _______, _______, _______,                        _______, _______, _______, _______, _______, _______, _______,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
            _______, MY_AT,  MY_HASH,S(KC_SCLN),KC_RBRC,S(KC_QUOT),       S(KC_BSLS),     _______,          _______,_______, _______, _______, KC_PGUP, _______,
        // |--------+--------+--------+--------+--------+--------+        +--------+    +--------+        +--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, XXXXXXX, _______, KC_MINS,                 S(KC_EQL),         _______,                _______, _______, KC_HOME, KC_PGDN, KC_END
        // `--------+--------+--------+--------+--------+      +        +--------'        `--------+      +        +--------+--------+--------+--------+--------'
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
        // |--------+--------+--------+--------+--------+--------+        +--------+    +--------+        +--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, _______, _______, _______,                 KC_MPLY,          KC_MNXT,                 XXXXXXX, KC_P0,   KC_PDOT, KC_PENT, KC_PPLS
        // `--------+--------+--------+--------+--------+      +        +--------+        +--------+      +        +--------+--------+--------+--------+--------'
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
        // |--------+--------+--------+--------+--------+--------+        +--------+    +--------+        +--------+--------+--------+--------+--------+--------|
            _______, _______, XXXXXXX, _______, KC_MYCM,                 AS_TOGG,          XXXXXXX,                 RM_VALD, RM_VALU, XXXXXXX, XXXXXXX, XXXXXXX
        // `--------+--------+--------+--------+--------+      +        +--------'        `--------+      +        +--------+--------+--------+--------+--------'
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] =        { ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [SYMBOLS] =     { ENCODER_CCW_CW(KC_RIGHT, KC_LEFT), ENCODER_CCW_CW(KC_UP, KC_DOWN)   },
    [MEDIA_FN] =    { ENCODER_CCW_CW(MS_WHLR, MS_WHLL),  ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
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

void render_leds (void) {
#ifdef AUTO_SHIFT_ENABLE
    oled_set_cursor(0, 7);
    oled_write_P(PSTR("  "), led_state.auto_shift_state);
    oled_set_cursor(0, 8);
    oled_write_P(PSTR("AS"), false);
#endif
    oled_set_cursor();
    oled_write_P(PSTR("  "), led_state.gui_key_state);
    oled_set_cursor(2, 8);
    oled_write_P(PSTR("GUI"), false);
}

void render_layer_state (void) {
    oled_set_cursor(0, 10);
    switch (get_highest_layer(layer_state)) {
        case BASE:
            oled_write_raw_P(base_layer, sizeof(base_layer));
            break;
        case SYMBOLS:
            oled_write_raw_P(symbols_layer, sizeof(symbols_layer));
            break;
        case MEDIA_FN:
            oled_write_raw_P(media_layer, sizeof(media_layer));
            break;
        case KB_SETTINGS:
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
        render_leds();
        render_layer_state();
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

void led_sync_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    if (in_buflen == sizeof(led_state)) {
        memcpy(&led_state, in_data, sizeof(led_state));
    }
}

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
    transaction_register_rpc(KB_LED_SYNC, led_sync_slave_handler);
}

void housekeeping_task_kb(void) {
    if (is_keyboard_master()) {
        // Interact with slave every 500ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 500) {
            eeconfig_read_keymap(&keymap_config);
            led_state_t led_s = {
                .auto_shift_state = get_autoshift_state(),
                .gui_key_state = !keymap_config.no_gui
            };
            if(transaction_rpc_send(KB_LED_SYNC, sizeof(led_s), &led_s)) {
                last_sync = timer_read32();
            } else {
                dprint("Slave sync failed!\n");
            }
        }
    }
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

#pragma region TapDance

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    uint8_t mod = mod_config(QK_MOD_TAP_GET_MODS(keycode));
    if (mod) {
        return TAPPING_TERM;
    }
    return 0;
}

// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

void td_finished(tap_dance_state_t *state, uint16_t code, uint8_t layer) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(code);
            set_last_keycode(code);
            break;
        case TD_SINGLE_HOLD:
            layer_on(layer);
            break;
        default:
            break;
    }
}

void td_reset(tap_dance_state_t *state, uint16_t code, uint8_t layer) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(code);
            break;
        case TD_SINGLE_HOLD:
            layer_off(layer);
            break;
        default:
            break;
    }
}

void t3_sb_finished(tap_dance_state_t *state, void *user_data) {
    td_finished(state, MY_SBRO, KB_SETTINGS);
}

void t3_sb_reset(tap_dance_state_t *state, void *user_data) {
    td_reset(state, MY_SBRO, KB_SETTINGS);
}

void t2_cb_finished(tap_dance_state_t *state, void *user_data) {
    td_finished(state, MY_CBRO, MEDIA_FN);
}

void t2_cb_reset(tap_dance_state_t *state, void *user_data) {
    td_reset(state, MY_CBRO, MEDIA_FN);
}

tap_dance_action_t tap_dance_actions[] = {
  [T3_SB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, t3_sb_finished, t3_sb_reset),
  [T2_CB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, t2_cb_finished, t2_cb_reset),
};

#pragma endregion

#pragma region alt repeat

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    if ((mods & MOD_MASK_CTRL)) {  // Was Ctrl held?
        switch (keycode) {
            case KC_Y: return C(KC_Z);  // Ctrl + Y reverses to Ctrl + Z.
            case KC_Z: return C(KC_Y);  // Ctrl + Z reverses to Ctrl + Y.
        }
    }
    if ((mods & MOD_MASK_SA)) {
        switch (keycode) {
            case KC_LBRC: return MY_CBRC;
            case KC_RBRC: return MY_CBRO;
        }
    }
    if ((mods & MOD_BIT(KC_RALT))) {
        switch (keycode) {
            case KC_LBRC: return MY_SBRC;
            case KC_RBRC: return MY_SBRO;
        }
    }

    return KC_TRNS;  // Defer to default definitions.
}

#pragma endregion
