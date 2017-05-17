#ifndef VSERIAL_H
#define VSERIAL_H

// controller pin 1 = RESET
// controller reset, active low output
#define VS_RST       18
#define VS_RST_DDR   DDRD
#define VS_RST_PORT  PORTD
#define VS_RST_PIN   PIND
#define VS_RST_MASK  0x08

// controller pin 2 = RTR
// controller select, active high output
#define VS_RTR       15
#define VS_RTR_DDR   DDRJ
#define VS_RTR_PORT  PORTJ
#define VS_RTR_PIN   PINJ
#define VS_RTR_MASK  0x01

// controller pin 3 = RX
// system TX, controller RX, active low output
#define VS_RX        16
#define VS_RX_DDR    DDRH
#define VS_RX_PORT   PORTH
#define VS_RX_PIN    PINH
#define VS_RX_MASK   0x02

// controller pin 4 = GND
// connect to Arduino GND
#define VS_GND       19
#define VS_GND_DDR   DDRD
#define VS_GND_PORT  PORTD
#define VS_GND_PIN   PIND
#define VS_GND_MASK  0x04

// controller pin 5 = TX
// controller TX, system RX, active low input
#define VS_TX        17
#define VS_TX_DDR    DDRH
#define VS_TX_PORT   PORTH
#define VS_TX_PIN    PINH
#define VS_TX_MASK   0x01

// controller pin 6 = RTS
// external interrupt, active low input
#define VS_RTS       14
#define VS_RTS_DDR   DDRJ
#define VS_RTS_PORT  PORTJ
#define VS_RTS_PIN   PINJ
#define VS_RTS_MASK  0x02

void vserial_begin();
int vserial_available();
int vserial_read();
void vserial_write(int v);
void vserial_reset();

#endif
