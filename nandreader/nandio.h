#ifndef NANDIO_H
#define NANDIO_H

#define IO_DIR   11
#define CE       22
#define RE       24
#define WE       26
#define CLE      28
#define ALE      30
#define IO_0     23
#define IO_1     25
#define IO_2     27
#define IO_3     29
#define IO_4     31
#define IO_5     33
#define IO_6     35
#define IO_7     37

#define IO_DIR_DDR    DDRB
#define IO_DIR_PORT   PORTB
#define IO_DIR_MASK   0x20

#define CE_DDR    DDRA
#define CE_PORT   PORTA
#define CE_MASK   0x01

#define RE_DDR    DDRA
#define RE_PORT   PORTA
#define RE_MASK   0x04

#define WE_DDR    DDRA
#define WE_PORT   PORTA
#define WE_MASK   0x10

#define CLE_DDR    DDRA
#define CLE_PORT   PORTA
#define CLE_MASK   0x40

#define ALE_DDR    DDRC
#define ALE_PORT   PORTC
#define ALE_MASK   0x80

#define IO_0_DDR    DDRA
#define IO_0_PORT   PORTA
#define IO_0_PIN    PINA
#define IO_0_MASK   0x02

#define IO_1_DDR    DDRA
#define IO_1_PORT   PORTA
#define IO_1_PIN    PINA
#define IO_1_MASK   0x08

#define IO_2_DDR    DDRA
#define IO_2_PORT   PORTA
#define IO_2_PIN    PINA
#define IO_2_MASK   0x20

#define IO_3_DDR    DDRA
#define IO_3_PORT   PORTA
#define IO_3_PIN    PINA
#define IO_3_MASK   0x80

#define IO_4_DDR    DDRC
#define IO_4_PORT   PORTC
#define IO_4_PIN    PINC
#define IO_4_MASK   0x40

#define IO_5_DDR    DDRC
#define IO_5_PORT   PORTC
#define IO_5_PIN    PINC
#define IO_5_MASK   0x10

#define IO_6_DDR    DDRC
#define IO_6_PORT   PORTC
#define IO_6_PIN    PINC
#define IO_6_MASK   0x04

#define IO_7_DDR    DDRC
#define IO_7_PORT   PORTC
#define IO_7_PIN    PINC
#define IO_7_MASK   0x01

void initChip();
void reset();
void setDataBusIn();
void setDataBusOut();
void prepChip();
void setCommand();
void latchCommand();
void setAddress();
void latchAddress();
int readDataBus();
void putDataBus(int i);
void closeChip();

#endif
