#ifndef RTUI_H
#define RTUI_H

#define RTUI_COLUMNS  16
#define RTUI_ROWS      2

#define RTUI_OFF     0
#define RTUI_BLACK   0
#define RTUI_RED     1
#define RTUI_GREEN   2
#define RTUI_YELLOW  3
#define RTUI_BLUE    4
#define RTUI_VIOLET  5
#define RTUI_TEAL    6
#define RTUI_WHITE   7
#define RTUI_ON      7
#define RTUI_COLORS  8

#define RTUI_DATA_WIDTH_8      0
#define RTUI_DATA_WIDTH_16_LE  1
#define RTUI_DATA_WIDTH_16_BE  2
#define RTUI_DATA_WIDTHS       3

#define RTUI_ADDR_WIDTH_8    0
#define RTUI_ADDR_WIDTH_9    2
#define RTUI_ADDR_WIDTH_10   4
#define RTUI_ADDR_WIDTH_11   6
#define RTUI_ADDR_WIDTH_12   8
#define RTUI_ADDR_WIDTH_13  10
#define RTUI_ADDR_WIDTH_14  12
#define RTUI_ADDR_WIDTH_15  14
#define RTUI_ADDR_WIDTH_16  16
#define RTUI_ADDR_WIDTH_17  18
#define RTUI_ADDR_WIDTH_18  20
#define RTUI_ADDR_WIDTH_19  22
#define RTUI_ADDR_WIDTH_20  24
#define RTUI_ADDR_WIDTH_21  26
#define RTUI_ADDR_WIDTH_22  28
#define RTUI_ADDR_WIDTH_23  30
#define RTUI_ADDR_WIDTH_24  32
#define RTUI_ADDR_WIDTH_25  34
#define RTUI_ADDR_WIDTH_26  36
#define RTUI_ADDR_WIDTH_27  38
#define RTUI_ADDR_WIDTH_28  40
#define RTUI_ADDR_WIDTH_29  42
#define RTUI_ADDR_WIDTH_30  44
#define RTUI_ADDR_WIDTH_31  46
#define RTUI_ADDR_WIDTHS    47

#define RTUI_UP      0x08
#define RTUI_DOWN    0x04
#define RTUI_LEFT    0x10
#define RTUI_RIGHT   0x02
#define RTUI_SELECT  0x01

void rtui_init();
unsigned char rtui_get_backlight();
void rtui_set_backlight(unsigned char color);
void rtui_clear();
void rtui_set_cursor(unsigned char col, unsigned char row);
void rtui_show_cursor();
void rtui_hide_cursor();
void rtui_print(const char * s);
void rtui_print_addr(unsigned long a);
void rtui_print_data_16(unsigned int d);
void rtui_print_data_8(unsigned char d);
void rtui_print_data_16x4(unsigned int * d);
void rtui_print_data_8x8(unsigned char * d);
void rtui_print_data_width(int dw);
void rtui_print_addr_width(int aw, int dw);
unsigned long rtui_get_addr_width(int aw);
unsigned char rtui_get_buttons();
char * rtui_get_hex(unsigned char d);

#endif
