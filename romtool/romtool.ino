#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include "rtio.h"
#include "rtui.h"

#define NUM_PGM     14
#define KEY_DELAY  500
#define REF_DELAY  100

int cur_pgm = 0;

int data_width = RTUI_DATA_WIDTH_8;
int addr_width = RTUI_ADDR_WIDTH_16;
int hex_format = false;

int active = false;
int addr_inc;
unsigned long addr;
unsigned long addr_max;

int eeprom_page = 0;
int eeprom_pages = 16;
char * eeprom_page_names[16] = {
  "0", "1", "2", "3", "4", "5", "6", "7",
  "8", "9", "A", "B", "C", "D", "E", "F",
};

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void setup() {
  Serial.begin(9600);
  rtio_init();
  rtui_init();
  pgm_setup();
}

void pgm_setup() {
  switch (cur_pgm) {
    case  0: hello_setup(); break;
    case  1: data_width_setup(); break;
    case  2: addr_width_setup(); break;
    case  3: hex_format_setup(); break;
    case  4: inspect_words_setup(); break;
    case  5: inspect_rows_setup(); break;
    case  6: dump_rom_setup(); break;
    case  7: program_rom_setup(); break;
    case  8: binary_counter_setup(); break;
    case  9: logic_probe_setup(); break;
    case 10: character_chart_setup(); break;
    case 11: party_mode_setup(); break;
    case 12: save_settings_setup(); break;
    case 13: load_settings_setup(); break;
  }
}

void pgm_prev() {
  if (cur_pgm <= 0) cur_pgm = NUM_PGM;
  cur_pgm--;
  pgm_setup();
}

void pgm_next() {
  cur_pgm++;
  if (cur_pgm >= NUM_PGM) cur_pgm = 0;
  pgm_setup();
}

void loop() {
  switch (cur_pgm) {
    case  0: hello_loop(); break;
    case  1: data_width_loop(); break;
    case  2: addr_width_loop(); break;
    case  3: hex_format_loop(); break;
    case  4: inspect_words_loop(); break;
    case  5: inspect_rows_loop(); break;
    case  6: dump_rom_loop(); break;
    case  7: program_rom_loop(); break;
    case  8: binary_counter_loop(); break;
    case  9: logic_probe_loop(); break;
    case 10: character_chart_loop(); break;
    case 11: party_mode_loop(); break;
    case 12: save_settings_loop(); break;
    case 13: load_settings_loop(); break;
  }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void hello_setup() {
  rtui_clear();
  rtui_print("Beckie\x03 ROM Tool");
  rtui_set_cursor(0, 1);
  rtui_print("\x04/\x05 Menu \x06/\x07 Adj");
}

void hello_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (buttons & RTUI_UP) {
    rtui_set_backlight(rtui_get_backlight() + 1);
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_DOWN) {
    rtui_set_backlight(rtui_get_backlight() - 1);
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_LEFT) {
    pgm_prev();
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_RIGHT) {
    pgm_next();
    while (rtui_get_buttons());
    return;
  }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void data_width_setup() {
  rtui_clear();
  rtui_print("Data Width");
  rtui_set_cursor(0, 1);
  rtui_print("\x06   ");
  rtui_print_data_width(data_width);
  rtui_print("   \x07");
}

void data_width_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (buttons & RTUI_UP) {
    data_width++;
    if (data_width >= RTUI_DATA_WIDTHS) data_width = 0;
    rtui_set_cursor(4, 1);
    rtui_print_data_width(data_width);
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_DOWN) {
    if (data_width <= 0) data_width = RTUI_DATA_WIDTHS;
    data_width--;
    rtui_set_cursor(4, 1);
    rtui_print_data_width(data_width);
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_LEFT) {
    pgm_prev();
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_RIGHT) {
    pgm_next();
    while (rtui_get_buttons());
    return;
  }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void addr_width_setup() {
  rtui_clear();
  rtui_print("Address Width");
  rtui_set_cursor(0, 1);
  rtui_print("\x06 ");
  rtui_print_addr_width(addr_width, data_width);
  rtui_print(" \x07");
}

void addr_width_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (buttons & RTUI_UP) {
    addr_width++;
    if (addr_width >= RTUI_ADDR_WIDTHS) addr_width = 0;
    rtui_set_cursor(2, 1);
    rtui_print_addr_width(addr_width, data_width);
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_DOWN) {
    if (addr_width <= 0) addr_width = RTUI_ADDR_WIDTHS;
    addr_width--;
    rtui_set_cursor(2, 1);
    rtui_print_addr_width(addr_width, data_width);
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_LEFT) {
    pgm_prev();
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_RIGHT) {
    pgm_next();
    while (rtui_get_buttons());
    return;
  }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void hex_format_setup() {
  rtui_clear();
  rtui_print("I/O Format");
  rtui_set_cursor(0, 1);
  rtui_print("\x06     ");
  rtui_print(hex_format ? "Hex " : "Raw ");
  rtui_print("     \x07");
}

void hex_format_loop() {
  unsigned char buttons = rtui_get_buttons();
  if ((buttons & RTUI_UP) || (buttons & RTUI_DOWN)) {
    hex_format = !hex_format;
    rtui_set_cursor(6, 1);
    rtui_print(hex_format ? "Hex " : "Raw ");
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_LEFT) {
    pgm_prev();
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_RIGHT) {
    pgm_next();
    while (rtui_get_buttons());
    return;
  }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void inspect_words_setup() {
  rtui_clear();
  rtui_print("Inspect Words");
  rtui_set_cursor(0, 1);
  rtui_print("  Press SELECT  ");
}

void inspect_words() {
  rtio_set_addr(addr);
  rtio_enable();
  unsigned int data0 = rtio_read_data();
  rtio_disable();
  unsigned long addr1 = addr + 1;
  if (addr1 >= addr_max) addr1 = 0;
  rtio_set_addr(addr1);
  rtio_enable();
  unsigned int data1 = rtio_read_data();
  rtio_disable();
  rtui_hide_cursor();
  rtui_set_cursor(0, 0);
  rtui_print_addr(addr);
  if (data_width) rtui_print_data_16(data0);
  else rtui_print_data_8(data0);
  rtui_set_cursor(0, 1);
  rtui_print_addr(addr1);
  if (data_width) rtui_print_data_16(data1);
  else rtui_print_data_8(data1);
  rtui_set_cursor(7 - addr_inc, 0);
  rtui_show_cursor();
}

void inspect_words_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (active) {
    if (buttons & RTUI_SELECT) {
      active = false;
      rtio_deactivate();
      rtui_hide_cursor();
      inspect_words_setup();
      while (rtui_get_buttons());
      return;
    }
    if (buttons & RTUI_UP) {
      addr += (1ul << (addr_inc << 2));
      while (addr >= addr_max) addr -= addr_max;
      inspect_words();
      delay(KEY_DELAY);
      while (rtui_get_buttons()) {
        addr += (1ul << (addr_inc << 2));
        while (addr >= addr_max) addr -= addr_max;
        inspect_words();
      }
      return;
    }
    if (buttons & RTUI_DOWN) {
      addr -= (1ul << (addr_inc << 2));
      while (addr >= addr_max) addr += addr_max;
      inspect_words();
      delay(KEY_DELAY);
      while (rtui_get_buttons()) {
        addr -= (1ul << (addr_inc << 2));
        while (addr >= addr_max) addr += addr_max;
        inspect_words();
      }
      return;
    }
    if (buttons & RTUI_LEFT) {
      addr_inc++;
      if (addr_inc >= 8) addr_inc = 0;
      rtui_set_cursor(7 - addr_inc, 0);
      while (rtui_get_buttons());
      return;
    }
    if (buttons & RTUI_RIGHT) {
      if (addr_inc <= 0) addr_inc = 8;
      addr_inc--;
      rtui_set_cursor(7 - addr_inc, 0);
      while (rtui_get_buttons());
      return;
    }
  } else {
    if (buttons & RTUI_SELECT) {
      active = true;
      addr_inc = 0;
      addr = 0;
      addr_max = rtui_get_addr_width(addr_width);
      rtio_read_mode();
      inspect_words();
      while (rtui_get_buttons());
      return;
    }
    if (buttons & RTUI_LEFT) {
      pgm_prev();
      while (rtui_get_buttons());
      return;
    }
    if (buttons & RTUI_RIGHT) {
      pgm_next();
      while (rtui_get_buttons());
      return;
    }
  }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void inspect_rows_setup() {
  rtui_clear();
  rtui_print("Inspect Rows");
  rtui_set_cursor(0, 1);
  rtui_print("  Press SELECT  ");
}

void inspect_rows() {
  rtui_hide_cursor();
  rtui_set_cursor(0, 0);
  rtui_print_addr(addr);
  if (data_width) {
    unsigned long addr1 = addr;
    unsigned int data[4];
    for (int i = 0; i < 4; i++) {
      rtio_set_addr(addr1);
      rtio_enable();
      data[i] = rtio_read_data();
      rtio_disable();
      addr1++;
      if (addr1 >= addr_max) addr1 = 0;
    }
    rtui_print_data_16x4(data);
  } else {
    unsigned long addr1 = addr;
    unsigned char data[8];
    for (int i = 0; i < 8; i++) {
      rtio_set_addr(addr1);
      rtio_enable();
      data[i] = rtio_read_data();
      rtio_disable();
      addr1++;
      if (addr1 >= addr_max) addr1 = 0;
    }
    rtui_print_data_8x8(data);
  }
  rtui_set_cursor(7 - addr_inc, 0);
  rtui_show_cursor();
}

void inspect_rows_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (active) {
    if (buttons & RTUI_SELECT) {
      active = false;
      rtio_deactivate();
      rtui_hide_cursor();
      inspect_rows_setup();
      while (rtui_get_buttons());
      return;
    }
    if (buttons & RTUI_UP) {
      addr += (1ul << (addr_inc << 2));
      while (addr >= addr_max) addr -= addr_max;
      inspect_rows();
      delay(KEY_DELAY);
      while (rtui_get_buttons()) {
        addr += (1ul << (addr_inc << 2));
        while (addr >= addr_max) addr -= addr_max;
        inspect_rows();
      }
      return;
    }
    if (buttons & RTUI_DOWN) {
      addr -= (1ul << (addr_inc << 2));
      while (addr >= addr_max) addr += addr_max;
      inspect_rows();
      delay(KEY_DELAY);
      while (rtui_get_buttons()) {
        addr -= (1ul << (addr_inc << 2));
        while (addr >= addr_max) addr += addr_max;
        inspect_rows();
      }
      return;
    }
    if (buttons & RTUI_LEFT) {
      addr_inc++;
      if (addr_inc >= 8) addr_inc = 0;
      rtui_set_cursor(7 - addr_inc, 0);
      while (rtui_get_buttons());
      return;
    }
    if (buttons & RTUI_RIGHT) {
      if (addr_inc <= 0) addr_inc = 8;
      addr_inc--;
      rtui_set_cursor(7 - addr_inc, 0);
      while (rtui_get_buttons());
      return;
    }
  } else {
    if (buttons & RTUI_SELECT) {
      active = true;
      addr_inc = 0;
      addr = 0;
      addr_max = rtui_get_addr_width(addr_width);
      rtio_read_mode();
      inspect_rows();
      while (rtui_get_buttons());
      return;
    }
    if (buttons & RTUI_LEFT) {
      pgm_prev();
      while (rtui_get_buttons());
      return;
    }
    if (buttons & RTUI_RIGHT) {
      pgm_next();
      while (rtui_get_buttons());
      return;
    }
  }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void dump_rom_setup() {
  rtui_clear();
  rtui_print("Dump ROM");
  rtui_set_cursor(0, 1);
  rtui_print("  Press SELECT  ");
}

void dump_rom_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (buttons & RTUI_SELECT) {
    unsigned long time = 0;
    unsigned int data;
    addr = 0;
    addr_max = rtui_get_addr_width(addr_width);
    rtui_clear();
    rtui_print("Dumping ROM\x08");
    rtio_read_mode();
    while (addr < addr_max) {
      if ((millis() - time) >= REF_DELAY) {
        time = millis();
        rtui_set_cursor(0, 1);
        rtui_print_addr(addr);
      }
      rtio_set_addr(addr);
      rtio_enable();
      data = rtio_read_data();
      rtio_disable();
      if (hex_format) {
        if (data_width == RTUI_DATA_WIDTH_16_BE) Serial.write(rtui_get_hex(data >> 8));
        Serial.write(rtui_get_hex(data));
        if (data_width == RTUI_DATA_WIDTH_16_LE) Serial.write(rtui_get_hex(data >> 8));
      } else {
        if (data_width == RTUI_DATA_WIDTH_16_BE) Serial.write(data >> 8);
        Serial.write(data);
        if (data_width == RTUI_DATA_WIDTH_16_LE) Serial.write(data >> 8);
      }
      addr++;
    }
    rtio_deactivate();
    dump_rom_setup();
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_LEFT) {
    pgm_prev();
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_RIGHT) {
    pgm_next();
    while (rtui_get_buttons());
    return;
  }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void program_rom_setup() {
  rtui_clear();
  rtui_print("Program ROM");
  rtui_set_cursor(0, 1);
  rtui_print("  Press SELECT  ");
}

void program_rom_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (buttons & RTUI_SELECT) {
    unsigned long time = 0;
    unsigned int data = 0;
    int subaddr = 0;
    int b;
    addr = 0;
    addr_max = rtui_get_addr_width(addr_width);
    rtui_clear();
    rtui_print("Programming ROM\x08");
    rtio_write_mode();
    while (addr < addr_max) {
      while (subaddr < 4) {
        if ((millis() - time) >= REF_DELAY) {
          time = millis();
          rtui_set_cursor(0, 1);
          rtui_print_addr(addr);
        }
        b = Serial.read();
        if (hex_format) {
          if (b >= '0' && b <= '9') b = b - '0';
          else if (b >= 'A' && b <= 'F') b = b - 'A' + 10;
          else if (b >= 'a' && b <= 'f') b = b - 'a' + 10;
          else continue;
          switch (data_width) {
            case RTUI_DATA_WIDTH_8:
              if (subaddr) data |= b;
              else data = (b << 4);
              subaddr += 2;
              break;
            case RTUI_DATA_WIDTH_16_LE:
              switch (subaddr) {
                case 0: data  = (b <<  4); break;
                case 1: data |= (b <<  0); break;
                case 2: data |= (b << 12); break;
                case 3: data |= (b <<  8); break;
              }
              subaddr++;
              break;
            case RTUI_DATA_WIDTH_16_BE:
              switch (subaddr) {
                case 0: data  = (b << 12); break;
                case 1: data |= (b <<  8); break;
                case 2: data |= (b <<  4); break;
                case 3: data |= (b <<  0); break;
              }
              subaddr++;
              break;
          }
        } else if (b >= 0) {
          switch (data_width) {
            case RTUI_DATA_WIDTH_8:
              data = b;
              subaddr += 4;
              break;
            case RTUI_DATA_WIDTH_16_LE:
              if (subaddr) data |= (b << 8);
              else data = b;
              subaddr += 2;
              break;
            case RTUI_DATA_WIDTH_16_BE:
              if (subaddr) data |= b;
              else data = (b << 8);
              subaddr += 2;
              break;
          }
        }
      }
      rtio_set_addr(addr);
      rtio_set_data(data);
      rtio_enable();
      rtio_disable();
      data = 0;
      subaddr = 0;
      addr++;
    }
    rtio_deactivate();
    program_rom_setup();
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_LEFT) {
    pgm_prev();
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_RIGHT) {
    pgm_next();
    while (rtui_get_buttons());
    return;
  }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void save_settings_setup() {
  rtui_clear();
  rtui_print("Save Settings");
  rtui_set_cursor(0, 1);
  rtui_print("\x06");
  rtui_print(eeprom_page_names[eeprom_page]);
  rtui_print("\x07");
  rtui_print(" Press SELECT");
}

void save_settings_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (buttons & RTUI_SELECT) {
    int ea = eeprom_page << 4;
    EEPROM.write(ea++, 0xB1);
    EEPROM.write(ea++, 0x27);
    EEPROM.write(ea++, data_width);
    EEPROM.write(ea++, addr_width);
    EEPROM.write(ea++, hex_format);
    EEPROM.write(ea++, rtui_get_backlight());
    rtui_set_cursor(4, 1);
    rtui_print("\x02\x02 Saved! \x02\x02");
    while (rtui_get_buttons());
    rtui_set_cursor(4, 1);
    rtui_print("Press SELECT");
    return;
  }
  if (buttons & RTUI_UP) {
    eeprom_page++;
    if (eeprom_page >= eeprom_pages) eeprom_page = 0;
    rtui_set_cursor(1, 1);
    rtui_print(eeprom_page_names[eeprom_page]);
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_DOWN) {
    if (eeprom_page <= 0) eeprom_page = eeprom_pages;
    eeprom_page--;
    rtui_set_cursor(1, 1);
    rtui_print(eeprom_page_names[eeprom_page]);
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_LEFT) {
    pgm_prev();
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_RIGHT) {
    pgm_next();
    while (rtui_get_buttons());
    return;
  }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void load_settings_setup() {
  rtui_clear();
  rtui_print("Load Settings");
  rtui_set_cursor(0, 1);
  rtui_print("\x06");
  rtui_print(eeprom_page_names[eeprom_page]);
  rtui_print("\x07");
  rtui_print(" Press SELECT");
}

void load_settings_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (buttons & RTUI_SELECT) {
    int ea = eeprom_page << 4;
    unsigned char m1 = EEPROM.read(ea++);
    unsigned char m2 = EEPROM.read(ea++);
    if (m1 == 0xB1 && m2 == 0x27) {
      data_width = EEPROM.read(ea++);
      addr_width = EEPROM.read(ea++);
      hex_format = EEPROM.read(ea++);
      rtui_set_backlight(EEPROM.read(ea++));
      rtui_set_cursor(4, 1);
      rtui_print("\x02\x02 Loaded \x02\x02");
    } else {
      rtui_set_cursor(4, 1);
      rtui_print("<File Empty>");
    }
    while (rtui_get_buttons());
    rtui_set_cursor(4, 1);
    rtui_print("Press SELECT");
    return;
  }
  if (buttons & RTUI_UP) {
    eeprom_page++;
    if (eeprom_page >= eeprom_pages) eeprom_page = 0;
    rtui_set_cursor(1, 1);
    rtui_print(eeprom_page_names[eeprom_page]);
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_DOWN) {
    if (eeprom_page <= 0) eeprom_page = eeprom_pages;
    eeprom_page--;
    rtui_set_cursor(1, 1);
    rtui_print(eeprom_page_names[eeprom_page]);
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_LEFT) {
    pgm_prev();
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_RIGHT) {
    pgm_next();
    while (rtui_get_buttons());
    return;
  }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void binary_counter_setup() {
  rtui_clear();
  rtui_print("Binary Counter");
  rtui_set_cursor(0, 1);
  rtui_print("  Press SELECT  ");
}

void binary_counter_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (buttons & RTUI_SELECT) {
    addr = 0;
    rtio_set_addr(0);
    rtui_set_cursor(0, 0);
    rtui_print("0000000000000000");
    rtui_set_cursor(0, 1);
    rtui_print("0000000000000000");
    while (rtui_get_buttons());
    while (!(rtui_get_buttons() & RTUI_SELECT)) {
      addr++;
      rtio_set_addr(addr);
      rtui_set_cursor(0, 0);
      for (int i = 31; i >= 16; i--) {
        rtui_print((addr & (1ul << i)) ? "1" : "0");
      }
      rtui_set_cursor(0, 1);
      for (int i = 15; i >= 0; i--) {
        rtui_print((addr & (1ul << i)) ? "1" : "0");
      }
    }
    binary_counter_setup();
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_LEFT) {
    pgm_prev();
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_RIGHT) {
    pgm_next();
    while (rtui_get_buttons());
    return;
  }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void logic_probe_setup() {
  rtui_clear();
  rtui_print("Logic Probe");
  rtui_set_cursor(0, 1);
  rtui_print("  Press SELECT  ");
}

void logic_probe_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (buttons & RTUI_SELECT) {
    unsigned int data = rtio_read_data();
    rtui_set_cursor(0, 0);
    for (int i = 15; i >= 0; i--) {
      rtui_print((data & (1 << i)) ? "1" : "0");
    }
    rtui_set_cursor(0, 1);
    rtui_print("    ");
    rtui_print_data_16(data);
    rtui_print("    ");
    while (rtui_get_buttons());
    while (!(rtui_get_buttons() & RTUI_SELECT)) {
      data = rtio_read_data();
      rtui_set_cursor(0, 0);
      for (int i = 15; i >= 0; i--) {
        rtui_print((data & (1 << i)) ? "1" : "0");
      }
      rtui_set_cursor(4, 1);
      rtui_print_data_16(data);
    }
    logic_probe_setup();
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_LEFT) {
    pgm_prev();
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_RIGHT) {
    pgm_next();
    while (rtui_get_buttons());
    return;
  }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void character_chart_setup() {
  rtui_clear();
  rtui_print("Character Chart");
  rtui_set_cursor(0, 1);
  rtui_print("  Press SELECT  ");
}

void character_chart() {
  char buf[17]; buf[16] = 0;
  for (int i = 0; i < 16; i++) {
    buf[i] = (addr + i) & 0xFF;
    if (!buf[i]) buf[i] = 0x08;
  }
  rtui_set_cursor(0, 0);
  rtui_print(buf);
  for (int i = 0, j = 16; i < 16; i++, j++) {
    buf[i] = (addr + j) & 0xFF;
    if (!buf[i]) buf[i] = 0x08;
  }
  rtui_set_cursor(0, 1);
  rtui_print(buf);
}

void character_chart_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (active) {
    if (buttons & RTUI_SELECT) {
      active = false;
      character_chart_setup();
      while (rtui_get_buttons());
      return;
    }
    if (buttons & RTUI_UP) {
      addr -= 0x10;
      addr &= 0xFF;
      character_chart();
      while (rtui_get_buttons());
      return;
    }
    if (buttons & RTUI_DOWN) {
      addr += 0x10;
      addr &= 0xFF;
      character_chart();
      while (rtui_get_buttons());
      return;
    }
  } else {
    if (buttons & RTUI_SELECT) {
      active = true;
      addr = 0x20;
      character_chart();
      while (rtui_get_buttons());
      return;
    }
    if (buttons & RTUI_LEFT) {
      pgm_prev();
      while (rtui_get_buttons());
      return;
    }
    if (buttons & RTUI_RIGHT) {
      pgm_next();
      while (rtui_get_buttons());
      return;
    }
  }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void party_mode_setup() {
  rtui_clear();
  rtui_print("Party Mode");
  rtui_set_cursor(0, 1);
  rtui_print("  Press SELECT  ");
}

void party_mode_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (buttons & RTUI_SELECT) {
    unsigned long time = 0;
    unsigned char b0 = rtui_get_backlight();
    unsigned char b1 = b0;
    unsigned char b2 = b1;
    randomSeed(millis());
    rtui_clear();
    while (rtui_get_buttons());
    while (!(rtui_get_buttons() & RTUI_SELECT)) {
      if ((millis() - time) >= 500) {
        time = millis();
        while (b2 == RTUI_OFF || b2 == b1) b2 = random(0, RTUI_COLORS);
        rtui_set_backlight((b1 = b2));
        rtui_clear();
        for (int i = 0; i < 4; i++) {
          rtui_set_cursor(random(0, RTUI_COLUMNS), random(0, RTUI_ROWS));
          rtui_print("\x02");
        }
      }
    }
    rtui_set_backlight(b0);
    party_mode_setup();
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_LEFT) {
    pgm_prev();
    while (rtui_get_buttons());
    return;
  }
  if (buttons & RTUI_RIGHT) {
    pgm_next();
    while (rtui_get_buttons());
    return;
  }
}
