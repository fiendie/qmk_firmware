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
#include "suspend.h"
#include "gpio.h"
#include "../../../bitmaps.h"
#include "ledmap.h"

#define EECONFIG_OS 0x20  // EEPROM address (choose a free one above 0x10)

extern rgb_config_t rgb_matrix_config;

typedef enum {
    OS_MACOS = 0,
    OS_WINDOWS = 1,
    OS_LINUX = 2
} os_type_t;

enum custom_keycodes {
    CC_EURO = SAFE_RANGE,
    CC_BSLS,                // Backslash
    CC_PIPE,
    CC_LBRC,                // Left Curly Brace
    CC_RBRC,                // Right Curly Brace
    CC_LABR,                // Left Angle Bracket
    CC_RABR,                // Right Angle Bracket
    CC_AT,
    CC_TILD,
    CC_CIRC,                // Accent Circonflex
    CC_DEGR,                // Degrees
    CC_BTCK,                // Backtick
    CC_LSBR,                // Left Bracket
    CC_RSBR,                // Right Bracket
    CC_PGUP,
    CC_PGDN,
    CC_OSWIN,
    CC_OSLIN,
    CC_OSMAC
};

static os_type_t current_os;
static os_type_t last_rendered_os;

enum layers {
    BASE,
    SYMBOL,
    MEDIA_FN,
    KB_SETTINGS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    CC_LABR,                        CC_RABR, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        // +--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   CC_LBRC,                        CC_RBRC, DE_Z,    KC_U,    KC_I,    KC_O,    KC_P,    KC_UNDS,
        // +--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            KC_RPRN,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   CC_PIPE,                        DE_MINS, KC_H,    KC_J,    KC_K,    KC_L,    DE_PLUS, KC_BSLS,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
            SC_LSPO,  DE_Y,    KC_X,    KC_C,    KC_V,    KC_B,             KC_DEL,      OSL(1),           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   SC_RSPC,
        // +--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            KC_LCTL,  MO(3),   MO(2),   KC_LOPT, KC_LGUI,                   KC_SPC,      KC_ENT,                    KC_RGUI, KC_ROPT, KC_LEFT, KC_DOWN, KC_RGHT
        // `--------+--------+--------+--------+--------+--------+--------+--------'    `--------+--------+--------+--------+--------+--------+--------+--------'
    ),

    [SYMBOL] = LAYOUT(
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            _______, _______, _______, _______, _______, _______, CC_CIRC,                        CC_DEGR, CC_BTCK, _______, _______, _______, _______, _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            _______, _______, _______, CC_EURO, _______, _______, CC_LSBR,                        CC_RSBR, _______, DE_UDIA, _______, DE_ODIA, _______, _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            _______, DE_ADIA, DE_SS,   _______, _______, _______, CC_BSLS,                        DE_SLSH, _______, _______, _______, CC_AT,   _______, _______,
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
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        KC_BRID, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_MUTE,      KC_VOLD,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CC_PGUP, KC_INS,
        // |--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, _______, XXXXXXX, KC_MRWD,                   KC_MPLY,      KC_VOLU,                   KC_MFFD, XXXXXXX, KC_HOME, CC_PGDN, KC_END
        // `--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------'
    ),

    [KB_SETTINGS] = LAYOUT(
        // ,--------+--------+--------+--------+--------+--------+--------.                      ,--------+--------+--------+--------+--------+--------+--------.
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,                       CC_OSMAC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       CC_OSWIN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // |--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       CC_OSLIN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // +--------+--------+--------+--------+--------+--------+--------+--------.    ,------- +--------+--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,      XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // |--------+--------+--------+--------+--------+--------+--------+--------+    +--------+--------+--------+--------+--------+--------+--------+--------|
            _______, _______, XXXXXXX, XXXXXXX, RGB_VAD,                   XXXXXXX,      XXXXXXX,                   RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
        // `--------+--------+--------+--------+--------+--------+--------+--------'    `--------+--------+--------+--------+--------+--------+--------+--------'
    )
};

void keyboard_pre_init_user(void) {
    // Disable Liatris power LED
    gpio_set_pin_output(24);
    gpio_write_pin_high(24);
}

void keyboard_post_init_user(void) {
    rgb_matrix_enable();

    uint8_t os_val = eeprom_read_byte((uint8_t*)EECONFIG_OS);

    if (os_val > OS_LINUX) {  // sanity check
        os_val = OS_MACOS;
    }

    current_os = (os_type_t)os_val;
    last_rendered_os = 255;  // force refresh once
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case CC_EURO:
                tap_code16(ROPT(KC_E));
                return false;
            case CC_BSLS:
                if (current_os == OS_MACOS) {
                    tap_code16(LSFT(ROPT(KC_7)));
                }
                else {
                    tap_code16(ROPT(KC_MINS));
                }
                return false;
            case CC_PIPE:
                if (current_os == OS_MACOS) {
                    tap_code16(ROPT(KC_7));
                }
                else {
                    tap_code16(ROPT(DE_LABK));
                }
                return false;
            case CC_LBRC:
                if (current_os == OS_MACOS) {
                    tap_code16(ROPT(KC_8));
                }
                else {
                    tap_code16(ROPT(KC_7));
                }
                return false;
            case CC_RBRC:
                if (current_os == OS_MACOS) {
                    tap_code16(ROPT(KC_9));
                }
                else {
                    tap_code16(ROPT(KC_0));
                }
                return false;
            case CC_LABR:
                if (current_os == OS_MACOS) {
                    tap_code16(KC_GRV);
                }
                else {
                    tap_code16(DE_LABK);
                }
                return false;
            case CC_RABR:
                if (current_os == OS_MACOS) {
                    tap_code16(RSFT(KC_GRV));
                }
                else {
                    tap_code16(DE_RABK);
                }
                return false;
            case CC_AT:
                if (current_os == OS_MACOS) {
                    tap_code16(ROPT(KC_L));
                }
                else {
                    tap_code16(ROPT(KC_Q));
                }
                return false;
            case CC_TILD:
                if (current_os == OS_MACOS) {
                    tap_code16(ROPT(KC_N));
                }
                else {
                    tap_code16(DE_TILD);
                }
                return false;
            case CC_CIRC:
                if (current_os == OS_MACOS) {
                    tap_code16(KC_NUBS);
                }
                else {
                    tap_code16(DE_CIRC);
                }
                return false;
            case CC_DEGR:
                if (current_os == OS_MACOS) {
                    tap_code16(LSFT(KC_NUBS));
                }
                else {
                    tap_code16(LSFT(DE_CIRC));
                }
                return false;
            case CC_BTCK:
                tap_code16(LSFT(KC_EQL));
                return false;
            case CC_LSBR:
                if (current_os == OS_MACOS) {
                    tap_code16(ROPT(KC_5));
                }
                else {
                    tap_code16(ROPT(KC_8));
                }
                return false;
            case CC_RSBR:
                if (current_os == OS_MACOS) {
                    tap_code16(ROPT(KC_6));
                }
                else {
                    tap_code16(ROPT(KC_9));
                }
                return false;
            case CC_PGUP:
                if (current_os == OS_MACOS) {
                    tap_code16(LGUI(KC_UP));
                }
                else {
                    tap_code(KC_PGUP);
                }
                return false;
            case CC_PGDN:
                if (current_os == OS_MACOS) {
                    tap_code16(LGUI(KC_DOWN));
                }
                else {
                    tap_code(KC_PGDN);
                }
                return false;
            case CC_OSWIN:
                current_os = OS_WINDOWS;
                eeprom_update_byte((uint8_t*)EECONFIG_OS, OS_WINDOWS);
                return false;
            case CC_OSMAC:
                current_os = OS_MACOS;
                eeprom_update_byte((uint8_t*)EECONFIG_OS, OS_MACOS);
                return false;
            case CC_OSLIN:
                current_os = OS_LINUX;
                eeprom_update_byte((uint8_t*)EECONFIG_OS, OS_LINUX);
                return false;
        }
    }

    return true;
}

void render_current_os (void) {
    if (is_keyboard_master()) {
        switch (current_os) {
            case OS_WINDOWS:
                oled_set_cursor(0, 10);
                oled_write_raw_P(windows_icon, sizeof(windows_icon));
                break;

            case OS_MACOS:
                oled_set_cursor(0, 10);
                oled_write_raw_P(apple_icon, sizeof(apple_icon));
                break;

            case OS_LINUX:
                oled_set_cursor(0, 10);
                oled_write_raw_P(linux_icon, sizeof(linux_icon));
                break;

            default:
                oled_set_cursor(0, 10);
                oled_write_raw_P(apple_icon, sizeof(apple_icon));
                break;
        }
    }
}

void suspend_power_down_user(void) {
    rgb_matrix_disable_noeeprom();
    oled_off();
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_enable_noeeprom();
    oled_on();
}

bool logo_rendered_master = false;
bool logo_rendered_slave = false;
int last_layer_state = 1;

void render_layer_state (int current_layer_state) {
    if (last_layer_state != current_layer_state) {
        last_layer_state = current_layer_state;

        if (!is_keyboard_master()) {
            switch (current_layer_state) {
                case BASE:
                    oled_set_cursor(0, 10);
                    oled_write_raw_P(layer_indicator_1, sizeof(layer_indicator_1));
                    break;
                case SYMBOL:
                    oled_set_cursor(0, 10);
                    oled_write_raw_P(layer_indicator_2, sizeof(layer_indicator_2));
                    break;
                case MEDIA_FN:
                    oled_set_cursor(0, 10);
                    oled_write_raw_P(layer_indicator_3, sizeof(layer_indicator_3));
                    break;
                case KB_SETTINGS:
                    oled_set_cursor(0, 10);
                    oled_write_raw_P(layer_indicator_4, sizeof(layer_indicator_4));
                    break;
                default:
                    oled_set_cursor(0, 10);
                    oled_write_raw_P(layer_indicator_0, sizeof(layer_indicator_0));
            }
        }
    }
}

bool oled_task_user(void) {
    int current_layer_state = get_highest_layer(layer_state);

    if (!logo_rendered_master && is_keyboard_master()) {
        oled_clear();
        oled_write_raw_P(nomad_logo, sizeof(nomad_logo));

        logo_rendered_master = true;
    }
    else if (!logo_rendered_slave && !is_keyboard_master()) {
        oled_clear();
        oled_write_raw_P(nomad_logo, sizeof(nomad_logo));

        logo_rendered_slave = true;
    }

    render_layer_state(current_layer_state);

    if (current_os != last_rendered_os) {
        render_current_os();
        last_rendered_os = current_os;
    }

    return false;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLD);
        }
        else {
            tap_code(KC_VOLU);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        }
        else {
            tap_code(KC_PGUP);
        }
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

