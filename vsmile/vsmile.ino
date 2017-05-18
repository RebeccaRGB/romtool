// VTech VSmile controller host demo

#include <Arduino.h>
#include "vserial.h"

static char * hex[256] = {
  "00","01","02","03","04","05","06","07","08","09","0A","0B","0C","0D","0E","0F",
  "10","11","12","13","14","15","16","17","18","19","1A","1B","1C","1D","1E","1F",
  "20","21","22","23","24","25","26","27","28","29","2A","2B","2C","2D","2E","2F",
  "30","31","32","33","34","35","36","37","38","39","3A","3B","3C","3D","3E","3F",
  "40","41","42","43","44","45","46","47","48","49","4A","4B","4C","4D","4E","4F",
  "50","51","52","53","54","55","56","57","58","59","5A","5B","5C","5D","5E","5F",
  "60","61","62","63","64","65","66","67","68","69","6A","6B","6C","6D","6E","6F",
  "70","71","72","73","74","75","76","77","78","79","7A","7B","7C","7D","7E","7F",
  "80","81","82","83","84","85","86","87","88","89","8A","8B","8C","8D","8E","8F",
  "90","91","92","93","94","95","96","97","98","99","9A","9B","9C","9D","9E","9F",
  "A0","A1","A2","A3","A4","A5","A6","A7","A8","A9","AA","AB","AC","AD","AE","AF",
  "B0","B1","B2","B3","B4","B5","B6","B7","B8","B9","BA","BB","BC","BD","BE","BF",
  "C0","C1","C2","C3","C4","C5","C6","C7","C8","C9","CA","CB","CC","CD","CE","CF",
  "D0","D1","D2","D3","D4","D5","D6","D7","D8","D9","DA","DB","DC","DD","DE","DF",
  "E0","E1","E2","E3","E4","E5","E6","E7","E8","E9","EA","EB","EC","ED","EE","EF",
  "F0","F1","F2","F3","F4","F5","F6","F7","F8","F9","FA","FB","FC","FD","FE","FF",
};

unsigned long lastSync;
int a = 0;
int leds = 0;
int h = -1;

void setup() {
  Serial.begin(9600);
  vserial_begin();
  lastSync = millis();
}

void loop() {
  a = vserial_read();
  if (a >= 0) {
    Serial.write(hex[a]);
    switch (a) {
      // messages from controller:
      // 55 - heartbeat every second; system responds with E4 D4 6x
      // 8x - vertical axis: 0 = center, 3..7 = up, B..F = down
      // 9x - color buttons: 8 = red, 4 = yellow, 2 = blue, 1 = green (bit mask)
      // Ax - action buttons: 1 = enter, 2 = exit, 3 = help, 4 = learning zone (abc)
      // Bx - some kind of sync signal; sent in response to a Bx message from system
      // Cx - horizontal axis: 0 = center, 3..7 = right, B..F = left;
      //      joystick state is always sent as a Cx message followed by an 8x message
      case 0x55: Serial.write(" heartbeat"); break;
      case 0x80: Serial.write(" v-center"); break;
      case 0x83: Serial.write(" up-1"); break;
      case 0x84: Serial.write(" up-2"); break;
      case 0x85: Serial.write(" up-3"); break;
      case 0x86: Serial.write(" up-4"); break;
      case 0x87: Serial.write(" up-5"); break;
      case 0x8B: Serial.write(" down-1"); break;
      case 0x8C: Serial.write(" down-2"); break;
      case 0x8D: Serial.write(" down-3"); break;
      case 0x8E: Serial.write(" down-4"); break;
      case 0x8F: Serial.write(" down-5"); break;
      case 0x90: Serial.write(" no-color"); break;
      case 0x91: Serial.write(" green"); break;
      case 0x92: Serial.write(" blue"); break;
      case 0x93: Serial.write(" blue green"); break;
      case 0x94: Serial.write(" yellow"); break;
      case 0x95: Serial.write(" yellow green"); break;
      case 0x96: Serial.write(" yellow blue"); break;
      case 0x97: Serial.write(" yellow blue green"); break;
      case 0x98: Serial.write(" red"); break;
      case 0x99: Serial.write(" red green"); break;
      case 0x9A: Serial.write(" red blue"); break;
      case 0x9B: Serial.write(" red blue green"); break;
      case 0x9C: Serial.write(" red yellow"); break;
      case 0x9D: Serial.write(" red yellow green"); break;
      case 0x9E: Serial.write(" red yellow blue"); break;
      case 0x9F: Serial.write(" red yellow blue green"); break;
      case 0xA0: Serial.write(" no-action"); break;
      case 0xA1: Serial.write(" enter"); break;
      case 0xA2: Serial.write(" exit"); break;
      case 0xA3: Serial.write(" help"); break;
      case 0xA4: Serial.write(" learning-zone"); break;
      case 0xC0: Serial.write(" h-center"); break;
      case 0xC3: Serial.write(" right-1"); break;
      case 0xC4: Serial.write(" right-2"); break;
      case 0xC5: Serial.write(" right-3"); break;
      case 0xC6: Serial.write(" right-4"); break;
      case 0xC7: Serial.write(" right-5"); break;
      case 0xCB: Serial.write(" left-1"); break;
      case 0xCC: Serial.write(" left-2"); break;
      case 0xCD: Serial.write(" left-3"); break;
      case 0xCE: Serial.write(" left-4"); break;
      case 0xCF: Serial.write(" left-5"); break;
      default: Serial.write(" ?"); break;
    }
    Serial.write('\n');
  }

  // messages to controller:
  // 6x - set leds: 8 = red, 4 = yellow, 2 = blue, 1 = green (bit mask)
  // Bx - some kind of sync signal; controller responds with a different Bx message;
  //      if controller goes ~90 seconds without a Bx message, it goes to sleep
  // D4 - second byte of response to heartbeat
  // E4 - first byte of response to heartbeat

  // Every second, the controller sends a 55 message to the system,
  // and the system responds with E4 D4 6x where x is the state of the LEDs.
  // If the controller does not receive a response, it goes to sleep:
  // the 55 heartbeat continues but no other messages are sent until
  // it receives a response.
  if (a == 0x55) {
    delay(8);
    vserial_write(0xE4);
    delay(8);
    vserial_write(0xD4);
    delay(8);
    vserial_write(0x60 | leds);
    delay(8);
  }

  // This is not a part of the communication protocol;
  // it's just a demo of using the color buttons to control the LEDs.
  if ((a & 0xF0) == 0x90) {
    leds = a & 0x0F;
    delay(8);
    vserial_write(0x60 | leds);
    delay(8);
  }

  // Every so often the system sends a Bx message to the controller,
  // and the controller responds with a different Bx message.
  // The Bx message the controller responds with is a function of the
  // last two Bx messages it received: the last two messages are added
  // modulo 16 and used as an index into the following array:
  // BA B5 B4 B7 B6 B1 B0 B3 B2 BD BC BF BE B9 B8 BB
  // Equivalently, if a and b are the last two Bx messages and c is
  // the response, c = (((a + b + 0x0F) & 0x0F) ^ 0xB5).
  // If the controller goes ~90 seconds without receiving a Bx message,
  // it goes to sleep: the 55 heartbeat continues but no other messages
  // are sent until it receives another Bx message.
  if ((millis() - lastSync) > 60000) {
    delay(8);
    vserial_write(0xB1);
    delay(8);
    lastSync = millis();
  }

  // forward hex data received by arduino to controller
  a = Serial.read();
  if (a == '*' || a == 'R' || a == 'r') {
    delay(8);
    vserial_reset();
    delay(8);
    lastSync = millis();
    h = -1;
    return;
  }
  else if (a == '$' || a == 'X' || a == 'x') { h = -1; return; }
  else if (a >= '0' && a <= '9') a = a - '0';
  else if (a >= 'A' && a <= 'F') a = a - 'A' + 10;
  else if (a >= 'a' && a <= 'f') a = a - 'a' + 10;
  else return;
  if (h < 0) { h = (a << 4); return; }
  if (h == 0x60) leds = a;
  delay(8);
  vserial_write(h | a);
  delay(8);
  if (h == 0xB0) lastSync = millis();
  h = -1;
}
