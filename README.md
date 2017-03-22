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
  *  Serial command line interface; connect and enter the command `?` to get a list of further commands:

    Beckie's ROM Tool Serial Interface
    ![<string>]         Echo string over serial
    b[<color>]          Report or set backlight color (0, 1, ..., 7)
    d[<width>]          Report or set data width (8, 16 LE, 16 BE)
    a[<width>]          Report or set address width (8, 8.5, ..., 31)
    f[<format>]         Report or set I/O format for D and P (Raw, Hex)
    i<addr>[ <addr>]    Print hex dump of specified range of ROM
    w<addr>[ <data>]    Program ROM using plain address and hex data
    S<rest-of-record>   Program ROM using Motorola SREC record
    :<rest-of-record>   Program ROM using Intel HEX record
    %<rest-of-record>   Program ROM using Tektronix extended HEX record
    M                   Report maximum address (exclusive) in hex
    D                   Start dumping entire ROM over serial
    P                   Start programming entire ROM over serial
    s<slot>             Save settings to Arduino EEPROM (0, 1, ..., F)
    r<slot>             Load settings from Arduino EEPROM (0, 1, ..., F)
    A<addr>             Set value on address bus (binary counter)
    Q                   Print value on data bus (logic probe)
    c, cs, ch           Clear LCD, show cursor, hide cursor
    c[<column> ]<row>   Set LCD cursor position
    p[<string>]         Print string on LCD
    m                   Return to menu display

## Dumping or Programming a ROM
This is easiest to do with the provided scripts `rtdownload.py` and `rtupload.py`.
These will connect to the ROM Tool over serial, configure it, start the dumping
or programming process, and save the output or read the input from a file.

Dump a ROM to the file `rom.bin` with this command:

    $ tools/rtdownload.py -u /dev/tty.usbmodemfa131 -d 8 -a 16 -f raw -o rom.bin

Program a ROM with the contents of the file `rom.bin` with this command:

    $ tools/rtupload.py -u /dev/tty.usbmodemfa131 -d 8 -a 16 -f raw -i rom.bin

Provide the path to the device with `-u`, the data width with `-d` (`8`, `16le`,
or `16be`), the address width with `-a` (`8`, `8.5`, ..., `31`), the format with
`-f` (`raw` or `hex`), the output file with `-o`, and the input file with `-i`.
