#include <Arduino.h>

int i;
int x;

void setup() {
  unsigned long baseline = -micros();
  for (i = 0; i < 1000; i++);
  baseline += micros();

  DDRA |= 0x08;
  PORTA &=~ 0x08;

  unsigned long forSet = -micros();
  for (i = 0; i < 1000; i++) {
    PORTA |= 0x08;
  }
  forSet += micros();
  forSet -= baseline;

  unsigned long forClear = -micros();
  for (i = 0; i < 1000; i++) {
    PORTA &=~ 0x08;
  }
  forClear += micros();
  forClear -= baseline;

  unsigned long forWrite = -micros();
  for (i = 0; i < 1000; i++) {
    if (i & 0x08) PORTA |= 0x08; else PORTA &=~ 0x08;
  }
  forWrite += micros();
  forWrite -= baseline;

  DDRA &=~ 0x08;
  PORTA |= 0x08;

  unsigned long forRead = -micros();
  for (i = 0; i < 1000; i++) {
    if (PINA & 0x08) x |= 0x08;
  }
  forRead += micros();
  forRead -= baseline;

  Serial.begin(9600);
  Serial.println();

  Serial.print("Baseline: ");
  Serial.print(baseline);
  Serial.println(" ns");

  Serial.print("Set: ");
  Serial.print(forSet);
  Serial.println(" ns");

  Serial.print("Clear: ");
  Serial.print(forClear);
  Serial.println(" ns");

  Serial.print("Write: ");
  Serial.print(forWrite);
  Serial.println(" ns");

  Serial.print("Read: ");
  Serial.print(forRead);
  Serial.println(" ns");

  Serial.println();
  Serial.end();
}

void loop() {}
