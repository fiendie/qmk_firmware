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
#pragma once

// space cadet shifts
#define LSPO_KEYS KC_LSFT, KC_LSFT, KC_8
#define RSPC_KEYS KC_RSFT, KC_RSFT, KC_9

// auto shift and gui key "led" status
#define SPLIT_TRANSACTION_IDS_KB KB_LED_SYNC

// caps words
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_INVERT_ON_SHIFT

// auto shift
#define AUTO_SHIFT_TIMEOUT 190
#define AUTO_SHIFT_NO_AUTO_REPEAT
#define AUTO_SHIFT_MODIFIERS
#define PERMISSIVE_HOLD

// quadratic speed mouse
#define MOUSEKEY_INERTIA

// tap dance
#define TAPPING_TERM 125
#define TAPPING_TERM_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS
