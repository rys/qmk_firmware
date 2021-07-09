/* Copyright 2021 Rys Sommefeldt
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌────┬────┬────┬────┐
     * │Esc │Tab │MO1 │Bsp │
     * ├────┼────┼────┼────┤
     * │Num │ /  │ *  │ -  │
     * ├────┼────┼────┼────┤
     * │ 7  │ 8  │ 9  │    │
     * ├────┼────┼────┤ +  │
     * │ 4  │ 5  │ 6  │    │
     * ├────┼────┼────┼────┤
     * │ 1  │ 2  │ 3  │    │
     * ├────┴────┼────┤Ent │
     * │    0    │ .  │    │
     * └─────────┴────┴────┘
     */
    [0] = LAYOUT_numpad_6x4(
        KC_ESC,  KC_TAB,  MO(1),   KC_BSPC,
        KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_NO,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_NO,
        KC_P0,   KC_NO,   KC_PDOT, KC_PENT
    ),

    /*
     * ┌────┬────┬────┬────┐
     * │Rst │RGB │    │RGB+│
     * ├────┼────┼────┼────┤
     * │    │    │    │RGB-│
     * ├────┼────┼────┼────┤
     * │Hom │ ↑  │PgU │    │
     * ├────┼────┼────┤    │
     * │ ←  │    │ →  │    │
     * ├────┼────┼────┼────┤
     * │End │ ↓  │PgD │    │
     * ├────┴────┼────┤    │
     * │ Insert  │Del │    │
     * └─────────┴────┴────┘
     */
    [1] = LAYOUT_numpad_6x4(
        RESET,   RGB_TOG, _______, RGB_MOD,
        _______, _______, _______, RGB_RMOD,
        KC_HOME, KC_UP,   KC_PGUP, XXXXXXX,
        KC_LEFT, XXXXXXX, KC_RGHT, _______,
        KC_END,  KC_DOWN, KC_PGDN, XXXXXXX,
        KC_INS,  XXXXXXX, KC_DEL,  _______
    )
};

void keyboard_post_init_user(void) {
  //debug_enable=true;
  //debug_matrix=true;
}
