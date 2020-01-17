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

/*
 * LED ranges
 * ┌──────────┬──────────┐
 * │ 00 01 02 │ 03 04 05 │
 * │   side   │    top   │
 * └──────────┴──────────┘
 */

// Define the LED ranges          start, end
#define SPACE65_LED_RANGE_OFF         0, 0
#define SPACE65_LED_RANGE_SIDE        0, 2
#define SPACE65_LED_RANGE_TOP         3, 5
#define SPACE65_LED_RANGE_ALL         0, 5

// Define the LED positions and counts for the dynamic lighting API
#define SPACE65_LED_SIDE_POS          0
#define SPACE65_LED_SIDE_NUM          3
#define SPACE65_LED_TOP_POS           3
#define SPACE65_LED_TOP_NUM           3
#define SPACE65_LED_SIDE_TOP_POS      SPACE65_LED_SIDE_POS
#define SPACE65_LED_SIDE_TOP_NUM      (SPACE65_LED_SIDE_NUM + SPACE65_LED_TOP_NUM)

// Turn the LEDs off by setting HSV to 0, 0, 0
#define SPACE65_LEDS_OFF              0, 0, 0

// There are 2 ranges, so we can store all combinations in 2^2 values
// Define all of them to make it easier to write the cycling code
#define SPACE65_LED_STATE_OFF         0x0 // 0b00000000
#define SPACE65_LED_STATE_SIDE        0x1 // 0b00000001
#define SPACE65_LED_STATE_TOP         0x2 // 0b00000010
#define SPACE65_LED_STATE_ON          0x4 // 0b00000011

// Define each LED range as a bit flag
#define SPACE65_LED_SIDE_RANGE_BIT    0
#define SPACE65_LED_TOP_RANGE_BIT     1

// Define a magic byte value to help protect us from other users overwriting our EEPROM space
#define SPACE65_LED_EEPROM_MAGIC_BYTE 0x52

// Define where in user EEPROM we want to start saving the per-range colour values
// eeconfig values currently stop at byte 33, so in theory we could use byte 34 onwards
// but let's pick something nice and high since we've got 1024 bytes on an atmega32u4
#define SPACE65_LED_EEPROM_BASE_ADDR  (uint8_t *)128
#define SPACE65_LED_EEPROM_MAGIC_ADDR 0
#define SPACE65_LED_EEPROM_SIDE_ADDR  1
#define SPACE65_LED_EEPROM_TOP_ADDR   4
#define SPACE65_LED_EEPROM_H_BYTE     0
#define SPACE65_LED_EEPROM_S_BYTE     1
#define SPACE65_LED_EEPROM_V_BYTE     2

// setup the user EEPROM space we need
typedef union {
    uint8_t raw;
    struct {
        uint8_t current_led_state:8;
    };
} user_config_t;

user_config_t user_config;

// setup a struct to hold the data we save into EEPROM for the per-range colours
typedef struct Space65_LED_Config {
    uint8_t side_h;
    uint8_t side_s;
    uint8_t side_v;
    uint8_t top_h;
    uint8_t top_s;
    uint8_t top_v;
} Space65_LED_Config;

Space65_LED_Config space65_led_config;

// Check if dynamic lighting is enabled
bool static_lighting(void);

// Range control setup
void setup_led_range_control(void);

// magic value read/write
bool is_magic_valid(void);
void set_magic_value(void);
uint8_t read_magic_value(void);

// clear/read/set LED config in user EEPROM
void clear_led_config(void);
void read_led_config(void);
void save_led_config(void);
void print_led_config(void);

// LED state API
void toggle_led_state(unsigned int led_range);
void set_led_state(unsigned int led_range);
void clear_led_state(unsigned int led_range);
void cycle_led_state(void);
void apply_led_state(void);

// Setup some keycodes to control cycling and range toggling
enum space65_led_keycodes {
    CYC_LED = SAFE_RANGE,
    // Range toggle
    TOG_SID,
    TOG_TOP,
    // Side range HSV
    SID_HUI,
    SID_HUD,
    SID_SAI,
    SID_SAD,
    SID_VAI,
    SID_VAD,
    // Top range HSV
    TOP_HUI,
    TOP_HUD,
    TOP_SAI,
    TOP_SAD,
    TOP_VAI,
    TOP_VAD,
    // New SAFE_RANGE
    SPACE65_SAFE_RANGE
};

// Handle the custom LED range control keycodes
bool process_led_range_control_codes(uint16_t keycode, keyrecord_t *record);
