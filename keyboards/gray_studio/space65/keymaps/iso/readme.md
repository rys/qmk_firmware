# ISO keymap for Space65

Make this firmware with `make gray_studio/space65:iso`.

## Static and Dynamic lighting

The Space65 has two groups of LEDs: 3 for the side lighting and 3 for the top light. This firmware allows you to enable and disable those LED ranges in both dynamic and static lighting environments.

### LED cycling

This map saves and restores your current active LED group choice to user EEPROM and restores it on keyboard init, which you can cycle through all combinations of, or toggle individually.

The cycle is `Off -> Side -> Top -> All`. Look at the keymap for the controls on layer 1.

### LED range colours

This map also allows you to set different colours for each of the two LED ranges (Side and Top) in static lighting mode, and those colours will be restored when you restart the keyboard. Look at the keymap for the controls on layer 1.

### Known issues

Because of how RGB toggling works in QMK, if you set your own LED range colours and then toggle RGB off and on with `RGB_TOG`, you'll get QMK's view of the colours rather than the ones you set. Just adjust the user range in some way and your custom colours will be restored.
