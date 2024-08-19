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
#include "quantum/keymap_extras/keymap_german.h"

// Custom keycodes
#define CC_TILD LOPT(KC_N)          // Tilde
#define CC_EURO LOPT(KC_E)          // Euro symbol
#define CC_BSLS LSFT(LOPT(KC_7))    // Backslash
#define CC_PIPE LOPT(KC_7)          // Pipe symbol
#define CC_SLSH LSFT(KC_7)          // Forward slash
#define CC_LBRC LOPT(KC_8)          // Left curly brace
#define CC_RBRC LOPT(KC_9)          // Right curly brace
#define CC_RABR RSFT(KC_GRV)        // Right angle bracket
#define CC_AT   LOPT(KC_L)          // @ symbol
#define CC_LSBR LOPT(KC_5)          // Left square bracket
#define CC_RSBR LOPT(KC_6)          // Right square bracket
#define CC_PGUP LGUI(KC_UP)         // Page up (macOS)
#define CC_PGDN LGUI(KC_DOWN)       // Page down (macOS)

enum layers {
    BASE,
    GERMAN,
    MEDIA_FN,
    KB_SETTINGS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,     KC_GRV,                         CC_RABR, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        // +--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    CC_LBRC,                       CC_RBRC, DE_Z,    KC_U,    KC_I,    KC_O,    KC_P,    KC_UNDS,
        // +--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            KC_RPRN,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    CC_PIPE,                       DE_MINS, KC_H,    KC_J,    KC_K,    KC_L,    DE_PLUS, KC_BSLS,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
            SC_LSPO,  DE_Y,    KC_X,    KC_C,    KC_V,    KC_B,             KC_DEL,      OSL(1),           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   SC_RSPC,
        // +--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            KC_LCTL,  MO(3),   MO(2),   KC_LOPT, KC_LGUI,                   KC_SPC,      KC_ENT,                    KC_RGUI, KC_ROPT, KC_LEFT, KC_DOWN, KC_RGHT
        // `--------+--------+--------+--------+--------+--------+--------+--------'    `--------+--------+--------+--------+--------+--------+--------+--------'
    ),

    [GERMAN] = LAYOUT(
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            _______, _______, _______, _______, _______, _______, DE_LABK,                        DE_ACUT, _______, _______, _______, _______, _______, _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            _______, _______, _______, CC_EURO, _______, _______, CC_LSBR,                        CC_RSBR, _______, DE_UDIA, _______, DE_ODIA, _______, _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            _______, DE_ADIA, DE_SS,   _______, _______, _______, CC_BSLS,                        CC_SLSH, _______, _______, _______, CC_AT,   _______, _______,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
            _______, _______, _______, _______, _______, _______,          _______,      _______,          CC_TILD, _______, _______, _______, _______, _______,
        // |--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            _______, _______, _______, _______, _______,                   _______,      _______,                   _______, _______, _______, _______, _______
        // `--------+--------+--------+--------+--------+--------+--------+--------'    `--------+--------+--------+--------+--------+--------+--------+--------'
    ),

    [MEDIA_FN] = LAYOUT(
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                          KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_MUTE,      KC_VOLD,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CC_PGUP, KC_INS,
        // |--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, _______, XXXXXXX, KC_MRWD,                   KC_MPLY,      KC_VOLU,                   KC_MFFD, XXXXXXX, KC_HOME, CC_PGDN, KC_END
        // `--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------'
    ),

    [KB_SETTINGS] = LAYOUT(
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_RMOD,                       RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_SPD,                        RGB_SPI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          RGB_HUI,      RGB_SAD,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // |--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            _______, _______, XXXXXXX, XXXXXXX, RGB_VAD,                   RGB_HUD,      RGB_SAI,                   RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
        // `--------+--------+--------+--------+--------+--------+--------+--------'    `--------+--------+--------+--------+--------+--------+--------+--------'
    )
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case BASE:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case GERMAN:
            oled_write_P(PSTR("German\n"), false);
            break;
        case MEDIA_FN:
            oled_write_P(PSTR("Media/FN\n"), false);
            break;
        case KB_SETTINGS:
            oled_write_P(PSTR("Settings\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    return false;
}
#endif

