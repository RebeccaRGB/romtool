#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include "rtui.h"

static Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
static unsigned char lcd_backlight = RTUI_ON;

static unsigned char rtui_csram[8][8] = {
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x15, 0x00 },
  { 0x08, 0x19, 0x0A, 0x1E, 0x09, 0x12, 0x07, 0x00 },
  { 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00 },
  { 0x08, 0x10, 0x0E, 0x10, 0x0E, 0x01, 0x1E, 0x00 },
  { 0x00, 0x04, 0x0C, 0x1F, 0x0C, 0x04, 0x00, 0x00 },
  { 0x00, 0x04, 0x06, 0x1F, 0x06, 0x04, 0x00, 0x00 },
  { 0x00, 0x04, 0x0E, 0x1F, 0x04, 0x04, 0x00, 0x00 },
  { 0x00, 0x04, 0x04, 0x1F, 0x0E, 0x04, 0x00, 0x00 },
};

static char * rtui_hex[256] = {
  "00","01","02","03","04","05","06","07","08","09","0A","0B","0C","0D","0E","0F",
  "10","11","12","13","14","15","16","17","18","19","1A","1B","1C","1D","1E","1F",
  "20","21","22","23","24","25","26","27","28","29","2A","2B","2C","2D","2E","2F",
  "30","31","32","33","34","35","36","37","38","39","3A","3B","3C","3D","3E","3F",
  "40","41","42","43","44","45","46","47","48","49","4A","4B","4C","4D","4E","4F",
  "50","51","52","53","54","55","56","57","58","59","5A","5B","5C","5D","5E","5F",
  "60","61","62","63","64","65","66","67","68","69","6A","6B","6C","6D","6E","6F",
  "70","71","72","73","74","75","76","77","78","79","7A","7B","7C","7D","7E","7F",
  "80","81","82","83","84","85","86","87","88","89","8A","8B","8C","8D","8E","8F",
  "90","91","92","93","94","95","96","97","98","99","9A","9B","9C","9D","9E","9F",
  "A0","A1","A2","A3","A4","A5","A6","A7","A8","A9","AA","AB","AC","AD","AE","AF",
  "B0","B1","B2","B3","B4","B5","B6","B7","B8","B9","BA","BB","BC","BD","BE","BF",
  "C0","C1","C2","C3","C4","C5","C6","C7","C8","C9","CA","CB","CC","CD","CE","CF",
  "D0","D1","D2","D3","D4","D5","D6","D7","D8","D9","DA","DB","DC","DD","DE","DF",
  "E0","E1","E2","E3","E4","E5","E6","E7","E8","E9","EA","EB","EC","ED","EE","EF",
  "F0","F1","F2","F3","F4","F5","F6","F7","F8","F9","FA","FB","FC","FD","FE","FF",
};

static char * rtui_chr[256] = {
  ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".",
  ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".",
  " ", "!","\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/",
  "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ";", "<", "=", ">", "?",
  "@", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
  "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "[","\\", "]", "^", "_",
  "`", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o",
  "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "{", "|", "}", ".", ".",
  ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".",
  ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".",
  ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".",
  ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".",
  ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".",
  ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".",
  ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".",
  ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".",
};

static char * rtui_data_width_str[RTUI_DATA_WIDTHS] = {
  "  8     ",
  " 16 (LE)",
  " 16 (BE)",
};

static char * rtui_addr_width_str[RTUI_ADDR_WIDTHS] = {
  "  8 ", "  8\x01", "  9 ", "  9\x01", " 10 ", " 10\x01", " 11 ", " 11\x01",
  " 12 ", " 12\x01", " 13 ", " 13\x01", " 14 ", " 14\x01", " 15 ", " 15\x01",
  " 16 ", " 16\x01", " 17 ", " 17\x01", " 18 ", " 18\x01", " 19 ", " 19\x01",
  " 20 ", " 20\x01", " 21 ", " 21\x01", " 22 ", " 22\x01", " 23 ", " 23\x01",
  " 24 ", " 24\x01", " 25 ", " 25\x01", " 26 ", " 26\x01", " 27 ", " 27\x01",
  " 28 ", " 28\x01", " 29 ", " 29\x01", " 30 ", " 30\x01", " 31 ",
};

static char * rtui_addr_width_sstr[RTUI_ADDR_WIDTHS + 2] = {
  "  (256B)", "  (384B)", "  (512B)", "  (768B)", " (1024B)", " (1536B)", "    (2K)",
  "    (3K)", "    (4K)", "    (6K)", "    (8K)", "   (12K)", "   (16K)", "   (24K)",
  "   (32K)", "   (48K)", "   (64K)", "   (96K)", "  (128K)", "  (192K)", "  (256K)",
  "  (384K)", "  (512K)", "  (768K)", " (1024K)", " (1536K)", "    (2M)", "    (3M)",
  "    (4M)", "    (6M)", "    (8M)", "   (12M)", "   (16M)", "   (24M)", "   (32M)",
  "   (48M)", "   (64M)", "   (96M)", "  (128M)", "  (192M)", "  (256M)", "  (384M)",
  "  (512M)", "  (768M)", " (1024M)", " (1536M)", "    (2G)", "    (3G)", "    (4G)",
};

static unsigned long rtui_addr_width[RTUI_ADDR_WIDTHS] = {
  0x00000100, 0x00000180, 0x00000200, 0x00000300, 0x00000400, 0x00000600, 0x00000800, 0x00000C00,
  0x00001000, 0x00001800, 0x00002000, 0x00003000, 0x00004000, 0x00006000, 0x00008000, 0x0000C000,
  0x00010000, 0x00018000, 0x00020000, 0x00030000, 0x00040000, 0x00060000, 0x00080000, 0x000C0000,
  0x00100000, 0x00180000, 0x00200000, 0x00300000, 0x00400000, 0x00600000, 0x00800000, 0x00C00000,
  0x01000000, 0x01800000, 0x02000000, 0x03000000, 0x04000000, 0x06000000, 0x08000000, 0x0C000000,
  0x10000000, 0x18000000, 0x20000000, 0x30000000, 0x40000000, 0x60000000, 0x80000000
};

void rtui_init() {
  lcd.begin(RTUI_COLUMNS, RTUI_ROWS);
  lcd.setBacklight(lcd_backlight);
  for (int i = 0; i < 8; i++) {
    lcd.createChar(i, rtui_csram[i]);
  }
}

unsigned char rtui_get_backlight() {
  return lcd_backlight;
}

void rtui_set_backlight(unsigned char color) {
  lcd_backlight = color & 7;
  lcd.setBacklight(lcd_backlight);
}

void rtui_clear() {
  lcd.clear();
}

void rtui_set_cursor(unsigned char col, unsigned char row) {
  lcd.setCursor(col, row);
}

void rtui_show_cursor() {
  lcd.cursor();
}

void rtui_hide_cursor() {
  lcd.noCursor();
}

void rtui_print(const char * s) {
  lcd.print(s);
}

void rtui_print_addr(unsigned long a) {
  lcd.print(rtui_hex[(a >> 24) & 0xFF]);
  lcd.print(rtui_hex[(a >> 16) & 0xFF]);
  lcd.print(rtui_hex[(a >>  8) & 0xFF]);
  lcd.print(rtui_hex[a & 0xFF]);
}

void rtui_print_data_16(unsigned int d) {
  lcd.print(" ");
  lcd.print(rtui_hex[(d >> 8) & 0xFF]);
  lcd.print(rtui_hex[d & 0xFF]);
  lcd.print(" ");
  lcd.print(rtui_chr[(d >> 8) & 0xFF]);
  lcd.print(rtui_chr[d & 0xFF]);
}

void rtui_print_data_8(unsigned char d) {
  lcd.print("   ");
  lcd.print(rtui_hex[d]);
  lcd.print("  ");
  lcd.print(rtui_chr[d]);
}

void rtui_print_data_16x4(unsigned int * d) {
  lcd.setCursor(8, 0);
  lcd.print(rtui_chr[(d[0] >> 8) & 0xFF]);
  lcd.print(rtui_chr[d[0] & 0xFF]);
  lcd.print(rtui_chr[(d[1] >> 8) & 0xFF]);
  lcd.print(rtui_chr[d[1] & 0xFF]);
  lcd.print(rtui_chr[(d[2] >> 8) & 0xFF]);
  lcd.print(rtui_chr[d[2] & 0xFF]);
  lcd.print(rtui_chr[(d[3] >> 8) & 0xFF]);
  lcd.print(rtui_chr[d[3] & 0xFF]);
  lcd.setCursor(0, 1);
  lcd.print(rtui_hex[(d[0] >> 8) & 0xFF]);
  lcd.print(rtui_hex[d[0] & 0xFF]);
  lcd.print(rtui_hex[(d[1] >> 8) & 0xFF]);
  lcd.print(rtui_hex[d[1] & 0xFF]);
  lcd.print(rtui_hex[(d[2] >> 8) & 0xFF]);
  lcd.print(rtui_hex[d[2] & 0xFF]);
  lcd.print(rtui_hex[(d[3] >> 8) & 0xFF]);
  lcd.print(rtui_hex[d[3] & 0xFF]);
}

void rtui_print_data_8x8(unsigned char * d) {
  lcd.setCursor(8, 0);
  lcd.print(rtui_chr[d[0]]);
  lcd.print(rtui_chr[d[1]]);
  lcd.print(rtui_chr[d[2]]);
  lcd.print(rtui_chr[d[3]]);
  lcd.print(rtui_chr[d[4]]);
  lcd.print(rtui_chr[d[5]]);
  lcd.print(rtui_chr[d[6]]);
  lcd.print(rtui_chr[d[7]]);
  lcd.setCursor(0, 1);
  lcd.print(rtui_hex[d[0]]);
  lcd.print(rtui_hex[d[1]]);
  lcd.print(rtui_hex[d[2]]);
  lcd.print(rtui_hex[d[3]]);
  lcd.print(rtui_hex[d[4]]);
  lcd.print(rtui_hex[d[5]]);
  lcd.print(rtui_hex[d[6]]);
  lcd.print(rtui_hex[d[7]]);
}

void rtui_print_data_width(int dw) {
  lcd.print(rtui_data_width_str[dw]);
}

void rtui_print_addr_width(int aw, int dw) {
  lcd.print(rtui_addr_width_str[aw]);
  if (dw) lcd.print(rtui_addr_width_sstr[aw + 2]);
  else lcd.print(rtui_addr_width_sstr[aw]);
}

unsigned long rtui_get_addr_width(int aw) {
  return rtui_addr_width[aw];
}

unsigned char rtui_get_buttons() {
  return lcd.readButtons();
}

char * rtui_get_hex(unsigned char d) {
  return rtui_hex[d];
}

char * rtui_get_chr(unsigned char d) {
  return rtui_chr[d];
}
