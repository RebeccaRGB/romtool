#include <Arduino.h>
#include "rtio.h"

void rtio_init() {
  pinMode(RT_CE , OUTPUT); digitalWrite(RT_CE , HIGH);
  pinMode(RT_OE , OUTPUT); digitalWrite(RT_OE , HIGH);
  pinMode(RT_WE , OUTPUT); digitalWrite(RT_WE , HIGH);
  pinMode(RT_A0 , OUTPUT); digitalWrite(RT_A0 , LOW );
  pinMode(RT_A1 , OUTPUT); digitalWrite(RT_A1 , LOW );
  pinMode(RT_A2 , OUTPUT); digitalWrite(RT_A2 , LOW );
  pinMode(RT_A3 , OUTPUT); digitalWrite(RT_A3 , LOW );
  pinMode(RT_A4 , OUTPUT); digitalWrite(RT_A4 , LOW );
  pinMode(RT_A5 , OUTPUT); digitalWrite(RT_A5 , LOW );
  pinMode(RT_A6 , OUTPUT); digitalWrite(RT_A6 , LOW );
  pinMode(RT_A7 , OUTPUT); digitalWrite(RT_A7 , LOW );
  pinMode(RT_A8 , OUTPUT); digitalWrite(RT_A8 , LOW );
  pinMode(RT_A9 , OUTPUT); digitalWrite(RT_A9 , LOW );
  pinMode(RT_A10, OUTPUT); digitalWrite(RT_A10, LOW );
  pinMode(RT_A11, OUTPUT); digitalWrite(RT_A11, LOW );
  pinMode(RT_A12, OUTPUT); digitalWrite(RT_A12, LOW );
  pinMode(RT_A13, OUTPUT); digitalWrite(RT_A13, LOW );
  pinMode(RT_A14, OUTPUT); digitalWrite(RT_A14, LOW );
  pinMode(RT_A15, OUTPUT); digitalWrite(RT_A15, LOW );
  pinMode(RT_A16, OUTPUT); digitalWrite(RT_A16, LOW );
  pinMode(RT_A17, OUTPUT); digitalWrite(RT_A17, LOW );
  pinMode(RT_A18, OUTPUT); digitalWrite(RT_A18, LOW );
  pinMode(RT_A19, OUTPUT); digitalWrite(RT_A19, LOW );
  pinMode(RT_A20, OUTPUT); digitalWrite(RT_A20, LOW );
  pinMode(RT_A21, OUTPUT); digitalWrite(RT_A21, LOW );
  pinMode(RT_A22, OUTPUT); digitalWrite(RT_A22, LOW );
  pinMode(RT_A23, OUTPUT); digitalWrite(RT_A23, LOW );
  pinMode(RT_A24, OUTPUT); digitalWrite(RT_A24, LOW );
  pinMode(RT_A25, OUTPUT); digitalWrite(RT_A25, LOW );
  pinMode(RT_A26, OUTPUT); digitalWrite(RT_A26, LOW );
  pinMode(RT_A27, OUTPUT); digitalWrite(RT_A27, LOW );
  pinMode(RT_A28, OUTPUT); digitalWrite(RT_A28, LOW );
  pinMode(RT_A29, OUTPUT); digitalWrite(RT_A29, LOW );
  pinMode(RT_A30, OUTPUT); digitalWrite(RT_A30, LOW );
  pinMode(RT_Q0 , INPUT );
  pinMode(RT_Q1 , INPUT );
  pinMode(RT_Q2 , INPUT );
  pinMode(RT_Q3 , INPUT );
  pinMode(RT_Q4 , INPUT );
  pinMode(RT_Q5 , INPUT );
  pinMode(RT_Q6 , INPUT );
  pinMode(RT_Q7 , INPUT );
  pinMode(RT_Q8 , INPUT );
  pinMode(RT_Q9 , INPUT );
  pinMode(RT_Q10, INPUT );
  pinMode(RT_Q11, INPUT );
  pinMode(RT_Q12, INPUT );
  pinMode(RT_Q13, INPUT );
  pinMode(RT_Q14, INPUT );
  pinMode(RT_Q15, INPUT );
}

void rtio_deactivate() {
  digitalWrite(RT_CE, HIGH);
  digitalWrite(RT_OE, HIGH);
  digitalWrite(RT_WE, HIGH);
  pinMode(RT_Q0 , INPUT);
  pinMode(RT_Q1 , INPUT);
  pinMode(RT_Q2 , INPUT);
  pinMode(RT_Q3 , INPUT);
  pinMode(RT_Q4 , INPUT);
  pinMode(RT_Q5 , INPUT);
  pinMode(RT_Q6 , INPUT);
  pinMode(RT_Q7 , INPUT);
  pinMode(RT_Q8 , INPUT);
  pinMode(RT_Q9 , INPUT);
  pinMode(RT_Q10, INPUT);
  pinMode(RT_Q11, INPUT);
  pinMode(RT_Q12, INPUT);
  pinMode(RT_Q13, INPUT);
  pinMode(RT_Q14, INPUT);
  pinMode(RT_Q15, INPUT);
}

void rtio_read_mode() {
  digitalWrite(RT_CE, HIGH);
  digitalWrite(RT_OE, LOW );
  digitalWrite(RT_WE, HIGH);
  pinMode(RT_Q0 , INPUT);
  pinMode(RT_Q1 , INPUT);
  pinMode(RT_Q2 , INPUT);
  pinMode(RT_Q3 , INPUT);
  pinMode(RT_Q4 , INPUT);
  pinMode(RT_Q5 , INPUT);
  pinMode(RT_Q6 , INPUT);
  pinMode(RT_Q7 , INPUT);
  pinMode(RT_Q8 , INPUT);
  pinMode(RT_Q9 , INPUT);
  pinMode(RT_Q10, INPUT);
  pinMode(RT_Q11, INPUT);
  pinMode(RT_Q12, INPUT);
  pinMode(RT_Q13, INPUT);
  pinMode(RT_Q14, INPUT);
  pinMode(RT_Q15, INPUT);
}

void rtio_write_mode() {
  digitalWrite(RT_CE, HIGH);
  digitalWrite(RT_OE, HIGH);
  digitalWrite(RT_WE, LOW );
  pinMode(RT_Q0 , OUTPUT); digitalWrite(RT_Q0 , LOW);
  pinMode(RT_Q1 , OUTPUT); digitalWrite(RT_Q1 , LOW);
  pinMode(RT_Q2 , OUTPUT); digitalWrite(RT_Q2 , LOW);
  pinMode(RT_Q3 , OUTPUT); digitalWrite(RT_Q3 , LOW);
  pinMode(RT_Q4 , OUTPUT); digitalWrite(RT_Q4 , LOW);
  pinMode(RT_Q5 , OUTPUT); digitalWrite(RT_Q5 , LOW);
  pinMode(RT_Q6 , OUTPUT); digitalWrite(RT_Q6 , LOW);
  pinMode(RT_Q7 , OUTPUT); digitalWrite(RT_Q7 , LOW);
  pinMode(RT_Q8 , OUTPUT); digitalWrite(RT_Q8 , LOW);
  pinMode(RT_Q9 , OUTPUT); digitalWrite(RT_Q9 , LOW);
  pinMode(RT_Q10, OUTPUT); digitalWrite(RT_Q10, LOW);
  pinMode(RT_Q11, OUTPUT); digitalWrite(RT_Q11, LOW);
  pinMode(RT_Q12, OUTPUT); digitalWrite(RT_Q12, LOW);
  pinMode(RT_Q13, OUTPUT); digitalWrite(RT_Q13, LOW);
  pinMode(RT_Q14, OUTPUT); digitalWrite(RT_Q14, LOW);
  pinMode(RT_Q15, OUTPUT); digitalWrite(RT_Q15, LOW);
}

void rtio_set_addr(unsigned long addr) {
  digitalWrite(RT_A0 , (addr & 0x00000001ul) ? HIGH : LOW);
  digitalWrite(RT_A1 , (addr & 0x00000002ul) ? HIGH : LOW);
  digitalWrite(RT_A2 , (addr & 0x00000004ul) ? HIGH : LOW);
  digitalWrite(RT_A3 , (addr & 0x00000008ul) ? HIGH : LOW);
  digitalWrite(RT_A4 , (addr & 0x00000010ul) ? HIGH : LOW);
  digitalWrite(RT_A5 , (addr & 0x00000020ul) ? HIGH : LOW);
  digitalWrite(RT_A6 , (addr & 0x00000040ul) ? HIGH : LOW);
  digitalWrite(RT_A7 , (addr & 0x00000080ul) ? HIGH : LOW);
  digitalWrite(RT_A8 , (addr & 0x00000100ul) ? HIGH : LOW);
  digitalWrite(RT_A9 , (addr & 0x00000200ul) ? HIGH : LOW);
  digitalWrite(RT_A10, (addr & 0x00000400ul) ? HIGH : LOW);
  digitalWrite(RT_A11, (addr & 0x00000800ul) ? HIGH : LOW);
  digitalWrite(RT_A12, (addr & 0x00001000ul) ? HIGH : LOW);
  digitalWrite(RT_A13, (addr & 0x00002000ul) ? HIGH : LOW);
  digitalWrite(RT_A14, (addr & 0x00004000ul) ? HIGH : LOW);
  digitalWrite(RT_A15, (addr & 0x00008000ul) ? HIGH : LOW);
  digitalWrite(RT_A16, (addr & 0x00010000ul) ? HIGH : LOW);
  digitalWrite(RT_A17, (addr & 0x00020000ul) ? HIGH : LOW);
  digitalWrite(RT_A18, (addr & 0x00040000ul) ? HIGH : LOW);
  digitalWrite(RT_A19, (addr & 0x00080000ul) ? HIGH : LOW);
  digitalWrite(RT_A20, (addr & 0x00100000ul) ? HIGH : LOW);
  digitalWrite(RT_A21, (addr & 0x00200000ul) ? HIGH : LOW);
  digitalWrite(RT_A22, (addr & 0x00400000ul) ? HIGH : LOW);
  digitalWrite(RT_A23, (addr & 0x00800000ul) ? HIGH : LOW);
  digitalWrite(RT_A24, (addr & 0x01000000ul) ? HIGH : LOW);
  digitalWrite(RT_A25, (addr & 0x02000000ul) ? HIGH : LOW);
  digitalWrite(RT_A26, (addr & 0x04000000ul) ? HIGH : LOW);
  digitalWrite(RT_A27, (addr & 0x08000000ul) ? HIGH : LOW);
  digitalWrite(RT_A28, (addr & 0x10000000ul) ? HIGH : LOW);
  digitalWrite(RT_A29, (addr & 0x20000000ul) ? HIGH : LOW);
  digitalWrite(RT_A30, (addr & 0x40000000ul) ? HIGH : LOW); 
}

void rtio_set_data(unsigned int data) {
  digitalWrite(RT_Q0 , (data & 0x0001) ? HIGH : LOW);
  digitalWrite(RT_Q1 , (data & 0x0002) ? HIGH : LOW);
  digitalWrite(RT_Q2 , (data & 0x0004) ? HIGH : LOW);
  digitalWrite(RT_Q3 , (data & 0x0008) ? HIGH : LOW);
  digitalWrite(RT_Q4 , (data & 0x0010) ? HIGH : LOW);
  digitalWrite(RT_Q5 , (data & 0x0020) ? HIGH : LOW);
  digitalWrite(RT_Q6 , (data & 0x0040) ? HIGH : LOW);
  digitalWrite(RT_Q7 , (data & 0x0080) ? HIGH : LOW);
  digitalWrite(RT_Q8 , (data & 0x0100) ? HIGH : LOW);
  digitalWrite(RT_Q9 , (data & 0x0200) ? HIGH : LOW);
  digitalWrite(RT_Q10, (data & 0x0400) ? HIGH : LOW);
  digitalWrite(RT_Q11, (data & 0x0800) ? HIGH : LOW);
  digitalWrite(RT_Q12, (data & 0x1000) ? HIGH : LOW);
  digitalWrite(RT_Q13, (data & 0x2000) ? HIGH : LOW);
  digitalWrite(RT_Q14, (data & 0x4000) ? HIGH : LOW);
  digitalWrite(RT_Q15, (data & 0x8000) ? HIGH : LOW);
}

unsigned int rtio_read_data() {
  unsigned int data = 0;
  if (digitalRead(RT_Q0 )) data |= 0x0001;
  if (digitalRead(RT_Q1 )) data |= 0x0002;
  if (digitalRead(RT_Q2 )) data |= 0x0004;
  if (digitalRead(RT_Q3 )) data |= 0x0008;
  if (digitalRead(RT_Q4 )) data |= 0x0010;
  if (digitalRead(RT_Q5 )) data |= 0x0020;
  if (digitalRead(RT_Q6 )) data |= 0x0040;
  if (digitalRead(RT_Q7 )) data |= 0x0080;
  if (digitalRead(RT_Q8 )) data |= 0x0100;
  if (digitalRead(RT_Q9 )) data |= 0x0200;
  if (digitalRead(RT_Q10)) data |= 0x0400;
  if (digitalRead(RT_Q11)) data |= 0x0800;
  if (digitalRead(RT_Q12)) data |= 0x1000;
  if (digitalRead(RT_Q13)) data |= 0x2000;
  if (digitalRead(RT_Q14)) data |= 0x4000;
  if (digitalRead(RT_Q15)) data |= 0x8000;
  return data;
}

void rtio_enable() {
  digitalWrite(RT_CE, LOW);
}

void rtio_disable() {
  digitalWrite(RT_CE, HIGH);
}
