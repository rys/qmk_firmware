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

#include "v2_iso_rgb.h"
#include "rgb_matrix_types.h"


void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up
  setPinOutput(E6);
  matrix_init_user();
}

void matrix_scan_kb(void) {
  // put your looping keyboard code here
  // runs every cycle (a lot)
  matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  // put your per-action keyboard code here
  // runs for every action, just before processing by the firmware
  return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinLow(E6);
  } else {
    writePinHigh(E6);
  }
	led_set_user(usb_led);
}

led_config_t g_led_config = {{
{0	,NO_LED,1	,2	,3	,4	,5	,6	,7	,8	,9	,10,	11	,12	,13	,14	,15},
{32	,31	   ,30	,29	,28	,27	,26	,25	,24	,23	,22	,21	,20	,19	,18	,17	,16},
{33	,34	   ,35	,36	,37	,38	,39	,40	,41	,42	,43	,44	,45	,NO_LED,	46,	47,	48},
{62	,61	   ,60	,59	,58	,57	,56	,55	,54	,53	,52	,51	,50	,49			},
{63	,64	   ,65	,66	,67	,68	,69	,70	,71	,72	,73	,74	,NO_LED	,75		,76	},
{87	,86	   ,85	,NO_LED ,NO_LED		,84,	NO_LED,NO_LED,NO_LED,83,	82,	81,	80,	NO_LED,	79,	78,	77}
},{
{0,0},	{14,0},	{28,0},	{42,0},	{56,0},	{70,0},	{84,0},	{98,0},	{112,0},	{126,0},	{140,0},	{154,0},	{168,0},		{196,0},	{210,0},	{224,0},
{0,13},	{14,13},	{28,13},	{42,13},	{56,13},	{70,13},	{84,13},	{98,13},	{112,13},	{126,13},	{140,13},	{154,13},	{168,13},	{182,13},	{196,13},	{210,13},	{224,13},
{0,26},	{14,26},	{28,26},	{42,26},	{56,26},	{70,26},	{84,26},	{98,26},	{112,26},	{126,26},	{140,26},	{154,26},	{168,26},		{196,26},	{210,26},	{224,26},
{0,38},	{14,38},	{28,38},	{42,38},	{56,38},	{70,38},	{84,38},	{98,38},	{112,38},	{126,38},	{140,38},	{154,38},	{168,38},	{182,38},
{0,51},	{14,51},	{28,51},	{42,51},	{56,51},	{70,51},	{84,51},	{98,51},	{112,51},	{126,51},	{140,51},	{154,51},		{182,51},		{210,51},
{0,64},	{14,64},	{28,64},			{70,64},				{126,64},	{140,64},	{154,64},	{168,64},		{196,64},	{210,64},	{224,64}
},{
    4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,		4,	1,	4,
    4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,
    4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,		4,	4,	4,
    1,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,
    4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,		4,		4,
    4,	4,	4,			4,				4,	4,	4,	4,		4,	4,	4
}
};
