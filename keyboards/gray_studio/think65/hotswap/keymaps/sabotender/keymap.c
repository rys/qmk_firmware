/* Copyright 2020 Rys Sommefeldt
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
#include "led_control.h"

void keyboard_post_init_user(void) {
    wait_ms(250); // workaround a bug somewhere in TMK that stops user init happening at the right time in the startup sequence
    setup_led_range_control();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CAPS:
            if (!record->event.pressed) {
                // toggle the Escape LED cluster white
                host_keyboard_led_state().caps_lock ? rgblight_sethsv_range(HSV_WHITE, THINK65_LED_RANGE_ESC) : rgblight_sethsv_range(THINK65_LEDS_OFF, THINK65_LED_RANGE_ESC);
            }
            break;
        default:
            break;
    }
    return process_led_range_control_codes(keycode, record);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // toggle the 10th LED on layer 1 activation
    switch (get_highest_layer(state)) {
        case 1:
            rgblight_sethsv_at(HSV_WHITE, 9);
            break;
        default:
            rgblight_sethsv_at(THINK65_LEDS_OFF, 9);
            break;
    }
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
 LT(1, KC_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           KC_PGUP,
LSFT_T(S(KC_9)), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(S(KC_0)),  KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                      KC_SPC,                          KC_RALT, MO(1),            KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_65_ansi_blocker(
        RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_END,
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, KC_PSCR, _______, _______, KC_GRV,  KC_INS,
        _______, ESC_HUI, ESC_SAI, ESC_VAI, BDG_HUI, BDG_SAI, BDG_VAI, UGL_HUI, UGL_SAI, UGL_VAI, _______, _______, _______,          KC_HOME,
        _______, ESC_HUD, ESC_SAD, ESC_VAD, BDG_HUD, BDG_SAD, BDG_VAD, UGL_HUD, UGL_SAD, UGL_VAD, _______, _______,          KC_PGUP, KC_END,
        TOG_ESC, TOG_BDG, TOG_UGL,                      CYC_LED,                         _______, _______,          KC_HOME, KC_PGDN, KC_END
    ),

};
