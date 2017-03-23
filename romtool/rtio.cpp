#include <Arduino.h>
#include "rtio.h"

void rtio_init() {
  RT_CE_PORT  |=  RT_CE_MASK ; RT_CE_DDR  |=  RT_CE_MASK ;  /* pinMode(RT_CE , OUTPUT); digitalWrite(RT_CE , HIGH); */
  RT_OE_PORT  |=  RT_OE_MASK ; RT_OE_DDR  |=  RT_OE_MASK ;  /* pinMode(RT_OE , OUTPUT); digitalWrite(RT_OE , HIGH); */
  RT_WE_PORT  |=  RT_WE_MASK ; RT_WE_DDR  |=  RT_WE_MASK ;  /* pinMode(RT_WE , OUTPUT); digitalWrite(RT_WE , HIGH); */
  RT_A0_PORT  &=~ RT_A0_MASK ; RT_A0_DDR  |=  RT_A0_MASK ;  /* pinMode(RT_A0 , OUTPUT); digitalWrite(RT_A0 , LOW ); */
  RT_A1_PORT  &=~ RT_A1_MASK ; RT_A1_DDR  |=  RT_A1_MASK ;  /* pinMode(RT_A1 , OUTPUT); digitalWrite(RT_A1 , LOW ); */
  RT_A2_PORT  &=~ RT_A2_MASK ; RT_A2_DDR  |=  RT_A2_MASK ;  /* pinMode(RT_A2 , OUTPUT); digitalWrite(RT_A2 , LOW ); */
  RT_A3_PORT  &=~ RT_A3_MASK ; RT_A3_DDR  |=  RT_A3_MASK ;  /* pinMode(RT_A3 , OUTPUT); digitalWrite(RT_A3 , LOW ); */
  RT_A4_PORT  &=~ RT_A4_MASK ; RT_A4_DDR  |=  RT_A4_MASK ;  /* pinMode(RT_A4 , OUTPUT); digitalWrite(RT_A4 , LOW ); */
  RT_A5_PORT  &=~ RT_A5_MASK ; RT_A5_DDR  |=  RT_A5_MASK ;  /* pinMode(RT_A5 , OUTPUT); digitalWrite(RT_A5 , LOW ); */
  RT_A6_PORT  &=~ RT_A6_MASK ; RT_A6_DDR  |=  RT_A6_MASK ;  /* pinMode(RT_A6 , OUTPUT); digitalWrite(RT_A6 , LOW ); */
  RT_A7_PORT  &=~ RT_A7_MASK ; RT_A7_DDR  |=  RT_A7_MASK ;  /* pinMode(RT_A7 , OUTPUT); digitalWrite(RT_A7 , LOW ); */
  RT_A8_PORT  &=~ RT_A8_MASK ; RT_A8_DDR  |=  RT_A8_MASK ;  /* pinMode(RT_A8 , OUTPUT); digitalWrite(RT_A8 , LOW ); */
  RT_A9_PORT  &=~ RT_A9_MASK ; RT_A9_DDR  |=  RT_A9_MASK ;  /* pinMode(RT_A9 , OUTPUT); digitalWrite(RT_A9 , LOW ); */
  RT_A10_PORT &=~ RT_A10_MASK; RT_A10_DDR |=  RT_A10_MASK;  /* pinMode(RT_A10, OUTPUT); digitalWrite(RT_A10, LOW ); */
  RT_A11_PORT &=~ RT_A11_MASK; RT_A11_DDR |=  RT_A11_MASK;  /* pinMode(RT_A11, OUTPUT); digitalWrite(RT_A11, LOW ); */
  RT_A12_PORT &=~ RT_A12_MASK; RT_A12_DDR |=  RT_A12_MASK;  /* pinMode(RT_A12, OUTPUT); digitalWrite(RT_A12, LOW ); */
  RT_A13_PORT &=~ RT_A13_MASK; RT_A13_DDR |=  RT_A13_MASK;  /* pinMode(RT_A13, OUTPUT); digitalWrite(RT_A13, LOW ); */
  RT_A14_PORT &=~ RT_A14_MASK; RT_A14_DDR |=  RT_A14_MASK;  /* pinMode(RT_A14, OUTPUT); digitalWrite(RT_A14, LOW ); */
  RT_A15_PORT &=~ RT_A15_MASK; RT_A15_DDR |=  RT_A15_MASK;  /* pinMode(RT_A15, OUTPUT); digitalWrite(RT_A15, LOW ); */
  RT_A16_PORT &=~ RT_A16_MASK; RT_A16_DDR |=  RT_A16_MASK;  /* pinMode(RT_A16, OUTPUT); digitalWrite(RT_A16, LOW ); */
  RT_A17_PORT &=~ RT_A17_MASK; RT_A17_DDR |=  RT_A17_MASK;  /* pinMode(RT_A17, OUTPUT); digitalWrite(RT_A17, LOW ); */
  RT_A18_PORT &=~ RT_A18_MASK; RT_A18_DDR |=  RT_A18_MASK;  /* pinMode(RT_A18, OUTPUT); digitalWrite(RT_A18, LOW ); */
  RT_A19_PORT &=~ RT_A19_MASK; RT_A19_DDR |=  RT_A19_MASK;  /* pinMode(RT_A19, OUTPUT); digitalWrite(RT_A19, LOW ); */
  RT_A20_PORT &=~ RT_A20_MASK; RT_A20_DDR |=  RT_A20_MASK;  /* pinMode(RT_A20, OUTPUT); digitalWrite(RT_A20, LOW ); */
  RT_A21_PORT &=~ RT_A21_MASK; RT_A21_DDR |=  RT_A21_MASK;  /* pinMode(RT_A21, OUTPUT); digitalWrite(RT_A21, LOW ); */
  RT_A22_PORT &=~ RT_A22_MASK; RT_A22_DDR |=  RT_A22_MASK;  /* pinMode(RT_A22, OUTPUT); digitalWrite(RT_A22, LOW ); */
  RT_A23_PORT &=~ RT_A23_MASK; RT_A23_DDR |=  RT_A23_MASK;  /* pinMode(RT_A23, OUTPUT); digitalWrite(RT_A23, LOW ); */
  RT_A24_PORT &=~ RT_A24_MASK; RT_A24_DDR |=  RT_A24_MASK;  /* pinMode(RT_A24, OUTPUT); digitalWrite(RT_A24, LOW ); */
  RT_A25_PORT &=~ RT_A25_MASK; RT_A25_DDR |=  RT_A25_MASK;  /* pinMode(RT_A25, OUTPUT); digitalWrite(RT_A25, LOW ); */
  RT_A26_PORT &=~ RT_A26_MASK; RT_A26_DDR |=  RT_A26_MASK;  /* pinMode(RT_A26, OUTPUT); digitalWrite(RT_A26, LOW ); */
  RT_A27_PORT &=~ RT_A27_MASK; RT_A27_DDR |=  RT_A27_MASK;  /* pinMode(RT_A27, OUTPUT); digitalWrite(RT_A27, LOW ); */
  RT_A28_PORT &=~ RT_A28_MASK; RT_A28_DDR |=  RT_A28_MASK;  /* pinMode(RT_A28, OUTPUT); digitalWrite(RT_A28, LOW ); */
  RT_A29_PORT &=~ RT_A29_MASK; RT_A29_DDR |=  RT_A29_MASK;  /* pinMode(RT_A29, OUTPUT); digitalWrite(RT_A29, LOW ); */
  RT_A30_PORT &=~ RT_A30_MASK; RT_A30_DDR |=  RT_A30_MASK;  /* pinMode(RT_A30, OUTPUT); digitalWrite(RT_A30, LOW ); */
  RT_Q0_PORT  &=~ RT_Q0_MASK ; RT_Q0_DDR  &=~ RT_Q0_MASK ;  /* pinMode(RT_Q0 , INPUT ); */
  RT_Q1_PORT  &=~ RT_Q1_MASK ; RT_Q1_DDR  &=~ RT_Q1_MASK ;  /* pinMode(RT_Q1 , INPUT ); */
  RT_Q2_PORT  &=~ RT_Q2_MASK ; RT_Q2_DDR  &=~ RT_Q2_MASK ;  /* pinMode(RT_Q2 , INPUT ); */
  RT_Q3_PORT  &=~ RT_Q3_MASK ; RT_Q3_DDR  &=~ RT_Q3_MASK ;  /* pinMode(RT_Q3 , INPUT ); */
  RT_Q4_PORT  &=~ RT_Q4_MASK ; RT_Q4_DDR  &=~ RT_Q4_MASK ;  /* pinMode(RT_Q4 , INPUT ); */
  RT_Q5_PORT  &=~ RT_Q5_MASK ; RT_Q5_DDR  &=~ RT_Q5_MASK ;  /* pinMode(RT_Q5 , INPUT ); */
  RT_Q6_PORT  &=~ RT_Q6_MASK ; RT_Q6_DDR  &=~ RT_Q6_MASK ;  /* pinMode(RT_Q6 , INPUT ); */
  RT_Q7_PORT  &=~ RT_Q7_MASK ; RT_Q7_DDR  &=~ RT_Q7_MASK ;  /* pinMode(RT_Q7 , INPUT ); */
  RT_Q8_PORT  &=~ RT_Q8_MASK ; RT_Q8_DDR  &=~ RT_Q8_MASK ;  /* pinMode(RT_Q8 , INPUT ); */
  RT_Q9_PORT  &=~ RT_Q9_MASK ; RT_Q9_DDR  &=~ RT_Q9_MASK ;  /* pinMode(RT_Q9 , INPUT ); */
  RT_Q10_PORT &=~ RT_Q10_MASK; RT_Q10_DDR &=~ RT_Q10_MASK;  /* pinMode(RT_Q10, INPUT ); */
  RT_Q11_PORT &=~ RT_Q11_MASK; RT_Q11_DDR &=~ RT_Q11_MASK;  /* pinMode(RT_Q11, INPUT ); */
  RT_Q12_PORT &=~ RT_Q12_MASK; RT_Q12_DDR &=~ RT_Q12_MASK;  /* pinMode(RT_Q12, INPUT ); */
  RT_Q13_PORT &=~ RT_Q13_MASK; RT_Q13_DDR &=~ RT_Q13_MASK;  /* pinMode(RT_Q13, INPUT ); */
  RT_Q14_PORT &=~ RT_Q14_MASK; RT_Q14_DDR &=~ RT_Q14_MASK;  /* pinMode(RT_Q14, INPUT ); */
  RT_Q15_PORT &=~ RT_Q15_MASK; RT_Q15_DDR &=~ RT_Q15_MASK;  /* pinMode(RT_Q15, INPUT ); */
}

void rtio_deactivate() {
  RT_CE_PORT  |=  RT_CE_MASK ;  /* digitalWrite(RT_CE, HIGH); */
  RT_OE_PORT  |=  RT_OE_MASK ;  /* digitalWrite(RT_OE, HIGH); */
  RT_WE_PORT  |=  RT_WE_MASK ;  /* digitalWrite(RT_WE, HIGH); */
  RT_Q0_PORT  &=~ RT_Q0_MASK ; RT_Q0_DDR  &=~ RT_Q0_MASK ;  /* pinMode(RT_Q0 , INPUT); */
  RT_Q1_PORT  &=~ RT_Q1_MASK ; RT_Q1_DDR  &=~ RT_Q1_MASK ;  /* pinMode(RT_Q1 , INPUT); */
  RT_Q2_PORT  &=~ RT_Q2_MASK ; RT_Q2_DDR  &=~ RT_Q2_MASK ;  /* pinMode(RT_Q2 , INPUT); */
  RT_Q3_PORT  &=~ RT_Q3_MASK ; RT_Q3_DDR  &=~ RT_Q3_MASK ;  /* pinMode(RT_Q3 , INPUT); */
  RT_Q4_PORT  &=~ RT_Q4_MASK ; RT_Q4_DDR  &=~ RT_Q4_MASK ;  /* pinMode(RT_Q4 , INPUT); */
  RT_Q5_PORT  &=~ RT_Q5_MASK ; RT_Q5_DDR  &=~ RT_Q5_MASK ;  /* pinMode(RT_Q5 , INPUT); */
  RT_Q6_PORT  &=~ RT_Q6_MASK ; RT_Q6_DDR  &=~ RT_Q6_MASK ;  /* pinMode(RT_Q6 , INPUT); */
  RT_Q7_PORT  &=~ RT_Q7_MASK ; RT_Q7_DDR  &=~ RT_Q7_MASK ;  /* pinMode(RT_Q7 , INPUT); */
  RT_Q8_PORT  &=~ RT_Q8_MASK ; RT_Q8_DDR  &=~ RT_Q8_MASK ;  /* pinMode(RT_Q8 , INPUT); */
  RT_Q9_PORT  &=~ RT_Q9_MASK ; RT_Q9_DDR  &=~ RT_Q9_MASK ;  /* pinMode(RT_Q9 , INPUT); */
  RT_Q10_PORT &=~ RT_Q10_MASK; RT_Q10_DDR &=~ RT_Q10_MASK;  /* pinMode(RT_Q10, INPUT); */
  RT_Q11_PORT &=~ RT_Q11_MASK; RT_Q11_DDR &=~ RT_Q11_MASK;  /* pinMode(RT_Q11, INPUT); */
  RT_Q12_PORT &=~ RT_Q12_MASK; RT_Q12_DDR &=~ RT_Q12_MASK;  /* pinMode(RT_Q12, INPUT); */
  RT_Q13_PORT &=~ RT_Q13_MASK; RT_Q13_DDR &=~ RT_Q13_MASK;  /* pinMode(RT_Q13, INPUT); */
  RT_Q14_PORT &=~ RT_Q14_MASK; RT_Q14_DDR &=~ RT_Q14_MASK;  /* pinMode(RT_Q14, INPUT); */
  RT_Q15_PORT &=~ RT_Q15_MASK; RT_Q15_DDR &=~ RT_Q15_MASK;  /* pinMode(RT_Q15, INPUT); */
}

void rtio_read_mode() {
  RT_CE_PORT  |=  RT_CE_MASK ;  /* digitalWrite(RT_CE, HIGH); */
  RT_OE_PORT  &=~ RT_OE_MASK ;  /* digitalWrite(RT_OE, LOW ); */
  RT_WE_PORT  |=  RT_WE_MASK ;  /* digitalWrite(RT_WE, HIGH); */
  RT_Q0_PORT  &=~ RT_Q0_MASK ; RT_Q0_DDR  &=~ RT_Q0_MASK ;  /* pinMode(RT_Q0 , INPUT); */
  RT_Q1_PORT  &=~ RT_Q1_MASK ; RT_Q1_DDR  &=~ RT_Q1_MASK ;  /* pinMode(RT_Q1 , INPUT); */
  RT_Q2_PORT  &=~ RT_Q2_MASK ; RT_Q2_DDR  &=~ RT_Q2_MASK ;  /* pinMode(RT_Q2 , INPUT); */
  RT_Q3_PORT  &=~ RT_Q3_MASK ; RT_Q3_DDR  &=~ RT_Q3_MASK ;  /* pinMode(RT_Q3 , INPUT); */
  RT_Q4_PORT  &=~ RT_Q4_MASK ; RT_Q4_DDR  &=~ RT_Q4_MASK ;  /* pinMode(RT_Q4 , INPUT); */
  RT_Q5_PORT  &=~ RT_Q5_MASK ; RT_Q5_DDR  &=~ RT_Q5_MASK ;  /* pinMode(RT_Q5 , INPUT); */
  RT_Q6_PORT  &=~ RT_Q6_MASK ; RT_Q6_DDR  &=~ RT_Q6_MASK ;  /* pinMode(RT_Q6 , INPUT); */
  RT_Q7_PORT  &=~ RT_Q7_MASK ; RT_Q7_DDR  &=~ RT_Q7_MASK ;  /* pinMode(RT_Q7 , INPUT); */
  RT_Q8_PORT  &=~ RT_Q8_MASK ; RT_Q8_DDR  &=~ RT_Q8_MASK ;  /* pinMode(RT_Q8 , INPUT); */
  RT_Q9_PORT  &=~ RT_Q9_MASK ; RT_Q9_DDR  &=~ RT_Q9_MASK ;  /* pinMode(RT_Q9 , INPUT); */
  RT_Q10_PORT &=~ RT_Q10_MASK; RT_Q10_DDR &=~ RT_Q10_MASK;  /* pinMode(RT_Q10, INPUT); */
  RT_Q11_PORT &=~ RT_Q11_MASK; RT_Q11_DDR &=~ RT_Q11_MASK;  /* pinMode(RT_Q11, INPUT); */
  RT_Q12_PORT &=~ RT_Q12_MASK; RT_Q12_DDR &=~ RT_Q12_MASK;  /* pinMode(RT_Q12, INPUT); */
  RT_Q13_PORT &=~ RT_Q13_MASK; RT_Q13_DDR &=~ RT_Q13_MASK;  /* pinMode(RT_Q13, INPUT); */
  RT_Q14_PORT &=~ RT_Q14_MASK; RT_Q14_DDR &=~ RT_Q14_MASK;  /* pinMode(RT_Q14, INPUT); */
  RT_Q15_PORT &=~ RT_Q15_MASK; RT_Q15_DDR &=~ RT_Q15_MASK;  /* pinMode(RT_Q15, INPUT); */
}

void rtio_write_mode() {
  RT_CE_PORT  |=  RT_CE_MASK ;  /* digitalWrite(RT_CE, HIGH); */
  RT_OE_PORT  |=  RT_OE_MASK ;  /* digitalWrite(RT_OE, HIGH); */
  RT_WE_PORT  &=~ RT_WE_MASK ;  /* digitalWrite(RT_WE, LOW ); */
  RT_Q0_PORT  &=~ RT_Q0_MASK ; RT_Q0_DDR  |= RT_Q0_MASK ;  /* pinMode(RT_Q0 , OUTPUT); digitalWrite(RT_Q0 , LOW); */
  RT_Q1_PORT  &=~ RT_Q1_MASK ; RT_Q1_DDR  |= RT_Q1_MASK ;  /* pinMode(RT_Q1 , OUTPUT); digitalWrite(RT_Q1 , LOW); */
  RT_Q2_PORT  &=~ RT_Q2_MASK ; RT_Q2_DDR  |= RT_Q2_MASK ;  /* pinMode(RT_Q2 , OUTPUT); digitalWrite(RT_Q2 , LOW); */
  RT_Q3_PORT  &=~ RT_Q3_MASK ; RT_Q3_DDR  |= RT_Q3_MASK ;  /* pinMode(RT_Q3 , OUTPUT); digitalWrite(RT_Q3 , LOW); */
  RT_Q4_PORT  &=~ RT_Q4_MASK ; RT_Q4_DDR  |= RT_Q4_MASK ;  /* pinMode(RT_Q4 , OUTPUT); digitalWrite(RT_Q4 , LOW); */
  RT_Q5_PORT  &=~ RT_Q5_MASK ; RT_Q5_DDR  |= RT_Q5_MASK ;  /* pinMode(RT_Q5 , OUTPUT); digitalWrite(RT_Q5 , LOW); */
  RT_Q6_PORT  &=~ RT_Q6_MASK ; RT_Q6_DDR  |= RT_Q6_MASK ;  /* pinMode(RT_Q6 , OUTPUT); digitalWrite(RT_Q6 , LOW); */
  RT_Q7_PORT  &=~ RT_Q7_MASK ; RT_Q7_DDR  |= RT_Q7_MASK ;  /* pinMode(RT_Q7 , OUTPUT); digitalWrite(RT_Q7 , LOW); */
  RT_Q8_PORT  &=~ RT_Q8_MASK ; RT_Q8_DDR  |= RT_Q8_MASK ;  /* pinMode(RT_Q8 , OUTPUT); digitalWrite(RT_Q8 , LOW); */
  RT_Q9_PORT  &=~ RT_Q9_MASK ; RT_Q9_DDR  |= RT_Q9_MASK ;  /* pinMode(RT_Q9 , OUTPUT); digitalWrite(RT_Q9 , LOW); */
  RT_Q10_PORT &=~ RT_Q10_MASK; RT_Q10_DDR |= RT_Q10_MASK;  /* pinMode(RT_Q10, OUTPUT); digitalWrite(RT_Q10, LOW); */
  RT_Q11_PORT &=~ RT_Q11_MASK; RT_Q11_DDR |= RT_Q11_MASK;  /* pinMode(RT_Q11, OUTPUT); digitalWrite(RT_Q11, LOW); */
  RT_Q12_PORT &=~ RT_Q12_MASK; RT_Q12_DDR |= RT_Q12_MASK;  /* pinMode(RT_Q12, OUTPUT); digitalWrite(RT_Q12, LOW); */
  RT_Q13_PORT &=~ RT_Q13_MASK; RT_Q13_DDR |= RT_Q13_MASK;  /* pinMode(RT_Q13, OUTPUT); digitalWrite(RT_Q13, LOW); */
  RT_Q14_PORT &=~ RT_Q14_MASK; RT_Q14_DDR |= RT_Q14_MASK;  /* pinMode(RT_Q14, OUTPUT); digitalWrite(RT_Q14, LOW); */
  RT_Q15_PORT &=~ RT_Q15_MASK; RT_Q15_DDR |= RT_Q15_MASK;  /* pinMode(RT_Q15, OUTPUT); digitalWrite(RT_Q15, LOW); */
}

void rtio_set_addr(unsigned long addr) {
  if (addr & 0x00000001ul) RT_A0_PORT  |= RT_A0_MASK ; else RT_A0_PORT  &=~ RT_A0_MASK ;  /* digitalWrite(RT_A0 , (addr & 0x00000001ul) ? HIGH : LOW); */
  if (addr & 0x00000002ul) RT_A1_PORT  |= RT_A1_MASK ; else RT_A1_PORT  &=~ RT_A1_MASK ;  /* digitalWrite(RT_A1 , (addr & 0x00000002ul) ? HIGH : LOW); */
  if (addr & 0x00000004ul) RT_A2_PORT  |= RT_A2_MASK ; else RT_A2_PORT  &=~ RT_A2_MASK ;  /* digitalWrite(RT_A2 , (addr & 0x00000004ul) ? HIGH : LOW); */
  if (addr & 0x00000008ul) RT_A3_PORT  |= RT_A3_MASK ; else RT_A3_PORT  &=~ RT_A3_MASK ;  /* digitalWrite(RT_A3 , (addr & 0x00000008ul) ? HIGH : LOW); */
  if (addr & 0x00000010ul) RT_A4_PORT  |= RT_A4_MASK ; else RT_A4_PORT  &=~ RT_A4_MASK ;  /* digitalWrite(RT_A4 , (addr & 0x00000010ul) ? HIGH : LOW); */
  if (addr & 0x00000020ul) RT_A5_PORT  |= RT_A5_MASK ; else RT_A5_PORT  &=~ RT_A5_MASK ;  /* digitalWrite(RT_A5 , (addr & 0x00000020ul) ? HIGH : LOW); */
  if (addr & 0x00000040ul) RT_A6_PORT  |= RT_A6_MASK ; else RT_A6_PORT  &=~ RT_A6_MASK ;  /* digitalWrite(RT_A6 , (addr & 0x00000040ul) ? HIGH : LOW); */
  if (addr & 0x00000080ul) RT_A7_PORT  |= RT_A7_MASK ; else RT_A7_PORT  &=~ RT_A7_MASK ;  /* digitalWrite(RT_A7 , (addr & 0x00000080ul) ? HIGH : LOW); */
  if (addr & 0x00000100ul) RT_A8_PORT  |= RT_A8_MASK ; else RT_A8_PORT  &=~ RT_A8_MASK ;  /* digitalWrite(RT_A8 , (addr & 0x00000100ul) ? HIGH : LOW); */
  if (addr & 0x00000200ul) RT_A9_PORT  |= RT_A9_MASK ; else RT_A9_PORT  &=~ RT_A9_MASK ;  /* digitalWrite(RT_A9 , (addr & 0x00000200ul) ? HIGH : LOW); */
  if (addr & 0x00000400ul) RT_A10_PORT |= RT_A10_MASK; else RT_A10_PORT &=~ RT_A10_MASK;  /* digitalWrite(RT_A10, (addr & 0x00000400ul) ? HIGH : LOW); */
  if (addr & 0x00000800ul) RT_A11_PORT |= RT_A11_MASK; else RT_A11_PORT &=~ RT_A11_MASK;  /* digitalWrite(RT_A11, (addr & 0x00000800ul) ? HIGH : LOW); */
  if (addr & 0x00001000ul) RT_A12_PORT |= RT_A12_MASK; else RT_A12_PORT &=~ RT_A12_MASK;  /* digitalWrite(RT_A12, (addr & 0x00001000ul) ? HIGH : LOW); */
  if (addr & 0x00002000ul) RT_A13_PORT |= RT_A13_MASK; else RT_A13_PORT &=~ RT_A13_MASK;  /* digitalWrite(RT_A13, (addr & 0x00002000ul) ? HIGH : LOW); */
  if (addr & 0x00004000ul) RT_A14_PORT |= RT_A14_MASK; else RT_A14_PORT &=~ RT_A14_MASK;  /* digitalWrite(RT_A14, (addr & 0x00004000ul) ? HIGH : LOW); */
  if (addr & 0x00008000ul) RT_A15_PORT |= RT_A15_MASK; else RT_A15_PORT &=~ RT_A15_MASK;  /* digitalWrite(RT_A15, (addr & 0x00008000ul) ? HIGH : LOW); */
  if (addr & 0x00010000ul) RT_A16_PORT |= RT_A16_MASK; else RT_A16_PORT &=~ RT_A16_MASK;  /* digitalWrite(RT_A16, (addr & 0x00010000ul) ? HIGH : LOW); */
  if (addr & 0x00020000ul) RT_A17_PORT |= RT_A17_MASK; else RT_A17_PORT &=~ RT_A17_MASK;  /* digitalWrite(RT_A17, (addr & 0x00020000ul) ? HIGH : LOW); */
  if (addr & 0x00040000ul) RT_A18_PORT |= RT_A18_MASK; else RT_A18_PORT &=~ RT_A18_MASK;  /* digitalWrite(RT_A18, (addr & 0x00040000ul) ? HIGH : LOW); */
  if (addr & 0x00080000ul) RT_A19_PORT |= RT_A19_MASK; else RT_A19_PORT &=~ RT_A19_MASK;  /* digitalWrite(RT_A19, (addr & 0x00080000ul) ? HIGH : LOW); */
  if (addr & 0x00100000ul) RT_A20_PORT |= RT_A20_MASK; else RT_A20_PORT &=~ RT_A20_MASK;  /* digitalWrite(RT_A20, (addr & 0x00100000ul) ? HIGH : LOW); */
  if (addr & 0x00200000ul) RT_A21_PORT |= RT_A21_MASK; else RT_A21_PORT &=~ RT_A21_MASK;  /* digitalWrite(RT_A21, (addr & 0x00200000ul) ? HIGH : LOW); */
  if (addr & 0x00400000ul) RT_A22_PORT |= RT_A22_MASK; else RT_A22_PORT &=~ RT_A22_MASK;  /* digitalWrite(RT_A22, (addr & 0x00400000ul) ? HIGH : LOW); */
  if (addr & 0x00800000ul) RT_A23_PORT |= RT_A23_MASK; else RT_A23_PORT &=~ RT_A23_MASK;  /* digitalWrite(RT_A23, (addr & 0x00800000ul) ? HIGH : LOW); */
  if (addr & 0x01000000ul) RT_A24_PORT |= RT_A24_MASK; else RT_A24_PORT &=~ RT_A24_MASK;  /* digitalWrite(RT_A24, (addr & 0x01000000ul) ? HIGH : LOW); */
  if (addr & 0x02000000ul) RT_A25_PORT |= RT_A25_MASK; else RT_A25_PORT &=~ RT_A25_MASK;  /* digitalWrite(RT_A25, (addr & 0x02000000ul) ? HIGH : LOW); */
  if (addr & 0x04000000ul) RT_A26_PORT |= RT_A26_MASK; else RT_A26_PORT &=~ RT_A26_MASK;  /* digitalWrite(RT_A26, (addr & 0x04000000ul) ? HIGH : LOW); */
  if (addr & 0x08000000ul) RT_A27_PORT |= RT_A27_MASK; else RT_A27_PORT &=~ RT_A27_MASK;  /* digitalWrite(RT_A27, (addr & 0x08000000ul) ? HIGH : LOW); */
  if (addr & 0x10000000ul) RT_A28_PORT |= RT_A28_MASK; else RT_A28_PORT &=~ RT_A28_MASK;  /* digitalWrite(RT_A28, (addr & 0x10000000ul) ? HIGH : LOW); */
  if (addr & 0x20000000ul) RT_A29_PORT |= RT_A29_MASK; else RT_A29_PORT &=~ RT_A29_MASK;  /* digitalWrite(RT_A29, (addr & 0x20000000ul) ? HIGH : LOW); */
  if (addr & 0x40000000ul) RT_A30_PORT |= RT_A30_MASK; else RT_A30_PORT &=~ RT_A30_MASK;  /* digitalWrite(RT_A30, (addr & 0x40000000ul) ? HIGH : LOW); */ 
}

void rtio_set_data(unsigned int data) {
  if (data & 0x0001) RT_Q0_PORT  |= RT_Q0_MASK ; else RT_Q0_PORT  &=~ RT_Q0_MASK ;  /* digitalWrite(RT_Q0 , (data & 0x0001) ? HIGH : LOW); */
  if (data & 0x0002) RT_Q1_PORT  |= RT_Q1_MASK ; else RT_Q1_PORT  &=~ RT_Q1_MASK ;  /* digitalWrite(RT_Q1 , (data & 0x0002) ? HIGH : LOW); */
  if (data & 0x0004) RT_Q2_PORT  |= RT_Q2_MASK ; else RT_Q2_PORT  &=~ RT_Q2_MASK ;  /* digitalWrite(RT_Q2 , (data & 0x0004) ? HIGH : LOW); */
  if (data & 0x0008) RT_Q3_PORT  |= RT_Q3_MASK ; else RT_Q3_PORT  &=~ RT_Q3_MASK ;  /* digitalWrite(RT_Q3 , (data & 0x0008) ? HIGH : LOW); */
  if (data & 0x0010) RT_Q4_PORT  |= RT_Q4_MASK ; else RT_Q4_PORT  &=~ RT_Q4_MASK ;  /* digitalWrite(RT_Q4 , (data & 0x0010) ? HIGH : LOW); */
  if (data & 0x0020) RT_Q5_PORT  |= RT_Q5_MASK ; else RT_Q5_PORT  &=~ RT_Q5_MASK ;  /* digitalWrite(RT_Q5 , (data & 0x0020) ? HIGH : LOW); */
  if (data & 0x0040) RT_Q6_PORT  |= RT_Q6_MASK ; else RT_Q6_PORT  &=~ RT_Q6_MASK ;  /* digitalWrite(RT_Q6 , (data & 0x0040) ? HIGH : LOW); */
  if (data & 0x0080) RT_Q7_PORT  |= RT_Q7_MASK ; else RT_Q7_PORT  &=~ RT_Q7_MASK ;  /* digitalWrite(RT_Q7 , (data & 0x0080) ? HIGH : LOW); */
  if (data & 0x0100) RT_Q8_PORT  |= RT_Q8_MASK ; else RT_Q8_PORT  &=~ RT_Q8_MASK ;  /* digitalWrite(RT_Q8 , (data & 0x0100) ? HIGH : LOW); */
  if (data & 0x0200) RT_Q9_PORT  |= RT_Q9_MASK ; else RT_Q9_PORT  &=~ RT_Q9_MASK ;  /* digitalWrite(RT_Q9 , (data & 0x0200) ? HIGH : LOW); */
  if (data & 0x0400) RT_Q10_PORT |= RT_Q10_MASK; else RT_Q10_PORT &=~ RT_Q10_MASK;  /* digitalWrite(RT_Q10, (data & 0x0400) ? HIGH : LOW); */
  if (data & 0x0800) RT_Q11_PORT |= RT_Q11_MASK; else RT_Q11_PORT &=~ RT_Q11_MASK;  /* digitalWrite(RT_Q11, (data & 0x0800) ? HIGH : LOW); */
  if (data & 0x1000) RT_Q12_PORT |= RT_Q12_MASK; else RT_Q12_PORT &=~ RT_Q12_MASK;  /* digitalWrite(RT_Q12, (data & 0x1000) ? HIGH : LOW); */
  if (data & 0x2000) RT_Q13_PORT |= RT_Q13_MASK; else RT_Q13_PORT &=~ RT_Q13_MASK;  /* digitalWrite(RT_Q13, (data & 0x2000) ? HIGH : LOW); */
  if (data & 0x4000) RT_Q14_PORT |= RT_Q14_MASK; else RT_Q14_PORT &=~ RT_Q14_MASK;  /* digitalWrite(RT_Q14, (data & 0x4000) ? HIGH : LOW); */
  if (data & 0x8000) RT_Q15_PORT |= RT_Q15_MASK; else RT_Q15_PORT &=~ RT_Q15_MASK;  /* digitalWrite(RT_Q15, (data & 0x8000) ? HIGH : LOW); */
}

unsigned int rtio_read_data() {
  unsigned int data = 0;
  if (RT_Q0_PIN  & RT_Q0_MASK ) data |= 0x0001;  /* if (digitalRead(RT_Q0 )) data |= 0x0001; */
  if (RT_Q1_PIN  & RT_Q1_MASK ) data |= 0x0002;  /* if (digitalRead(RT_Q1 )) data |= 0x0002; */
  if (RT_Q2_PIN  & RT_Q2_MASK ) data |= 0x0004;  /* if (digitalRead(RT_Q2 )) data |= 0x0004; */
  if (RT_Q3_PIN  & RT_Q3_MASK ) data |= 0x0008;  /* if (digitalRead(RT_Q3 )) data |= 0x0008; */
  if (RT_Q4_PIN  & RT_Q4_MASK ) data |= 0x0010;  /* if (digitalRead(RT_Q4 )) data |= 0x0010; */
  if (RT_Q5_PIN  & RT_Q5_MASK ) data |= 0x0020;  /* if (digitalRead(RT_Q5 )) data |= 0x0020; */
  if (RT_Q6_PIN  & RT_Q6_MASK ) data |= 0x0040;  /* if (digitalRead(RT_Q6 )) data |= 0x0040; */
  if (RT_Q7_PIN  & RT_Q7_MASK ) data |= 0x0080;  /* if (digitalRead(RT_Q7 )) data |= 0x0080; */
  if (RT_Q8_PIN  & RT_Q8_MASK ) data |= 0x0100;  /* if (digitalRead(RT_Q8 )) data |= 0x0100; */
  if (RT_Q9_PIN  & RT_Q9_MASK ) data |= 0x0200;  /* if (digitalRead(RT_Q9 )) data |= 0x0200; */
  if (RT_Q10_PIN & RT_Q10_MASK) data |= 0x0400;  /* if (digitalRead(RT_Q10)) data |= 0x0400; */
  if (RT_Q11_PIN & RT_Q11_MASK) data |= 0x0800;  /* if (digitalRead(RT_Q11)) data |= 0x0800; */
  if (RT_Q12_PIN & RT_Q12_MASK) data |= 0x1000;  /* if (digitalRead(RT_Q12)) data |= 0x1000; */
  if (RT_Q13_PIN & RT_Q13_MASK) data |= 0x2000;  /* if (digitalRead(RT_Q13)) data |= 0x2000; */
  if (RT_Q14_PIN & RT_Q14_MASK) data |= 0x4000;  /* if (digitalRead(RT_Q14)) data |= 0x4000; */
  if (RT_Q15_PIN & RT_Q15_MASK) data |= 0x8000;  /* if (digitalRead(RT_Q15)) data |= 0x8000; */
  return data;
}

void rtio_enable() {
  RT_CE_PORT &=~ RT_CE_MASK;  /* digitalWrite(RT_CE, LOW); */
}

void rtio_disable() {
  RT_CE_PORT |= RT_CE_MASK;  /* digitalWrite(RT_CE, HIGH); */
}
