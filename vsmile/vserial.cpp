#include <Arduino.h>
#include "vserial.h"

static unsigned char vs_buffer[256];
static unsigned char vs_buf_start = 0;
static unsigned char vs_buf_end = 0;

// controller pin 1 = RST - controller reset, active low output
// controller pin 2 = RTR - controller select, active high output
// controller pin 3 = RX  - system TX, controller RX, active low output
// controller pin 4 = GND - connect to Arduino GND
// controller pin 5 = TX  - controller TX, system RX, active low input
// controller pin 6 = RTS - external interrupt, active low input
void vserial_begin() {
  VS_RTR_DDR |=  VS_RTR_MASK; VS_RTR_PORT &=~ VS_RTR_MASK;
  VS_RTS_DDR &=~ VS_RTS_MASK; VS_RTS_PORT |=  VS_RTS_MASK;
  VS_RX_DDR  |=  VS_RX_MASK ; VS_RX_PORT  |=  VS_RX_MASK ;
  VS_TX_DDR  &=~ VS_TX_MASK ; VS_TX_PORT  |=  VS_TX_MASK ;
  VS_RST_DDR |=  VS_RST_MASK; VS_RST_PORT |=  VS_RST_MASK;
  VS_GND_DDR |=  VS_GND_MASK; VS_GND_PORT &=~ VS_GND_MASK;
  vs_buf_start = 0;
  vs_buf_end = 0;
}

// controller -> system:
//        ~10us ->||<-       ->|-|<- ~208us (4800bps)
//               ->|-----------|<- ~3.7ms
// 2 - RTR: _______|"""""""""""""""""""""""""""""""|______ csel, active high output
// 5 - TX : """""""""""""""""""|_|"|_|"|_|"|_|"|_|"""""""" controller TX, system RX
// 6 - RTS: """"""|____________|"""""""""""""""""""""""""" extint, active low input
//                              ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
//                          start 0 1 2 3 4 5 6 7 stop
static void vs_receive() {
  noInterrupts();
  while (!(VS_RTS_PIN & VS_RTS_MASK)) {
    int v = 0;
    VS_RTR_PORT |= VS_RTR_MASK;
    while (VS_TX_PIN & VS_TX_MASK);  // wait for start bit
    delayMicroseconds(312);
    if (VS_TX_PIN & VS_TX_MASK) v |= 0x01;
    delayMicroseconds(208);
    if (VS_TX_PIN & VS_TX_MASK) v |= 0x02;
    delayMicroseconds(208);
    if (VS_TX_PIN & VS_TX_MASK) v |= 0x04;
    delayMicroseconds(208);
    if (VS_TX_PIN & VS_TX_MASK) v |= 0x08;
    delayMicroseconds(208);
    if (VS_TX_PIN & VS_TX_MASK) v |= 0x10;
    delayMicroseconds(208);
    if (VS_TX_PIN & VS_TX_MASK) v |= 0x20;
    delayMicroseconds(208);
    if (VS_TX_PIN & VS_TX_MASK) v |= 0x40;
    delayMicroseconds(208);
    if (VS_TX_PIN & VS_TX_MASK) v |= 0x80;
    delayMicroseconds(208);
    vs_buffer[vs_buf_end++] = v;
  }
  VS_RTR_PORT &=~ VS_RTR_MASK;
  interrupts();
}

int vserial_available() {
  vs_receive();
  return (vs_buf_start != vs_buf_end);
}

int vserial_read() {
  vs_receive();
  if (vs_buf_start == vs_buf_end) return -1;
  else return vs_buffer[vs_buf_start++];
}

// system -> controller:
//              ~75us ->||<-   ->|-|<- ~208us (4800bps)
// 2 - RTR: ____________|"""""""""""""""""""|____________ csel, active high output
// 3 - RX : """""""""""""|_|"|_|"|_|"|_|"|_|""""""""""""" system TX, controller RX
// 6 - RTS: """"""""""""""""""""""""""""""""""""""""""""" extint, active low input
//                        ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
//                    start 0 1 2 3 4 5 6 7 stop
void vserial_write(int v) {
  noInterrupts();
  VS_RTR_PORT |= VS_RTR_MASK;
  delayMicroseconds(75);
  VS_RX_PORT &=~ VS_RX_MASK;  // start bit
  delayMicroseconds(208);
  if (v & 0x01) VS_RX_PORT |= VS_RX_MASK; else VS_RX_PORT &=~ VS_RX_MASK;
  delayMicroseconds(208);
  if (v & 0x02) VS_RX_PORT |= VS_RX_MASK; else VS_RX_PORT &=~ VS_RX_MASK;
  delayMicroseconds(208);
  if (v & 0x04) VS_RX_PORT |= VS_RX_MASK; else VS_RX_PORT &=~ VS_RX_MASK;
  delayMicroseconds(208);
  if (v & 0x08) VS_RX_PORT |= VS_RX_MASK; else VS_RX_PORT &=~ VS_RX_MASK;
  delayMicroseconds(208);
  if (v & 0x10) VS_RX_PORT |= VS_RX_MASK; else VS_RX_PORT &=~ VS_RX_MASK;
  delayMicroseconds(208);
  if (v & 0x20) VS_RX_PORT |= VS_RX_MASK; else VS_RX_PORT &=~ VS_RX_MASK;
  delayMicroseconds(208);
  if (v & 0x40) VS_RX_PORT |= VS_RX_MASK; else VS_RX_PORT &=~ VS_RX_MASK;
  delayMicroseconds(208);
  if (v & 0x80) VS_RX_PORT |= VS_RX_MASK; else VS_RX_PORT &=~ VS_RX_MASK;
  delayMicroseconds(208);
  VS_RX_PORT |= VS_RX_MASK;  // stop bit
  delayMicroseconds(133);
  VS_RTR_PORT &=~ VS_RTR_MASK;
  interrupts();
}

void vserial_reset() {
  VS_RTR_PORT &=~ VS_RTR_MASK;
  VS_RTS_PORT &=~ VS_RTS_MASK;
  VS_RX_PORT  &=~ VS_RX_MASK ;
  VS_TX_PORT  &=~ VS_TX_MASK ;
  VS_RST_PORT &=~ VS_RST_MASK;
  VS_GND_PORT &=~ VS_GND_MASK;
  delay(10);
  VS_RTR_PORT &=~ VS_RTR_MASK;
  VS_RTS_PORT |=  VS_RTS_MASK;
  VS_RX_PORT  |=  VS_RX_MASK ;
  VS_TX_PORT  |=  VS_TX_MASK ;
  VS_RST_PORT |=  VS_RST_MASK;
  VS_GND_PORT &=~ VS_GND_MASK;
  vs_buf_start = 0;
  vs_buf_end = 0;
}
