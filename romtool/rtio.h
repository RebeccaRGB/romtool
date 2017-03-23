#ifndef RTIO_H
#define RTIO_H

/* Digital Pin Numbers for Control Lines */

#define RT_CE   13
#define RT_OE   12
#define RT_WE   11

#define RT_CE_DDR    DDRB
#define RT_CE_PORT   PORTB
#define RT_CE_MASK   0x80

#define RT_OE_DDR    DDRB
#define RT_OE_PORT   PORTB
#define RT_OE_MASK   0x40

#define RT_WE_DDR    DDRB
#define RT_WE_PORT   PORTB
#define RT_WE_MASK   0x20

/* Digital Pin Numbers for Address Lines */

#define RT_A0   22
#define RT_A1   24
#define RT_A2   26
#define RT_A3   28
#define RT_A4   30
#define RT_A5   32
#define RT_A6   34
#define RT_A7   36
#define RT_A8   38
#define RT_A9   40
#define RT_A10  42
#define RT_A11  44
#define RT_A12  46
#define RT_A13  48
#define RT_A14  50
#define RT_A15  52
#define RT_A16  19
#define RT_A17  18
#define RT_A18  17
#define RT_A19  16
#define RT_A20  15
#define RT_A21  14
#define RT_A22   2
#define RT_A23   3
#define RT_A24   4
#define RT_A25   5
#define RT_A26   6
#define RT_A27   7
#define RT_A28   8
#define RT_A29   9
#define RT_A30  10

#define RT_A0_DDR    DDRA
#define RT_A0_PORT   PORTA
#define RT_A0_MASK   0x01

#define RT_A1_DDR    DDRA
#define RT_A1_PORT   PORTA
#define RT_A1_MASK   0x04

#define RT_A2_DDR    DDRA
#define RT_A2_PORT   PORTA
#define RT_A2_MASK   0x10

#define RT_A3_DDR    DDRA
#define RT_A3_PORT   PORTA
#define RT_A3_MASK   0x40

#define RT_A4_DDR    DDRC
#define RT_A4_PORT   PORTC
#define RT_A4_MASK   0x80

#define RT_A5_DDR    DDRC
#define RT_A5_PORT   PORTC
#define RT_A5_MASK   0x20

#define RT_A6_DDR    DDRC
#define RT_A6_PORT   PORTC
#define RT_A6_MASK   0x08

#define RT_A7_DDR    DDRC
#define RT_A7_PORT   PORTC
#define RT_A7_MASK   0x02

#define RT_A8_DDR    DDRD
#define RT_A8_PORT   PORTD
#define RT_A8_MASK   0x80

#define RT_A9_DDR    DDRG
#define RT_A9_PORT   PORTG
#define RT_A9_MASK   0x02

#define RT_A10_DDR    DDRL
#define RT_A10_PORT   PORTL
#define RT_A10_MASK   0x80

#define RT_A11_DDR    DDRL
#define RT_A11_PORT   PORTL
#define RT_A11_MASK   0x20

#define RT_A12_DDR    DDRL
#define RT_A12_PORT   PORTL
#define RT_A12_MASK   0x08

#define RT_A13_DDR    DDRL
#define RT_A13_PORT   PORTL
#define RT_A13_MASK   0x02

#define RT_A14_DDR    DDRB
#define RT_A14_PORT   PORTB
#define RT_A14_MASK   0x08

#define RT_A15_DDR    DDRB
#define RT_A15_PORT   PORTB
#define RT_A15_MASK   0x02

#define RT_A16_DDR    DDRD
#define RT_A16_PORT   PORTD
#define RT_A16_MASK   0x04

#define RT_A17_DDR    DDRD
#define RT_A17_PORT   PORTD
#define RT_A17_MASK   0x08

#define RT_A18_DDR    DDRH
#define RT_A18_PORT   PORTH
#define RT_A18_MASK   0x01

#define RT_A19_DDR    DDRH
#define RT_A19_PORT   PORTH
#define RT_A19_MASK   0x02

#define RT_A20_DDR    DDRJ
#define RT_A20_PORT   PORTJ
#define RT_A20_MASK   0x01

#define RT_A21_DDR    DDRJ
#define RT_A21_PORT   PORTJ
#define RT_A21_MASK   0x02

#define RT_A22_DDR    DDRE
#define RT_A22_PORT   PORTE
#define RT_A22_MASK   0x10

#define RT_A23_DDR    DDRE
#define RT_A23_PORT   PORTE
#define RT_A23_MASK   0x20

#define RT_A24_DDR    DDRG
#define RT_A24_PORT   PORTG
#define RT_A24_MASK   0x20

#define RT_A25_DDR    DDRE
#define RT_A25_PORT   PORTE
#define RT_A25_MASK   0x08

#define RT_A26_DDR    DDRH
#define RT_A26_PORT   PORTH
#define RT_A26_MASK   0x08

#define RT_A27_DDR    DDRH
#define RT_A27_PORT   PORTH
#define RT_A27_MASK   0x10

#define RT_A28_DDR    DDRH
#define RT_A28_PORT   PORTH
#define RT_A28_MASK   0x20

#define RT_A29_DDR    DDRH
#define RT_A29_PORT   PORTH
#define RT_A29_MASK   0x40

#define RT_A30_DDR    DDRB
#define RT_A30_PORT   PORTB
#define RT_A30_MASK   0x10

/* Digital Pin Numbers for Data Lines */

#define RT_Q0   23
#define RT_Q1   25
#define RT_Q2   27
#define RT_Q3   29
#define RT_Q4   31
#define RT_Q5   33
#define RT_Q6   35
#define RT_Q7   37
#define RT_Q8   39
#define RT_Q9   41
#define RT_Q10  43
#define RT_Q11  45
#define RT_Q12  47
#define RT_Q13  49
#define RT_Q14  51
#define RT_Q15  53

#define RT_Q0_DDR    DDRA
#define RT_Q0_PORT   PORTA
#define RT_Q0_PIN    PINA
#define RT_Q0_MASK   0x02

#define RT_Q1_DDR    DDRA
#define RT_Q1_PORT   PORTA
#define RT_Q1_PIN    PINA
#define RT_Q1_MASK   0x08

#define RT_Q2_DDR    DDRA
#define RT_Q2_PORT   PORTA
#define RT_Q2_PIN    PINA
#define RT_Q2_MASK   0x20

#define RT_Q3_DDR    DDRA
#define RT_Q3_PORT   PORTA
#define RT_Q3_PIN    PINA
#define RT_Q3_MASK   0x80

#define RT_Q4_DDR    DDRC
#define RT_Q4_PORT   PORTC
#define RT_Q4_PIN    PINC
#define RT_Q4_MASK   0x40

#define RT_Q5_DDR    DDRC
#define RT_Q5_PORT   PORTC
#define RT_Q5_PIN    PINC
#define RT_Q5_MASK   0x10

#define RT_Q6_DDR    DDRC
#define RT_Q6_PORT   PORTC
#define RT_Q6_PIN    PINC
#define RT_Q6_MASK   0x04

#define RT_Q7_DDR    DDRC
#define RT_Q7_PORT   PORTC
#define RT_Q7_PIN    PINC
#define RT_Q7_MASK   0x01

#define RT_Q8_DDR    DDRG
#define RT_Q8_PORT   PORTG
#define RT_Q8_PIN    PING
#define RT_Q8_MASK   0x04

#define RT_Q9_DDR    DDRG
#define RT_Q9_PORT   PORTG
#define RT_Q9_PIN    PING
#define RT_Q9_MASK   0x01

#define RT_Q10_DDR    DDRL
#define RT_Q10_PORT   PORTL
#define RT_Q10_PIN    PINL
#define RT_Q10_MASK   0x40

#define RT_Q11_DDR    DDRL
#define RT_Q11_PORT   PORTL
#define RT_Q11_PIN    PINL
#define RT_Q11_MASK   0x10

#define RT_Q12_DDR    DDRL
#define RT_Q12_PORT   PORTL
#define RT_Q12_PIN    PINL
#define RT_Q12_MASK   0x04

#define RT_Q13_DDR    DDRL
#define RT_Q13_PORT   PORTL
#define RT_Q13_PIN    PINL
#define RT_Q13_MASK   0x01

#define RT_Q14_DDR    DDRB
#define RT_Q14_PORT   PORTB
#define RT_Q14_PIN    PINB
#define RT_Q14_MASK   0x04

#define RT_Q15_DDR    DDRB
#define RT_Q15_PORT   PORTB
#define RT_Q15_PIN    PINB
#define RT_Q15_MASK   0x01

/* Interface */

void rtio_init();
void rtio_deactivate();
void rtio_read_mode();
void rtio_write_mode();
void rtio_set_addr(unsigned long addr);
void rtio_set_data(unsigned int data);
unsigned int rtio_read_data();
void rtio_enable();
void rtio_disable();

#endif
