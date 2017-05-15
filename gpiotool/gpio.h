#ifndef GPIO_H
#define GPIO_H

void setDir(int pin, int dir);
void setPin(int pin, int val);
void togglePin(int pin);
int getPin(int pin);

#endif
