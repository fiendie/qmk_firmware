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
#include "suspend.h"
#include "gpio.h"
#include "bitmaps.h"
#include "ledmap.h"

extern rgb_config_t rgb_matrix_config;

enum layers {
    BASE,
    SYMBOL,
    MEDIA_FN,
    KB_SETTINGS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            QK_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS,                        KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        // +--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,                        KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,
        // +--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            KC_NUBS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME,                        KC_END,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_SLSH,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
			SC_LSPO,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_DEL,       KC_ENT,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   SC_RSPC,
        // +--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            KC_LCTL,  MO(3),   MO(2),   KC_LGUI, KC_LALT,                   KC_SPC,       KC_SPC,                    MO(1),   KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
        // `--------+--------+--------+--------+--------+--------+--------+--------'    `--------+--------+--------+--------+--------+--------+--------+--------'
    ),

    [SYMBOL] = LAYOUT( // greens
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            _______, _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______, _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            _______, _______, _______, KC_LBRC, _______, _______, _______,                        _______, _______, KC_BSLS, KC_EQL,  KC_SCLN, _______, _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            XXXXXXX, KC_QUOT, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______,   _______, _______,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
            _______, _______, _______, _______, _______, _______,          _______,      _______,          _______, _______, _______, _______, KC_PGUP, _______,
        // |--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, XXXXXXX, _______, _______,                   _______,      _______,                   _______, _______, KC_HOME, KC_PGDN, KC_END
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
            _______, XXXXXXX, _______, XXXXXXX, XXXXXXX,                   KC_MPLY,      KC_MNXT,                   XXXXXXX, KC_P0,   KC_PDOT, KC_PENT, KC_PPLS
        // `--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------'
    ),

    [KB_SETTINGS] = LAYOUT( // reds
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        KC_BRIU, XXXXXXX, RM_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            _______, QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        KC_BRID, XXXXXXX, RM_PREV, RM_NEXT, XXXXXXX, XXXXXXX, KC_SLEP,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            EE_CLR,  QK_RBT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, RM_HUED, RM_HUEU, XXXXXXX, XXXXXXX, XXXXXXX,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
            _______, DB_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,      XXXXXXX,          XXXXXXX, RM_SATD, RM_SATU, XXXXXXX, XXXXXXX, XXXXXXX,
        // |--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            _______, _______, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,      XXXXXXX,                   RM_VALD, RM_VALU, XXXXXXX, XXXXXXX, XXXXXXX
        // `--------+--------+--------+--------+--------+--------+--------+--------'    `--------+--------+--------+--------+--------+--------+--------+--------'
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] = { ENCODER_CCW_CW(UG_PREV, UG_NEXT),  ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
    [2] = { ENCODER_CCW_CW(UG_VALD, UG_VALU),  ENCODER_CCW_CW(UG_SPDD, UG_SPDU)  },
    [3] = { ENCODER_CCW_CW(UG_HUED, UG_HUEU),  ENCODER_CCW_CW(UG_SATD, UG_SATU)  },
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
    switch (get_highest_layer(layer_state)) {
        case BASE:
            oled_set_cursor(0, 10);
            oled_write_raw_P(base_layer, sizeof(base_layer));
            break;
        case SYMBOL:
            oled_set_cursor(0, 10);
            oled_write_raw_P(symbols_layer, sizeof(symbols_layer));
            break;
        case MEDIA_FN:
            oled_set_cursor(0, 10);
            oled_write_raw_P(media_layer, sizeof(media_layer));
            break;
        case KB_SETTINGS:
            oled_set_cursor(0, 10);
            oled_write_raw_P(settings_layer, sizeof(settings_layer));
            break;
        default:
            oled_set_cursor(0, 10);
            oled_write_raw_P(layer_indicator_0, sizeof(layer_indicator_0));
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
    if (bootloader) {
        oled_write_raw_P(skull, sizeof(skull));
        oled_set_cursor(0, 4);
        oled_write_raw_P(skull, sizeof(skull));
        oled_set_cursor(0, 8);
        oled_write_raw_P(skull, sizeof(skull));
        oled_set_cursor(0, 12);
        oled_write_raw_P(skull, sizeof(skull));
    } else {
        for (int i = 0; i < 16; i++) {
            oled_set_cursor(0, i);
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
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };

        if (!hsv.h && !hsv.s && !hsv.v) {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
        else {
            RGB rgb = hsv_to_rgb(hsv);
            float brightness_factor = (float)rgb_matrix_config.hsv.v / UINT8_MAX;

            rgb_matrix_set_color(i,
                brightness_factor * rgb.r,
                brightness_factor * rgb.g,
                brightness_factor * rgb.b
            );
        }
    }
}

bool rgb_matrix_indicators_user(void) {
    switch (biton32(layer_state)) {
        case 0:
            rgb_matrix_enable();
            break;
        case 1:
            set_layer_color(1);
            break;
        case 2:
            set_layer_color(2);
            break;
        case 3:
            set_layer_color(3);
            break;
        default:
            if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
                rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
    }
    return true;
}

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
}
