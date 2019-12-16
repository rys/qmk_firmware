# Personal keymap for the Think 6.5 with compatible soldered PCB

The layout is UK ISO with some small personal tweaks.

The LED cycling code is based on code posted to the Gray Studio Discord by `MudkipMao` on Nov 22nd 2019. Thanks!

## LED cycling

This map saves and restores your current active LED group choice to user EEPROM and restores it on keyboard init, which you can cycle through all combinations of, or toggle individually.

The cycle is `Off -> Esc -> Badge -> Underglow -> Esc+Badge -> Esc+Underglow -> Badge+Underglow -> All`. Look at the keymap for the controls on layer 1.

## LED range colours

This map also allows you to set different colours for each of the different LED ranges (Esc, Badge and Underglow), and those colours will be restored when you restart the keyboard. Look at the keymap for the controls on layer 2.

## Known issues

Because of how RGB toggling works in QMK, if you set your own LED range colours and then toggle RGB off and on with `RGB_TOG`, you'll get QMK's view of the colours rather than the ones you set. Just adjust the user range in some way and your custom colours will be restored.
