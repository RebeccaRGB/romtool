# Beckie's ROM Tool
Firmware, shield, and level shifter for reading and programming ROMs using an Arduino Mega.

## Hardware Required
  *  [Arduino Mega](https://www.adafruit.com/product/191)
  *  [RGB LCD Shield](https://www.adafruit.com/products/716) from Adafruit
  *  3x Texas Instruments SN74LVCH16T245 for level shifter board
  *  1x Texas Instruments SN74LVC2T45 for level shifter board
  *  A whole bunch of headers for shield and level shifter board

## Software Required
  *  [Arduino IDE](https://www.arduino.cc/en/Main/Software)
  *  [RGB LCD Shield Library](https://learn.adafruit.com/rgb-lcd-shield/downloads) from Adafruit

## Provided Functionality
  *  Change backlight color! Woo!
  *  Configurable data bus width (8 or 16, little- or big-endian)
  *  Configurable address bus width (8 to 31, in half-line increments)
  *  Raw binary or hexadecimal input and output over serial
  *  Inspect individual words of the ROM on the LCD
  *  Inspect 8 (in 8-bit mode) or 4 (in 16-bit mode) words at once on the LCD
  *  Dump ROM over serial
  *  Program ROM over serial
  *  Binary counter mode using address bus
  *  Logic probe mode using data bus
  *  LCD character chart 'cause why not
  *  Party mode!
  *  Save and load settings using the Arduino's EEPROM
  *  5V logic using the shield, 3.3V logic using the shield + level shifter

## Dumping or Programming a ROM
This is easy to do with `sread` and `swrite` from [the goodie `/bin/`](https://github.com/RebeccaRGB/goodiebin).

Dump a ROM to the file `rom.bin` with this command:

    $ sread -u /dev/tty.usbmodemfa131 -b 9600 -d 8 -p none -s 1 -r -o rom.bin -w 1

...then load settings and select Dump ROM on the Mega.

Program a ROM with the contents of the file `rom.bin` with this command:

    $ swrite -u /dev/tty.usbmodemfa131 -b 9600 -d 8 -p none -s 1 -r -i rom.bin -w 60

...then *quickly* load settings and select Program ROM on the Mega *before* `swrite` starts sending the ROM a minute later (`-w 60` = 60 seconds).
