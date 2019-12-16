# Without disabling something like mousekeys or the console
# the LED range control leaves less than 200 bytes in the
# firmware for other things
MOUSEKEY_ENABLE = no
SRC += led_control.c
