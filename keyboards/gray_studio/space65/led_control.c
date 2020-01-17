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
#include "tmk_core/common/eeprom.h"
#include "led_control.h"

bool static_lighting(void) {
    return rgblight_get_mode() == RGBLIGHT_MODE_STATIC_LIGHT;
}

bool is_magic_valid(void) {
    return eeprom_read_byte((void*)SPACE65_LED_EEPROM_BASE_ADDR) == SPACE65_LED_EEPROM_MAGIC_BYTE;
}

void set_magic_value(void) {
    eeprom_update_byte((void*)SPACE65_LED_EEPROM_BASE_ADDR, SPACE65_LED_EEPROM_MAGIC_BYTE);
}

uint8_t read_magic_value(void) {
    return eeprom_read_byte((void*)SPACE65_LED_EEPROM_BASE_ADDR);
}

void print_led_config(void) {
#ifdef CONSOLE_ENABLE
    uprintf("Magic     %d\n", read_magic_value());

    switch (user_config.current_led_state) {
        case SPACE65_LED_STATE_OFF:
            uprintf("LED state %d -> Off\n",      user_config.current_led_state);
            break;
        case SPACE65_LED_STATE_SIDE:
            uprintf("LED state %d -> Esc\n",      user_config.current_led_state);
            break;
        case SPACE65_LED_STATE_TOP:
            uprintf("LED state %d -> Badge\n",    user_config.current_led_state);
            break;
        case SPACE65_LED_STATE_ON:
            uprintf("LED state %d -> All\n",      user_config.current_led_state);
            break;
        default:
            uprintf("LED state %d -> Unknown!\n", user_config.current_led_state);
            break;
    }

    uprintf("Side hsv(%d, %d, %d)\n", space65_led_config.side_h,
                                      space65_led_config.side_s,
                                      space65_led_config.side_v);
    uprintf("Top  hsv(%d, %d, %d)\n", space65_led_config.top_h,
                                      space65_led_config.top_s,
                                      space65_led_config.top_v);
#endif
}

void clear_led_config(void) {
    // Clear to HSV_WHITE (0, 0, 255)
    space65_led_config.side_h = (uint8_t)0;
    space65_led_config.side_s = (uint8_t)0;
    space65_led_config.side_v = (uint8_t)255;
    space65_led_config.top_h  = (uint8_t)0;
    space65_led_config.top_s  = (uint8_t)0;
    space65_led_config.top_v  = (uint8_t)255;
}

void read_led_config(void) {
    space65_led_config.side_h = (uint8_t)eeprom_read_byte(SPACE65_LED_EEPROM_BASE_ADDR +
                                                          SPACE65_LED_EEPROM_SIDE_ADDR  +
                                                          SPACE65_LED_EEPROM_H_BYTE);
    space65_led_config.side_s = (uint8_t)eeprom_read_byte(SPACE65_LED_EEPROM_BASE_ADDR +
                                                          SPACE65_LED_EEPROM_SIDE_ADDR  +
                                                          SPACE65_LED_EEPROM_S_BYTE);
    space65_led_config.side_v = (uint8_t)eeprom_read_byte(SPACE65_LED_EEPROM_BASE_ADDR +
                                                          SPACE65_LED_EEPROM_SIDE_ADDR  +
                                                          SPACE65_LED_EEPROM_V_BYTE);

    space65_led_config.top_h =  (uint8_t)eeprom_read_byte(SPACE65_LED_EEPROM_BASE_ADDR  +
                                                          SPACE65_LED_EEPROM_TOP_ADDR +
                                                          SPACE65_LED_EEPROM_H_BYTE);
    space65_led_config.top_s =  (uint8_t)eeprom_read_byte(SPACE65_LED_EEPROM_BASE_ADDR  +
                                                          SPACE65_LED_EEPROM_TOP_ADDR +
                                                          SPACE65_LED_EEPROM_S_BYTE);
    space65_led_config.top_v =  (uint8_t)eeprom_read_byte(SPACE65_LED_EEPROM_BASE_ADDR  +
                                                          SPACE65_LED_EEPROM_TOP_ADDR +
                                                          SPACE65_LED_EEPROM_V_BYTE);
}

void save_led_config(void) {
    eeprom_update_byte(SPACE65_LED_EEPROM_BASE_ADDR +
                       SPACE65_LED_EEPROM_SIDE_ADDR +
                       SPACE65_LED_EEPROM_H_BYTE, (uint8_t)space65_led_config.side_h);
    eeprom_update_byte(SPACE65_LED_EEPROM_BASE_ADDR +
                       SPACE65_LED_EEPROM_SIDE_ADDR +
                       SPACE65_LED_EEPROM_S_BYTE, (uint8_t)space65_led_config.side_s);
    eeprom_update_byte(SPACE65_LED_EEPROM_BASE_ADDR +
                       SPACE65_LED_EEPROM_SIDE_ADDR +
                       SPACE65_LED_EEPROM_V_BYTE, (uint8_t)space65_led_config.side_v);

    eeprom_update_byte(SPACE65_LED_EEPROM_BASE_ADDR +
                       SPACE65_LED_EEPROM_TOP_ADDR +
                       SPACE65_LED_EEPROM_H_BYTE, (uint8_t)space65_led_config.top_h);
    eeprom_update_byte(SPACE65_LED_EEPROM_BASE_ADDR +
                       SPACE65_LED_EEPROM_TOP_ADDR +
                       SPACE65_LED_EEPROM_S_BYTE, (uint8_t)space65_led_config.top_s);
    eeprom_update_byte(SPACE65_LED_EEPROM_BASE_ADDR +
                       SPACE65_LED_EEPROM_TOP_ADDR +
                       SPACE65_LED_EEPROM_V_BYTE, (uint8_t)space65_led_config.top_v);
}

// toggle one of the range flag bits
void toggle_led_state(unsigned int led_range) {
    if (led_range >= SPACE65_LED_SIDE_RANGE_BIT && led_range <= SPACE65_LED_TOP_RANGE_BIT) {
        user_config.current_led_state ^= 1 << led_range;
    }
}

// set one of the range flag bits
void set_led_state(unsigned int led_range) {
    if (led_range >= SPACE65_LED_SIDE_RANGE_BIT && led_range <= SPACE65_LED_TOP_RANGE_BIT) {
        user_config.current_led_state |= 1 << led_range;
    }
}

// clear one of the range flag bits
void clear_led_state(unsigned int led_range) {
    if (led_range >= SPACE65_LED_SIDE_RANGE_BIT && led_range <= SPACE65_LED_SIDE_RANGE_BIT) {
        user_config.current_led_state &= ~(1 << led_range);
    }
}

// cycle LED states: Off -> Esc -> Badge -> Underglow -> Esc+Badge -> Esc+Underglow -> Badge+Underglow -> All
void cycle_led_state(void) {
    switch(user_config.current_led_state) {
        case SPACE65_LED_STATE_OFF:
            user_config.current_led_state = SPACE65_LED_STATE_SIDE;
            break;
        case SPACE65_LED_STATE_SIDE:
            user_config.current_led_state = SPACE65_LED_STATE_TOP;
            break;
        case SPACE65_LED_STATE_TOP:
            user_config.current_led_state = SPACE65_LED_STATE_ON;
            break;
        case SPACE65_LED_STATE_ON:
            user_config.current_led_state = SPACE65_LED_STATE_OFF;
            break;
        default:
            break;
    }
}

void apply_led_state(void) {
    uint8_t side_h = space65_led_config.side_h;
    uint8_t side_s = space65_led_config.side_s;
    uint8_t side_v = space65_led_config.side_v;
    uint8_t top_h  = space65_led_config.top_h;
    uint8_t top_s  = space65_led_config.top_s;
    uint8_t top_v  = space65_led_config.top_v;

    // Set the RGB ranges based on the current state
    switch(user_config.current_led_state) {
        case SPACE65_LED_STATE_OFF:
            if (static_lighting()) {
                rgblight_sethsv_range(SPACE65_LEDS_OFF, SPACE65_LED_RANGE_ALL);
            } else {
                rgblight_disable();
            }
            break;
        case SPACE65_LED_STATE_SIDE:
            if (static_lighting()) {
                rgblight_sethsv_range(side_h, side_s, side_v, SPACE65_LED_RANGE_SIDE);
            } else {
                rgblight_set_effect_range(SPACE65_LED_SIDE_POS, SPACE65_LED_SIDE_NUM);
            }
            rgblight_sethsv_range(SPACE65_LEDS_OFF, SPACE65_LED_RANGE_TOP);
            break;
        case SPACE65_LED_STATE_TOP:
            if (static_lighting()) {
                rgblight_sethsv_range(top_h, top_s, top_v, SPACE65_LED_RANGE_TOP);
            } else {
                rgblight_set_effect_range(SPACE65_LED_TOP_POS, SPACE65_LED_TOP_NUM);
            }
            rgblight_sethsv_range(SPACE65_LEDS_OFF, SPACE65_LED_RANGE_SIDE);
            break;
        case SPACE65_LED_STATE_ON:
            if (static_lighting()) {
                rgblight_sethsv_range(side_h, side_s, side_v, SPACE65_LED_RANGE_SIDE);
                rgblight_sethsv_range(top_h, top_s, top_v, SPACE65_LED_RANGE_TOP);
            } else {
                rgblight_enable();
                rgblight_set_effect_range(SPACE65_LED_RANGE_ALL);
            }
            break;
        default:
            break;
    }

    print_led_config();
}

void setup_led_range_control(void) {
    user_config.raw = eeconfig_read_user();

    if (user_config.current_led_state >= SPACE65_LED_STATE_OFF && user_config.current_led_state <= SPACE65_LED_STATE_ON) {
        // If we find a good LED range state in the user EEPROM

        if (is_magic_valid()) {
            // Try and get a valid colour configuration out of the EEPROM space we use
            read_led_config();
        } else {
            // It's invalid, so write a fresh one
            set_magic_value();
            clear_led_config();
            save_led_config();
        }

        // Apply it
        apply_led_state();
    } else {
        // Setup a new default state of all on
        user_config.current_led_state = SPACE65_LED_STATE_ON;
        // Set the EEPROM magic value so we know we can safely read the values
        set_magic_value();
        // Then clear the colour set and save it
        clear_led_config();
        save_led_config();
        // Then apply that new default state and colour set
        apply_led_state();
        // Then save the state to user EEPROM
        eeconfig_update_user(user_config.raw);
    }
}

bool process_led_range_control_codes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CYC_LED:
            if (record->event.pressed) {
                cycle_led_state();
                apply_led_state();
                eeconfig_update_user(user_config.raw);
            }
            break;
        case TOG_SID:
            if (record->event.pressed) {
                toggle_led_state(SPACE65_LED_SIDE_RANGE_BIT);
                apply_led_state();
                eeconfig_update_user(user_config.raw);
            }
            break;
        case TOG_TOP:
            if (record->event.pressed) {
                toggle_led_state(SPACE65_LED_TOP_RANGE_BIT);
                apply_led_state();
                eeconfig_update_user(user_config.raw);
            }
            break;
        case SID_HUI:
            if (record->event.pressed) {
                space65_led_config.side_h += RGBLIGHT_HUE_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case SID_HUD:
            if (record->event.pressed) {
                space65_led_config.side_h -= RGBLIGHT_HUE_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case SID_SAI:
            if (record->event.pressed) {
                space65_led_config.side_s += RGBLIGHT_SAT_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case SID_SAD:
            if (record->event.pressed) {
                space65_led_config.side_s -= RGBLIGHT_SAT_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case SID_VAI:
            if (record->event.pressed) {
                space65_led_config.side_v += RGBLIGHT_VAL_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case SID_VAD:
            if (record->event.pressed) {
                space65_led_config.side_v -= RGBLIGHT_VAL_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case TOP_HUI:
            if (record->event.pressed) {
                space65_led_config.top_h += RGBLIGHT_HUE_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case TOP_HUD:
            if (record->event.pressed) {
                space65_led_config.top_h -= RGBLIGHT_HUE_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case TOP_SAI:
            if (record->event.pressed) {
                space65_led_config.top_s += RGBLIGHT_SAT_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case TOP_SAD:
            if (record->event.pressed) {
                space65_led_config.top_s -= RGBLIGHT_SAT_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case TOP_VAI:
            if (record->event.pressed) {
                space65_led_config.top_v += RGBLIGHT_VAL_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case TOP_VAD:
            if (record->event.pressed) {
                space65_led_config.top_v -= RGBLIGHT_VAL_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        default:
            break;
    }
    return true;
}
