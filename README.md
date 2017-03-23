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
  *  Serial command line interface; connect and enter the command `?` to get a list of further commands

## Dumping or Programming a ROM
This is easiest to do with the provided scripts `rtdownload.py` and `rtupload.py`.
These will connect to the ROM Tool over serial, configure it, start the dumping
or programming process, and save the output or read the input from a file.
(The pySerial library is required; refer to the pySerial installation instructions
for details.)

Dump a ROM to the file `rom.bin` with this command:

    $ tools/rtdownload.py -u /dev/tty.usbmodemfa131 -d 8 -a 16 -f raw -o rom.bin

Program a ROM with the contents of the file `rom.bin` with this command:

    $ tools/rtupload.py -u /dev/tty.usbmodemfa131 -d 8 -a 16 -f raw -i rom.bin

Provide the path to the device with `-u`, the data width with `-d` (`8`, `16le`,
or `16be`), the address width with `-a` (`8`, `8.5`, ..., `31`), the format with
`-f` (`raw` or `hex`), the output file with `-o`, and the input file with `-i`.

If you are having difficulty dumping a ROM reliably, you can attempt several
dumps and compare them using `erdrcr.py`. With enough dumps you may be able
to construct an error-corrected version.

This command will compare three dumps, `1.bin`, `2.bin`, and `3.bin`, and
output an error-corrected version to `4.bin`:

    $ tools/erdrcr.py 1.bin 2.bin 3.bin -o 4.bin
    Address.Mask	0's	1's	Correction
    00000015.02:	2	1	0
    0000001C.08:	1	2	1
    2 out of 320 bits mismatched (0.625% error rate)
    all errors correctable

If you wish to talk to the ROM Tool directly over its serial interface,
you can do so using the miniterm utility that comes with pySerial.
Make sure to specify `--rtscts`, `--echo`, and `--eol LF`:

    $ python -m serial.tools.miniterm --rtscts --echo --eol LF /dev/tty.usbmodemfd121 57600
    --- Miniterm on /dev/tty.usbmodemfd121  57600,8,N,1 ---
    --- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    ?
    Beckie's ROM Tool Serial Interface
    ![<string>]         Echo string over serial
    b[<color>]          Report or set backlight color (0, 1, ..., 7)
    d[<width>]          Report or set data width (8, 16 LE, 16 BE)
    a[<width>]          Report or set address width (8, 8.5, ..., 31)
    f[<format>]         Report or set I/O format for D and P (Raw, Hex)
    i[<addr>[ <addr>]]  Print hex dump of specified range of ROM
    w<addr>[ <data>]    Program ROM using plain address and hex data
    S<rest-of-record>   Program ROM using Motorola SREC record
    :<rest-of-record>   Program ROM using Intel HEX record
    %<rest-of-record>   Program ROM using Tektronix extended HEX record
    M                   Report maximum address (inclusive) in hex
    D[<addr>[ <addr>]]  Start dumping specified range or entire ROM over serial
    P[<addr>[ <addr>]]  Start programming specified range or entire ROM over serial
    s<slot>             Save settings to Arduino EEPROM (0, 1, ..., F)
    r<slot>             Load settings from Arduino EEPROM (0, 1, ..., F)
    A<addr>             Set value on address bus (binary counter)
    Q                   Print value on data bus (logic probe)
    c, cs, ch           Clear LCD, show cursor, hide cursor
    c[<column> ]<row>   Set LCD cursor position
    p[<string>]         Print string on LCD
    m                   Return to menu display
    d16le
    OK
    a25
    OK
    i 600 63f
    00000600: 6863 736B 6D75 333A 4334 4236 4444 2034 6576 3A72 7522 6E27 5053 4920 4544 6556  chksum:34C6BDD4 ver:"u'nSP IDEVe
    00000610: 2072 2E31 2E36 2232 7520 6573 3A72 7322 6E75 6C70 7375 2022 6F62 7964 223A 5053  r 1.6.2" user:"sunplus" body:"SP
    00000620: 3247 3334 0022 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000  G243"...........................
    00000630: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000  ................................
