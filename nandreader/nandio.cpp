#include <Arduino.h>
#include "nandio.h"

void initChip() {
  IO_DIR_PORT |=  IO_DIR_MASK; IO_DIR_DDR |= IO_DIR_MASK;  /* pinMode(IO_DIR, OUTPUT); digitalWrite(IO_DIR, HIGH); */
  CE_PORT     |=  CE_MASK    ; CE_DDR     |= CE_MASK    ;  /* pinMode(CE,     OUTPUT); digitalWrite(CE,     HIGH); */
  RE_PORT     |=  RE_MASK    ; RE_DDR     |= RE_MASK    ;  /* pinMode(RE,     OUTPUT); digitalWrite(RE,     HIGH); */
  WE_PORT     |=  WE_MASK    ; WE_DDR     |= WE_MASK    ;  /* pinMode(WE,     OUTPUT); digitalWrite(WE,     HIGH); */
  CLE_PORT    &=~ CLE_MASK   ; CLE_DDR    |= CLE_MASK   ;  /* pinMode(CLE,    OUTPUT); digitalWrite(CLE,    LOW ); */
  ALE_PORT    &=~ ALE_MASK   ; ALE_DDR    |= ALE_MASK   ;  /* pinMode(ALE,    OUTPUT); digitalWrite(ALE,    LOW ); */
  reset();
}

void reset() {
  setDataBusOut();
  CLE_PORT |=  CLE_MASK;  /* digitalWrite(CLE, HIGH); */
  CE_PORT  &=~ CE_MASK ;  /* digitalWrite(CE,  LOW ); */
  putDataBus(0xFF);
  CE_PORT  |=  CE_MASK ;  /* digitalWrite(CE,  HIGH); */
  CLE_PORT &=~ CLE_MASK;  /* digitalWrite(CLE, LOW ); */
  setDataBusIn();
  delayMicroseconds(500);
}

void setDataBusIn() {
  IO_DIR_PORT |= IO_DIR_MASK;  /* digitalWrite(IO_DIR, HIGH); */
  IO_0_PORT &=~ IO_0_MASK; IO_0_DDR &=~ IO_0_MASK;  /* pinMode(IO_0, INPUT); */
  IO_1_PORT &=~ IO_1_MASK; IO_1_DDR &=~ IO_1_MASK;  /* pinMode(IO_1, INPUT); */
  IO_2_PORT &=~ IO_2_MASK; IO_2_DDR &=~ IO_2_MASK;  /* pinMode(IO_2, INPUT); */
  IO_3_PORT &=~ IO_3_MASK; IO_3_DDR &=~ IO_3_MASK;  /* pinMode(IO_3, INPUT); */
  IO_4_PORT &=~ IO_4_MASK; IO_4_DDR &=~ IO_4_MASK;  /* pinMode(IO_4, INPUT); */
  IO_5_PORT &=~ IO_5_MASK; IO_5_DDR &=~ IO_5_MASK;  /* pinMode(IO_5, INPUT); */
  IO_6_PORT &=~ IO_6_MASK; IO_6_DDR &=~ IO_6_MASK;  /* pinMode(IO_6, INPUT); */
  IO_7_PORT &=~ IO_7_MASK; IO_7_DDR &=~ IO_7_MASK;  /* pinMode(IO_7, INPUT); */
}

void setDataBusOut() {
  IO_DIR_PORT &=~ IO_DIR_MASK;  /* digitalWrite(IO_DIR, LOW); */
  IO_0_PORT &=~ IO_0_MASK; IO_0_DDR |= IO_0_MASK;  /* pinMode(IO_0, OUTPUT); digitalWrite(IO_0, LOW); */
  IO_1_PORT &=~ IO_1_MASK; IO_1_DDR |= IO_1_MASK;  /* pinMode(IO_1, OUTPUT); digitalWrite(IO_1, LOW); */
  IO_2_PORT &=~ IO_2_MASK; IO_2_DDR |= IO_2_MASK;  /* pinMode(IO_2, OUTPUT); digitalWrite(IO_2, LOW); */
  IO_3_PORT &=~ IO_3_MASK; IO_3_DDR |= IO_3_MASK;  /* pinMode(IO_3, OUTPUT); digitalWrite(IO_3, LOW); */
  IO_4_PORT &=~ IO_4_MASK; IO_4_DDR |= IO_4_MASK;  /* pinMode(IO_4, OUTPUT); digitalWrite(IO_4, LOW); */
  IO_5_PORT &=~ IO_5_MASK; IO_5_DDR |= IO_5_MASK;  /* pinMode(IO_5, OUTPUT); digitalWrite(IO_5, LOW); */
  IO_6_PORT &=~ IO_6_MASK; IO_6_DDR |= IO_6_MASK;  /* pinMode(IO_6, OUTPUT); digitalWrite(IO_6, LOW); */
  IO_7_PORT &=~ IO_7_MASK; IO_7_DDR |= IO_7_MASK;  /* pinMode(IO_7, OUTPUT); digitalWrite(IO_7, LOW); */
}

void prepChip() {
  ALE_PORT &=~ ALE_MASK;  /* digitalWrite(ALE, LOW ); */
  CLE_PORT |=  CLE_MASK;  /* digitalWrite(CLE, HIGH); */
  WE_PORT  &=~ WE_MASK ;  /* digitalWrite(WE,  LOW ); */
  RE_PORT  |=  RE_MASK ;  /* digitalWrite(RE,  HIGH); */
  CE_PORT  &=~ CE_MASK ;  /* digitalWrite(CE,  LOW ); */
}

void setCommand() {
  CLE_PORT |= CLE_MASK;  /* digitalWrite(CLE, HIGH); */
}

void latchCommand() {
  CLE_PORT &=~ CLE_MASK;  /* digitalWrite(CLE, LOW); */
}

void setAddress() {
  ALE_PORT |= ALE_MASK;  /* digitalWrite(ALE, HIGH); */
}

void latchAddress() {
  ALE_PORT &=~ ALE_MASK;  /* digitalWrite(ALE, LOW); */
}

int readDataBus() {
  int value = 0;
  RE_PORT &=~ RE_MASK;  /* digitalWrite(RE, LOW); */
  if (IO_0_PIN & IO_0_MASK) value |= 0x01;  /* if (digitalRead(IO_0)) value |= 0x01; */
  if (IO_1_PIN & IO_1_MASK) value |= 0x02;  /* if (digitalRead(IO_1)) value |= 0x02; */
  if (IO_2_PIN & IO_2_MASK) value |= 0x04;  /* if (digitalRead(IO_2)) value |= 0x04; */
  if (IO_3_PIN & IO_3_MASK) value |= 0x08;  /* if (digitalRead(IO_3)) value |= 0x08; */
  if (IO_4_PIN & IO_4_MASK) value |= 0x10;  /* if (digitalRead(IO_4)) value |= 0x10; */
  if (IO_5_PIN & IO_5_MASK) value |= 0x20;  /* if (digitalRead(IO_5)) value |= 0x20; */
  if (IO_6_PIN & IO_6_MASK) value |= 0x40;  /* if (digitalRead(IO_6)) value |= 0x40; */
  if (IO_7_PIN & IO_7_MASK) value |= 0x80;  /* if (digitalRead(IO_7)) value |= 0x80; */
  RE_PORT |= RE_MASK;  /* digitalWrite(RE, HIGH); */
  return value;
}

void putDataBus(int i) {
  WE_PORT &=~ WE_MASK;  /* digitalWrite(WE, LOW); */
  if (i & 0x01) IO_0_PORT |= IO_0_MASK; else IO_0_PORT &=~ IO_0_MASK;  /* digitalWrite(IO_0, (i & 0x01) ? HIGH : LOW); */
  if (i & 0x02) IO_1_PORT |= IO_1_MASK; else IO_1_PORT &=~ IO_1_MASK;  /* digitalWrite(IO_1, (i & 0x02) ? HIGH : LOW); */
  if (i & 0x04) IO_2_PORT |= IO_2_MASK; else IO_2_PORT &=~ IO_2_MASK;  /* digitalWrite(IO_2, (i & 0x04) ? HIGH : LOW); */
  if (i & 0x08) IO_3_PORT |= IO_3_MASK; else IO_3_PORT &=~ IO_3_MASK;  /* digitalWrite(IO_3, (i & 0x08) ? HIGH : LOW); */
  if (i & 0x10) IO_4_PORT |= IO_4_MASK; else IO_4_PORT &=~ IO_4_MASK;  /* digitalWrite(IO_4, (i & 0x10) ? HIGH : LOW); */
  if (i & 0x20) IO_5_PORT |= IO_5_MASK; else IO_5_PORT &=~ IO_5_MASK;  /* digitalWrite(IO_5, (i & 0x20) ? HIGH : LOW); */
  if (i & 0x40) IO_6_PORT |= IO_6_MASK; else IO_6_PORT &=~ IO_6_MASK;  /* digitalWrite(IO_6, (i & 0x40) ? HIGH : LOW); */
  if (i & 0x80) IO_7_PORT |= IO_7_MASK; else IO_7_PORT &=~ IO_7_MASK;  /* digitalWrite(IO_7, (i & 0x80) ? HIGH : LOW); */
  WE_PORT |= WE_MASK;  /* digitalWrite(WE, HIGH); */
}

void closeChip() {
  CE_PORT  |=  CE_MASK ;  /* digitalWrite(CE,  HIGH); */
  RE_PORT  |=  RE_MASK ;  /* digitalWrite(RE,  HIGH); */
  WE_PORT  |=  WE_MASK ;  /* digitalWrite(WE,  HIGH); */
  CLE_PORT &=~ CLE_MASK;  /* digitalWrite(CLE, LOW ); */
  ALE_PORT &=~ ALE_MASK;  /* digitalWrite(ALE, LOW ); */
}
