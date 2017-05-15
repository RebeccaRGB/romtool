#include <Arduino.h>
#include "gpio.h"

int a = 13;
int s =  0;

void setup() {
  Serial.begin(250000);
}

void loop() {
  switch (Serial.read()) {
    case '2': a =  2; break; case '3': a =  3; break; case '4': a =  4; break; case '5': a =  5; break;
    case '6': a =  6; break; case '7': a =  7; break; case '8': a =  8; break; case '9': a =  9; break;
    case 'A': a = 10; break; case 'B': a = 11; break; case 'C': a = 12; break; case 'D': a = 13; break;
    case 'E': a = 14; break; case 'F': a = 15; break; case 'G': a = 16; break; case 'H': a = 17; break;
    case 'I': a = 18; break; case 'J': a = 19; break; case 'K': a = 20; break; case 'L': a = 21; break;
    case 'M': a = 22; break; case 'N': a = 23; break; case 'O': a = 24; break; case 'P': a = 25; break;
    case 'Q': a = 26; break; case 'R': a = 27; break; case 'S': a = 28; break; case 'T': a = 29; break;
    case 'U': a = 30; break; case 'V': a = 31; break; case 'W': a = 32; break; case 'X': a = 33; break;
    case 'Y': a = 34; break; case 'Z': a = 35; break; case 'a': a = 36; break; case 'b': a = 37; break;
    case 'c': a = 38; break; case 'd': a = 39; break; case 'e': a = 40; break; case 'f': a = 41; break;
    case 'g': a = 42; break; case 'h': a = 43; break; case 'i': a = 44; break; case 'j': a = 45; break;
    case 'k': a = 46; break; case 'l': a = 47; break; case 'm': a = 48; break; case 'n': a = 49; break;
    case 'o': a = 50; break; case 'p': a = 51; break; case 'q': a = 52; break; case 'r': a = 53; break;
    case '@': Serial.write((a < 10) ? ('0' + a) : (a < 36) ? ('A' + a - 10) : ('a' + a - 36)); break;

    case ':': s =  0; break;
    case '(': s = -1; break; case ')': s = +1; break;
    case '{': s = -2; break; case '}': s = +2; break;
    case '$': Serial.write((s < -1) ? '{' : (s > +1) ? '}' : (s < 0) ? '(' : (s > 0) ? ')' : ':'); break;

    case '-': a -= s; if (a < 2) a = 2; if (a > 53) a = 53; break;
    case '+': a += s; if (a < 2) a = 2; if (a > 53) a = 53; break;

    case '<': setDir(a, 0); a += s; if (a < 2) a = 2; if (a > 53) a = 53; break;
    case '>': setDir(a, 1); a += s; if (a < 2) a = 2; if (a > 53) a = 53; break;
    case '0': setPin(a, 0); a += s; if (a < 2) a = 2; if (a > 53) a = 53; break;
    case '1': setPin(a, 1); a += s; if (a < 2) a = 2; if (a > 53) a = 53; break;
    case '!': togglePin(a); a += s; if (a < 2) a = 2; if (a > 53) a = 53; break;

    case '[': setDir(a, 0); break;
    case ']': setDir(a, 1); break;
    case'\\': setPin(a, 0); break;
    case '/': setPin(a, 1); break;
    case '^': togglePin(a); break;

    case '=': Serial.write(getPin(a) ? '1' : '0'); break;
    case '?': Serial.write(getPin(a) ? '1' : '0'); a += s; if (a < 2) a = 2; if (a > 53) a = 53; break;
  }
}
