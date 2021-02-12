/*
Copyright 2021 CapsUnlocked

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "v2_iso.h"

// Define LED 62 to white (caps lock)
const rgblight_segment_t PROGMEM cu80_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {62, 1, HSV_WHITE}
);

// Define LED 14 to white (scroll lock)
const rgblight_segment_t PROGMEM cu80_scrolllock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {14, 1, HSV_WHITE}
);

// Define layer array
const rgblight_segment_t* const PROGMEM cu80_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    cu80_capslock_layer, // lighting layer 0
    cu80_scrolllock_layer // lighting layer 1
);

// init
void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = cu80_rgb_layers;
}

// on state change read the stored status of the lock and apply that value to the layers
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    rgblight_set_layer_state(1, led_state.scroll_lock);
    return true;
}
