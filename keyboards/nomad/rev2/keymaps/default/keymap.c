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
#include "../../../bitmaps.h"
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
            KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LT,                          KC_GT,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        // +--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LCBR,                        KC_RCBR, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_UNDS,
        // +--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            KC_RPRN,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_PIPE,                        KC_MINS, KC_H,    KC_J,    KC_K,    KC_L,    KC_PLUS, KC_BSLS,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
            SC_LSPO,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_DEL,       OSL(1),           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   SC_RSPC,
        // +--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            KC_LCTL,  MO(3),   MO(2),   KC_LOPT, KC_LGUI,                   KC_SPC,       KC_ENT,                    KC_RGUI, KC_ROPT, KC_LEFT, KC_DOWN, KC_RGHT
        // `--------+--------+--------+--------+--------+--------+--------+--------'    `--------+--------+--------+--------+--------+--------+--------+--------'
    ),

    [SYMBOL] = LAYOUT(
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            _______, _______, _______, _______, _______, _______, KC_CIRC,                        _______, KC_GRV,  _______, _______, _______, _______, _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            _______, _______, _______, _______, _______, _______, KC_LBRC,                        KC_RBRC, _______, _______, _______, _______, _______, _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            _______, _______, _______, _______, _______, _______, KC_BSLS,                        KC_SLSH, _______, _______, _______, KC_AT,   _______, _______,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
            _______, _______, _______, _______, _______, _______,          _______,      _______,          KC_TILD, _______, _______, _______, _______, _______,
        // |--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            _______, _______, _______, _______, _______,                   _______,      _______,                   _______, _______, _______, _______, _______
        // `--------+--------+--------+--------+--------+--------+--------+--------'    `--------+--------+--------+--------+--------+--------+--------+--------'
    ),

    [MEDIA_FN] = LAYOUT(
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                          KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        KC_BRID, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_MUTE,      KC_VOLD,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_INS,
        // |--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, _______, XXXXXXX, KC_MRWD,                   KC_MPLY,      KC_VOLU,                   KC_MFFD, XXXXXXX, KC_HOME, KC_PGDN, KC_END
        // `--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------'
    ),

    [KB_SETTINGS] = LAYOUT(
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RM_TOGG,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,      XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // |--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            _______, _______, XXXXXXX, XXXXXXX, RM_VALD,                   XXXXXXX,      XXXXXXX,                   RM_VALU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
        // `--------+--------+--------+--------+--------+--------+--------+--------'    `--------+--------+--------+--------+--------+--------+--------+--------'
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] =        { ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [SYMBOL] =     { ENCODER_CCW_CW(KC_RIGHT, KC_LEFT), ENCODER_CCW_CW(KC_UP, KC_DOWN)   },
    [MEDIA_FN] =    { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(MS_WHLL, MS_WHLR) },
    [KB_SETTINGS] = { ENCODER_CCW_CW(RM_SPDU, RM_SPDD),  ENCODER_CCW_CW(RM_VALD, RM_VALU) },
};
#endif

void keyboard_pre_init_user(void) {
    // Disable Liatris power LED
    gpio_set_pin_output(24);
    gpio_write_pin_high(24);
}

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
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
    switch (get_highest_layer(layer_state)) {
        case BASE:
            oled_write_raw_P(layer_indicator_1, sizeof(layer_indicator_1));
            break;
        case SYMBOL:
            oled_write_raw_P(layer_indicator_2, sizeof(layer_indicator_2));
            break;
        case MEDIA_FN:
            oled_write_raw_P(layer_indicator_3, sizeof(layer_indicator_3));
            break;
        case KB_SETTINGS:
            oled_write_raw_P(layer_indicator_4, sizeof(layer_indicator_4));
            break;
        default:
            oled_write_raw_P(layer_indicator_0, sizeof(layer_indicator_0));
    }
}

bool oled_task_user(void) {
    oled_clear();

    render_logo();

    if (!is_keyboard_master()) {
        render_layer_state();
    }

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
            set_layer_color(0);
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

