#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include "rtio.h"
#include "rtui.h"

#define NUM_PGM         16
#define SER_BUF_SIZE  1024
#define KEY_DELAY      500
#define REF_DELAY      200

int cur_pgm = 0;
char ser_buf[SER_BUF_SIZE];
int ser_buf_pos = 0;

int data_width = RTUI_DATA_WIDTH_8;
int addr_width = RTUI_ADDR_WIDTH_16;
int io_delay = 0;
int hex_format = false;

int active = false;
int addr_inc;
unsigned long addr;
unsigned long addr_max;
unsigned long intel_hex_origin = 0;

int eeprom_page = 0;
int eeprom_pages = 16;
char * eeprom_page_names[16] = {
  "0", "1", "2", "3", "4", "5", "6", "7",
  "8", "9", "A", "B", "C", "D", "E", "F",
};

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void setup() {
  Serial.begin(250000);
  rtio_init();
  rtui_init();
  pgm_setup();
}

void pgm_setup() {
  switch (cur_pgm) {
    case  0: hello_setup(); break;
    case  1: data_width_setup(); break;
    case  2: addr_width_setup(); break;
    case  3: io_delay_setup(); break;
    case  4: hex_format_setup(); break;
    case  5: inspect_words_setup(); break;
    case  6: inspect_rows_setup(); break;
    case  7: dump_rom_setup(); break;
    case  8: program_rom_setup(); break;
    case  9: binary_counter_setup(); break;
    case 10: logic_probe_setup(); break;
    case 11: self_test_setup(); break;
    case 12: character_chart_setup(); break;
    case 13: party_mode_setup(); break;
    case 14: save_settings_setup(); break;
    case 15: load_settings_setup(); break;
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
  if (!active && Serial.available() > 0) {
    char b = Serial.read();
    if (b == 0x0A || b == 0x0D) {
      ser_buf[ser_buf_pos] = 0;
      serial_command();
      ser_buf_pos = 0;
    } else if (b && ser_buf_pos < (SER_BUF_SIZE - 1)) {
      ser_buf[ser_buf_pos] = b;
      ser_buf_pos++;
    }
  }
  switch (cur_pgm) {
    case  0: hello_loop(); break;
    case  1: data_width_loop(); break;
    case  2: addr_width_loop(); break;
    case  3: io_delay_loop(); break;
    case  4: hex_format_loop(); break;
    case  5: inspect_words_loop(); break;
    case  6: inspect_rows_loop(); break;
    case  7: dump_rom_loop(); break;
    case  8: program_rom_loop(); break;
    case  9: binary_counter_loop(); break;
    case 10: logic_probe_loop(); break;
    case 11: self_test_loop(); break;
    case 12: character_chart_loop(); break;
    case 13: party_mode_loop(); break;
    case 14: save_settings_loop(); break;
    case 15: load_settings_loop(); break;
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

void io_delay_print() {
  char buf[9];
  buf[0] = (io_delay >= 10000) ? (((io_delay / 10000) % 10) + '0') : ' ';
  buf[1] = (io_delay >=  1000) ? (((io_delay /  1000) % 10) + '0') : ' ';
  buf[2] = (io_delay >=   100) ? (((io_delay /   100) % 10) + '0') : ' ';
  buf[3] = (io_delay >=    10) ? (((io_delay /    10) % 10) + '0') : ' ';
  buf[4] = (io_delay >=     0) ? (((io_delay /     1) % 10) + '0') : ' ';
  buf[5] = ' ';
  buf[6] = 'u';
  buf[7] = 's';
  buf[8] = 0;
  rtui_print(buf);
}

void io_delay_setup() {
  rtui_clear();
  rtui_print("I/O Delay");
  rtui_set_cursor(0, 1);
  rtui_print("\x06   ");
  io_delay_print();
  rtui_print("   \x07");
}

void io_delay_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (buttons & RTUI_UP) {
    io_delay += 5;
    if (io_delay > 10000) io_delay = 10000;
    rtui_set_cursor(4, 1);
    io_delay_print();
    delay(KEY_DELAY);
    while (rtui_get_buttons()) {
      io_delay += 5;
      if (io_delay > 10000) io_delay = 10000;
      rtui_set_cursor(4, 1);
      io_delay_print();
    }
    return;
  }
  if (buttons & RTUI_DOWN) {
    io_delay -= 5;
    if (io_delay < 0) io_delay = 0;
    rtui_set_cursor(4, 1);
    io_delay_print();
    delay(KEY_DELAY);
    while (rtui_get_buttons()) {
      io_delay -= 5;
      if (io_delay < 0) io_delay = 0;
      rtui_set_cursor(4, 1);
      io_delay_print();
    }
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
  if (io_delay) delayMicroseconds(io_delay);
  unsigned int data0 = rtio_read_data();
  rtio_disable();
  unsigned long addr1 = addr + 1;
  if (addr1 >= addr_max) addr1 = 0;
  rtio_set_addr(addr1);
  rtio_enable();
  if (io_delay) delayMicroseconds(io_delay);
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
      if (io_delay) delayMicroseconds(io_delay);
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
      if (io_delay) delayMicroseconds(io_delay);
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

void dump_rom(unsigned long i, unsigned long j) {
  unsigned long time = 0;
  unsigned int data;
  rtui_clear();
  rtui_print("Dumping ROM\x08");
  rtio_read_mode();
  for (addr = i; addr <= j; addr++) {
    if ((millis() - time) >= REF_DELAY) {
      time = millis();
      rtui_set_cursor(0, 1);
      rtui_print_addr(addr);
    }
    rtio_set_addr(addr);
    rtio_enable();
    if (io_delay) delayMicroseconds(io_delay);
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
  }
  rtio_deactivate();
}

void dump_rom_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (buttons & RTUI_SELECT) {
    dump_rom(0, rtui_get_addr_width(addr_width) - 1);
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

void program_rom(unsigned long i, unsigned long j) {
  unsigned long time = 0;
  unsigned int data = 0;
  int subaddr = 0;
  int b;
  rtui_clear();
  rtui_print("Programming ROM\x08");
  rtio_write_mode();
  for (addr = i; addr <= j; addr++) {
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
    if (io_delay) delayMicroseconds(io_delay);
    rtio_disable();
    data = 0;
    subaddr = 0;
  }
  rtio_deactivate();
}

void program_rom_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (buttons & RTUI_SELECT) {
    program_rom(0, rtui_get_addr_width(addr_width) - 1);
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

void save_settings() {
  int ea = eeprom_page << 4;
  EEPROM.write(ea++, 0xB1);
  EEPROM.write(ea++, 0x27);
  EEPROM.write(ea++, data_width);
  EEPROM.write(ea++, addr_width);
  EEPROM.write(ea++, hex_format);
  EEPROM.write(ea++, rtui_get_backlight());
  EEPROM.write(ea++, io_delay >> 8);
  EEPROM.write(ea++, io_delay);
}

void save_settings_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (buttons & RTUI_SELECT) {
    save_settings();
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

int load_settings() {
    int ea = eeprom_page << 4;
    unsigned char m1 = EEPROM.read(ea++);
    unsigned char m2 = EEPROM.read(ea++);
    if (m1 == 0xB1 && m2 == 0x27) {
      data_width = EEPROM.read(ea++);
      addr_width = EEPROM.read(ea++);
      hex_format = EEPROM.read(ea++);
      rtui_set_backlight(EEPROM.read(ea++));
      io_delay = EEPROM.read(ea++);
      io_delay <<= 8;
      io_delay |= EEPROM.read(ea++);
      if (io_delay < 0) io_delay = 0;
      return true;
    } else {
      return false;
    }
}

void load_settings_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (buttons & RTUI_SELECT) {
    if (load_settings()) {
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

void self_test_setup() {
  rtui_clear();
  rtui_print("Self Test");
  rtui_set_cursor(0, 1);
  rtui_print("  Press SELECT  ");
}

void self_test_loop() {
  unsigned char buttons = rtui_get_buttons();
  if (buttons & RTUI_SELECT) {
    int i;
    unsigned long am;
    unsigned int dm;
    unsigned int data;
    char failures[17];
    for (i = 0; i < 16; i++) failures[i] = '0';
    failures[16] = 0;
    randomSeed(millis());
    rtui_clear();
    rtui_print("Failures:");
    rtui_set_cursor(0, 1);
    rtui_print(failures);
    while (rtui_get_buttons());
    while (!(rtui_get_buttons() & RTUI_SELECT)) {
      data = random(0, 0x100);
      data <<= 8;
      data |= random(0, 0x100);
      addr = data;
      for (am = 0x8000L, dm = 0x8000; dm; dm >>= 1, am <<= 1L) {
        if (data & dm) addr |= am;
      }
      rtio_set_addr(addr);
      data ^= rtio_read_data();
      for (i = 15, dm = 0x8000; dm; dm >>= 1, i--) {
        if (data & dm) {
          switch (failures[i]) {
            case '!': break;
            case '9': failures[i] = 'A'; break;
            case 'Z': failures[i] = '!'; break;
            default: failures[i]++; break;
          }
        }
      }
      if (data) {
        rtui_set_cursor(0, 1);
        rtui_print(failures);
      }
    }
    self_test_setup();
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

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

int free_ram() {
  extern int __heap_start, * __brkval; int v;
  return (int)&v - ((__brkval == 0) ? (int)&__heap_start : (int)__brkval);
}

int digit(char ch) {
  if (ch >= '0' && ch <= '9') return ch - '0';
  else if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 10;
  else if (ch >= 'a' && ch <= 'z') return ch - 'a' + 10;
  return -1;
}

int log2ish(int v) {
  switch (v) {
    case 0x0001: return  0;
    case 0x0002: return  2;
    case 0x0003: return  3;
    case 0x0004: return  4;
    case 0x0006: return  5;
    case 0x0008: return  6;
    case 0x000C: return  7;
    case 0x0010: return  8;
    case 0x0018: return  9;
    case 0x0020: return 10;
    case 0x0030: return 11;
    case 0x0040: return 12;
    case 0x0060: return 13;
    case 0x0080: return 14;
    case 0x00C0: return 15;
    case 0x0100: return 16;
    case 0x0180: return 17;
    case 0x0200: return 18;
    case 0x0300: return 19;
    case 0x0400: return 20;
    case 0x0600: return 21;
    case 0x0800: return 22;
    case 0x0C00: return 23;
    case 0x1000: return 24;
    case 0x1800: return 25;
    case 0x2000: return 26;
    case 0x3000: return 27;
    case 0x4000: return 28;
    case 0x6000: return 29;
    case 0x8000: return 30;
    case 0xC000: return 31;
    default: return -1;
  }
}

void serial_dump_rom(unsigned long i, unsigned long j) {
  int ds, de;
  unsigned int data[16];
  rtio_read_mode();
  for (addr = i; addr <= j; addr++) {
    if (addr == i || (addr & 0xF) == 0) {
      ds = (addr & 0xF);
      Serial.print(rtui_get_hex(addr >> 24));
      Serial.print(rtui_get_hex(addr >> 16));
      Serial.print(rtui_get_hex(addr >>  8));
      Serial.print(rtui_get_hex(addr));
      Serial.print(":");
    }
    de = (addr & 0xF);
    rtio_set_addr(addr);
    rtio_enable();
    if (io_delay) delayMicroseconds(io_delay);
    data[de] = rtio_read_data();
    rtio_disable();
    Serial.print(" ");
    if (data_width) Serial.print(rtui_get_hex(data[de] >> 8));
    Serial.print(rtui_get_hex(data[de]));
    if (addr == j || (addr & 0xF) == 0xF) {
      Serial.print("  ");
      while (ds <= de) {
        if (data_width == RTUI_DATA_WIDTH_16_BE) Serial.print(rtui_get_chr(data[ds] >> 8));
        Serial.print(rtui_get_chr(data[ds]));
        if (data_width == RTUI_DATA_WIDTH_16_LE) Serial.print(rtui_get_chr(data[ds] >> 8));
        ds++;
      }
      Serial.println();
    }
  }
  rtio_deactivate();
}

void serial_program_rom(unsigned long origin, char * buf, int count) {
  unsigned int data = 0;
  int subaddr = 0;
  int written = 0;
  addr = origin;
  rtio_write_mode();
  while ((*buf) && (count > 0)) {
    while ((*buf) && (subaddr < 4)) {
      int b = *buf++;
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
    }
    rtio_set_addr(addr);
    rtio_set_data(data);
    rtio_enable();
    if (io_delay) delayMicroseconds(io_delay);
    rtio_disable();
    data = 0;
    subaddr = 0;
    written += (data_width ? 2 : 1);
    count -= (data_width ? 2 : 1);
    addr++;
  }
  rtio_deactivate();
  Serial.print("Wrote ");
  Serial.print(written);
  Serial.println(" bytes");
}

void serial_command() {
  int d, i = 0;
  while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
  char cmd = ser_buf[i++];
  switch (cmd) {
    case '!':
      Serial.println(&ser_buf[i]);
      break;
    case 'b':
      while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
      d = digit(ser_buf[i]);
      if (d >= 0 && d < 10) {
        int p = d; i++;
        d = digit(ser_buf[i]);
        while (d >= 0 && d < 10) {
          p = p * 10 + d; i++;
          d = digit(ser_buf[i]);
        }
        if (p >= 0 && p < RTUI_COLORS) {
          rtui_set_backlight(p);
          Serial.println("OK");
          break;
        }
      }
      Serial.println(rtui_get_backlight());
      break;
    case 'd':
      while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
      if (ser_buf[i] == '8') {
        data_width = RTUI_DATA_WIDTH_8;
        Serial.println("OK");
        break;
      }
      if (ser_buf[i] == '1') {
        i++;
        if (ser_buf[i] == '6') {
          i++;
          while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
          if (ser_buf[i] == 'L' || ser_buf[i] == 'l') {
            data_width = RTUI_DATA_WIDTH_16_LE;
            Serial.println("OK");
            break;
          }
          if (ser_buf[i] == 'B' || ser_buf[i] == 'b') {
            data_width = RTUI_DATA_WIDTH_16_BE;
            Serial.println("OK");
            break;
          }
        }
      }
      switch (data_width) {
        case RTUI_DATA_WIDTH_8: Serial.println("8"); break;
        case RTUI_DATA_WIDTH_16_LE: Serial.println("16 LE"); break;
        case RTUI_DATA_WIDTH_16_BE: Serial.println("16 BE"); break;
      }
      break;
    case 'a':
      while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
      d = digit(ser_buf[i]);
      if (d >= 0 && d < 10) {
        int p = d; i++;
        d = digit(ser_buf[i]);
        while (d >= 0 && d < 10) {
          p = p * 10 + d; i++;
          d = digit(ser_buf[i]);
        }
        if (ser_buf[i] == 'B' || ser_buf[i] == 'b') {
          p = log2ish(p);
          if (p >= 0) p += (data_width ? -18 : -16);
        } else if (ser_buf[i] == 'K' || ser_buf[i] == 'k') {
          p = log2ish(p);
          if (p >= 0) p += (data_width ? 2 : 4);
        } else if (ser_buf[i] == 'M' || ser_buf[i] == 'm') {
          p = log2ish(p);
          if (p >= 0) p += (data_width ? 22 : 24);
        } else if (ser_buf[i] == 'G' || ser_buf[i] == 'g') {
          p = log2ish(p);
          if (p >= 0) p += (data_width ? 42 : 44);
        } else {
          p = (p - 8) << 1;
          if (ser_buf[i] == '.' || ser_buf[i] == '+') p++;
          else if (ser_buf[i] == '-') p--;
        }
        if (p >= 0 && p < RTUI_ADDR_WIDTHS) {
          addr_width = p;
          Serial.println("OK");
          break;
        }
      }
      if (addr_width & 1) {
        Serial.print((addr_width >> 1) + 8);
        Serial.println(".5");
      } else {
        Serial.println((addr_width >> 1) + 8);
      }
      break;
    case 'y':
      while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
      d = digit(ser_buf[i]);
      if (d >= 0 && d < 10) {
        int p = d; i++;
        d = digit(ser_buf[i]);
        while (d >= 0 && d < 10) {
          p = p * 10 + d; i++;
          d = digit(ser_buf[i]);
        }
        if (p >= 0 && p <= 10000) {
          io_delay = p;
          Serial.println("OK");
          break;
        }
      }
      Serial.println(io_delay);
      break;
    case 'f':
      while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
      if (ser_buf[i] == 'B' || ser_buf[i] == 'b' || ser_buf[i] == 'R' || ser_buf[i] == 'r') {
        hex_format = false;
        Serial.println("OK");
        break;
      }
      if (ser_buf[i] == 'H' || ser_buf[i] == 'h') {
        hex_format = true;
        Serial.println("OK");
        break;
      }
      Serial.println(hex_format ? "Hex" : "Raw");
      break;
    case 'i':
      while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
      d = digit(ser_buf[i]);
      if (d >= 0 && d < 16) {
        unsigned long st = d; i++;
        d = digit(ser_buf[i]);
        while (d >= 0 && d < 16) {
          st = (st << 4) | d; i++;
          d = digit(ser_buf[i]);
        }
        while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
        d = digit(ser_buf[i]);
        if (d >= 0 && d < 16) {
          unsigned long en = d; i++;
          d = digit(ser_buf[i]);
          while (d >= 0 && d < 16) {
            en = (en << 4) | d; i++;
            d = digit(ser_buf[i]);
          }
          serial_dump_rom(st, en);
          break;
        }
        serial_dump_rom(st, st);
        break;
      }
      serial_dump_rom(addr, addr | 0xF);
      break;
    case 'w':
      while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
      d = digit(ser_buf[i]);
      if (d >= 0 && d < 16) {
        unsigned long st = d; i++;
        d = digit(ser_buf[i]);
        while (d >= 0 && d < 16) {
          st = (st << 4) | d; i++;
          d = digit(ser_buf[i]);
        }
        serial_program_rom(st, &ser_buf[i], ser_buf_pos - i);
        break;
      }
      break;
    case 'M':
      Serial.println(rtui_get_addr_width(addr_width) - 1, HEX);
      break;
    case 'D':
      while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
      d = digit(ser_buf[i]);
      if (d >= 0 && d < 16) {
        unsigned long st = d; i++;
        d = digit(ser_buf[i]);
        while (d >= 0 && d < 16) {
          st = (st << 4) | d; i++;
          d = digit(ser_buf[i]);
        }
        while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
        d = digit(ser_buf[i]);
        if (d >= 0 && d < 16) {
          unsigned long en = d; i++;
          d = digit(ser_buf[i]);
          while (d >= 0 && d < 16) {
            en = (en << 4) | d; i++;
            d = digit(ser_buf[i]);
          }
          dump_rom(st, en);
          pgm_setup();
          Serial.println();
          Serial.println("OK");
          break;
        }
        dump_rom(st, rtui_get_addr_width(addr_width) - 1);
        pgm_setup();
        Serial.println();
        Serial.println("OK");
        break;
      }
      dump_rom(0, rtui_get_addr_width(addr_width) - 1);
      pgm_setup();
      Serial.println();
      Serial.println("OK");
      break;
    case 'P':
      while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
      d = digit(ser_buf[i]);
      if (d >= 0 && d < 16) {
        unsigned long st = d; i++;
        d = digit(ser_buf[i]);
        while (d >= 0 && d < 16) {
          st = (st << 4) | d; i++;
          d = digit(ser_buf[i]);
        }
        while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
        d = digit(ser_buf[i]);
        if (d >= 0 && d < 16) {
          unsigned long en = d; i++;
          d = digit(ser_buf[i]);
          while (d >= 0 && d < 16) {
            en = (en << 4) | d; i++;
            d = digit(ser_buf[i]);
          }
          program_rom(st, en);
          pgm_setup();
          Serial.println("OK");
          break;
        }
        program_rom(st, rtui_get_addr_width(addr_width) - 1);
        pgm_setup();
        Serial.println("OK");
        break;
      }
      program_rom(0, rtui_get_addr_width(addr_width) - 1);
      pgm_setup();
      Serial.println("OK");
      break;
    case 's':
      while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
      d = digit(ser_buf[i]);
      if (d >= 0 && d < eeprom_pages) {
        eeprom_page = d;
        save_settings();
        Serial.println("OK");
        break;
      }
      Serial.println(eeprom_page_names[eeprom_page]);
      break;
    case 'r':
      while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
      d = digit(ser_buf[i]);
      if (d >= 0 && d < eeprom_pages) {
        eeprom_page = d;
        if (load_settings()) {
          Serial.println("OK");
        } else {
          Serial.println("File Empty");
        }
        break;
      }
      Serial.println(eeprom_page_names[eeprom_page]);
      break;
    case 'A':
      while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
      d = digit(ser_buf[i]);
      if (d >= 0 && d < 16) {
        unsigned long st = d; i++;
        d = digit(ser_buf[i]);
        while (d >= 0 && d < 16) {
          st = (st << 4) | d; i++;
          d = digit(ser_buf[i]);
        }
        rtio_set_addr(addr = st);
        for (int i = 31; i >= 0; i--) {
          Serial.print((addr & (1ul << i)) ? "1" : "0");
        }
        Serial.println();
      }
      break;
    case 'Q':
      d = rtio_read_data();
      for (int i = 15; i >= 0; i--) {
        Serial.print((d & (1ul << i)) ? "1" : "0");
      }
      Serial.print("  ");
      Serial.print(rtui_get_hex(d >> 8));
      Serial.print(rtui_get_hex(d));
      Serial.print("  ");
      Serial.print(rtui_get_chr(d >> 8));
      Serial.print(rtui_get_chr(d));
      Serial.println();
      break;
    case 'c':
      while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
      if (ser_buf[i] == 'S' || ser_buf[i] == 's') {
        rtui_show_cursor();
        Serial.println("OK");
        break;
      }
      if (ser_buf[i] == 'H' || ser_buf[i] == 'h') {
        rtui_hide_cursor();
        Serial.println("OK");
        break;
      }
      d = digit(ser_buf[i]);
      if (d >= 0 && d < 10) {
        int p = d; i++;
        d = digit(ser_buf[i]);
        while (d >= 0 && d < 10) {
          p = p * 10 + d; i++;
          d = digit(ser_buf[i]);
        }
        while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
        d = digit(ser_buf[i]);
        if (d >= 0 && d < 10) {
          int q = d; i++;
          d = digit(ser_buf[i]);
          while (d >= 0 && d < 10) {
            q = q * 10 + d; i++;
            d = digit(ser_buf[i]);
          }
          rtui_set_cursor(p, q);
          Serial.println("OK");
          break;
        }
        rtui_set_cursor(0, p);
        Serial.println("OK");
        break;
      }
      rtui_clear();
      Serial.println("OK");
      break;
    case 'p':
      rtui_print(&ser_buf[i]);
      Serial.println("OK");
      break;
    case 'm':
      while (ser_buf[i] > 0 && ser_buf[i] < 33) i++;
      if (ser_buf[i] == '+') {
        rtui_hide_cursor();
        pgm_next();
        Serial.println("OK");
        break;
      }
      if (ser_buf[i] == '-') {
        rtui_hide_cursor();
        pgm_prev();
        Serial.println("OK");
        break;
      }
      d = digit(ser_buf[i]);
      if (d >= 0 && d < 10) {
        int p = d; i++;
        d = digit(ser_buf[i]);
        while (d >= 0 && d < 10) {
          p = p * 10 + d; i++;
          d = digit(ser_buf[i]);
        }
        if (p >= 0 && p < NUM_PGM) {
          cur_pgm = p;
        }
      }
      rtui_hide_cursor();
      pgm_setup();
      Serial.println("OK");
      break;
    case 'v':
      Serial.println("3");
      break;
    case 'z':
      Serial.println(free_ram());
      break;
    case 'S':
      /* Motorola SREC Format */
      d = digit(ser_buf[i]);
      if (d >= 0 && d < 10) {
        int type = d; i++;
        d = digit(ser_buf[i]);
        if (d >= 0 && d < 16) {
          int count = (d << 4); i++;
          d = digit(ser_buf[i]);
          if (d >= 0 && d < 16) {
            count |= d; i++;
            unsigned long origin = 0;
            switch (type) {
              case 3:
                d = digit(ser_buf[i++]);
                if (d < 0 || d >= 16) break;
                origin = (origin << 4) | d;
                d = digit(ser_buf[i++]);
                if (d < 0 || d >= 16) break;
                origin = (origin << 4) | d;
                /* fallthrough; */
              case 2:
                d = digit(ser_buf[i++]);
                if (d < 0 || d >= 16) break;
                origin = (origin << 4) | d;
                d = digit(ser_buf[i++]);
                if (d < 0 || d >= 16) break;
                origin = (origin << 4) | d;
                /* fallthrough; */
              case 1:
                d = digit(ser_buf[i++]);
                if (d < 0 || d >= 16) break;
                origin = (origin << 4) | d;
                d = digit(ser_buf[i++]);
                if (d < 0 || d >= 16) break;
                origin = (origin << 4) | d;
                d = digit(ser_buf[i++]);
                if (d < 0 || d >= 16) break;
                origin = (origin << 4) | d;
                d = digit(ser_buf[i++]);
                if (d < 0 || d >= 16) break;
                origin = (origin << 4) | d;
                serial_program_rom(
                  (data_width ? (origin >> 1) : origin),
                  &ser_buf[i], (count - type) - 2
                );
                break;
              default:
                Serial.println("OK");
                break;
            }
          }
        }
      }
      break;
    case ':':
      /* Intel HEX Format */
      d = digit(ser_buf[i]);
      if (d >= 0 && d < 16) {
        int count = (d << 4); i++;
        d = digit(ser_buf[i]);
        if (d >= 0 && d < 16) {
          count |= d; i++;
          d = digit(ser_buf[i]);
          if (d >= 0 && d < 16) {
            unsigned long offset = (d << 12); i++;
            d = digit(ser_buf[i]);
            if (d >= 0 && d < 16) {
              offset |= (d << 8); i++;
              d = digit(ser_buf[i]);
              if (d >= 0 && d < 16) {
                offset |= (d << 4); i++;
                d = digit(ser_buf[i]);
                if (d >= 0 && d < 16) {
                  offset |= d; i++;
                  d = digit(ser_buf[i]);
                  if (d == 0) {
                    int type = (d << 4); i++;
                    d = digit(ser_buf[i]);
                    if (d >= 0 && d <= 5) {
                      type |= d; i++;
                      switch (type) {
                        case 0:
                          serial_program_rom(
                            (data_width
                              ? ((intel_hex_origin + offset) >> 1)
                              : (intel_hex_origin + offset)),
                            &ser_buf[i], count
                          );
                          break;
                        case 2:
                          count <<= 1; offset = 0;
                          d = digit(ser_buf[i]);
                          while (count > 0 && d >= 0 && d < 16) {
                            count--; offset = (offset << 4) | d;
                            i++; d = digit(ser_buf[i]);
                          }
                          intel_hex_origin = offset << 4;
                          Serial.print("Origin set to ");
                          Serial.println(intel_hex_origin, HEX);
                          break;
                        case 3:
                          count <<= 1; offset = 0;
                          d = digit(ser_buf[i]);
                          while (count > 0 && d >= 0 && d < 16) {
                            count--; offset = (offset << 4) | d;
                            i++; d = digit(ser_buf[i]);
                          }
                          intel_hex_origin = ((offset >> 16) << 4) + (offset & 0xFFFF);
                          Serial.print("Origin set to ");
                          Serial.println(intel_hex_origin, HEX);
                          break;
                        case 4:
                          count <<= 1; offset = 0;
                          d = digit(ser_buf[i]);
                          while (count > 0 && d >= 0 && d < 16) {
                            count--; offset = (offset << 4) | d;
                            i++; d = digit(ser_buf[i]);
                          }
                          intel_hex_origin = offset << 16;
                          Serial.print("Origin set to ");
                          Serial.println(intel_hex_origin, HEX);
                          break;
                        case 5:
                          count <<= 1; offset = 0;
                          d = digit(ser_buf[i]);
                          while (count > 0 && d >= 0 && d < 16) {
                            count--; offset = (offset << 4) | d;
                            i++; d = digit(ser_buf[i]);
                          }
                          intel_hex_origin = offset;
                          Serial.print("Origin set to ");
                          Serial.println(intel_hex_origin, HEX);
                          break;
                        default:
                          Serial.println("OK");
                          break;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      break;
    case '%':
      /* Tektronix Extended HEX Format */
      d = digit(ser_buf[i]);
      if (d >= 0 && d < 16) {
        int count = (d << 4); i++;
        d = digit(ser_buf[i]);
        if (d >= 0 && d < 16) {
          count |= d; i++;
          d = digit(ser_buf[i]);
          if (d == 6 || d == 8) {
            int type = d; i++;
            d = digit(ser_buf[i]);
            if (d >= 0 && d < 16) {
              int checksum = (d << 4); i++;
              d = digit(ser_buf[i]);
              if (d >= 0 && d < 16) {
                checksum |= d; i++;
                d = digit(ser_buf[i]);
                if (d >= 0 && d < 16) {
                  int addr_length = d; i++;
                  unsigned long origin = 0;
                  d = digit(ser_buf[i]);
                  while (addr_length > 0 && d >= 0 && d < 16) {
                    addr_length--; origin = (origin << 4) | d;
                    i++; d = digit(ser_buf[i]);
                  }
                  switch (type) {
                    case 6:
                      serial_program_rom(
                        (data_width ? (origin >> 1) : origin),
                        &ser_buf[i], count >> 1
                      );
                      break;
                    default:
                      Serial.println("OK");
                      break;
                  }
                }
              }
            }
          }
        }
      }
      break;
    case '?':
      Serial.println("Beckie's ROM Tool Serial Interface");
      Serial.println("![<string>]         Echo string over serial");
      Serial.println("b[<color>]          Report or set backlight color (0, 1, ..., 7)");
      Serial.println("d[<width>]          Report or set data width (8, 16 LE, 16 BE)");
      Serial.println("a[<width>]          Report or set address width (8, 8.5, ..., 31)");
      Serial.println("y[<delay>]          Report or set I/O delay in microseconds (0 - 10000)");
      Serial.println("f[<format>]         Report or set I/O format for D and P (Raw, Hex)");
      Serial.println("i[<addr>[ <addr>]]  Print hex dump of specified range of ROM");
      Serial.println("w<addr>[ <data>]    Program ROM using plain address and hex data");
      Serial.println("S<rest-of-record>   Program ROM using Motorola SREC record");
      Serial.println(":<rest-of-record>   Program ROM using Intel HEX record");
      Serial.println("%<rest-of-record>   Program ROM using Tektronix extended HEX record");
      Serial.println("M                   Report maximum address (inclusive) in hex");
      Serial.println("D[<addr>[ <addr>]]  Start dumping specified range or entire ROM over serial");
      Serial.println("P[<addr>[ <addr>]]  Start programming specified range or entire ROM over serial");
      Serial.println("s<slot>             Save settings to Arduino EEPROM (0, 1, ..., F)");
      Serial.println("r<slot>             Load settings from Arduino EEPROM (0, 1, ..., F)");
      Serial.println("A<addr>             Set value on address bus (binary counter)");
      Serial.println("Q                   Print value on data bus (logic probe)");
      Serial.println("c, cs, ch           Clear LCD, show cursor, hide cursor");
      Serial.println("c[<column> ]<row>   Set LCD cursor position");
      Serial.println("p[<string>]         Print string on LCD");
      Serial.println("m                   Return to menu display");
      break;
  }
}
