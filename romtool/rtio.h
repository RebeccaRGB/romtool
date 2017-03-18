#ifndef RTIO_H
#define RTIO_H

/* Digital Pin Numbers for Control Lines */

#define RT_CE   13
#define RT_OE   12
#define RT_WE   11

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
