// http://atariage.com/forums/topic/232752-5v-to-atari-joystick-ports/
// http://www.instructables.com/id/Arduino-lets-you-play-Atari-2600-and-ZX-Spectrum-u/

#include "NesController.h"

NesController nes(4,3,2);

// C64 button defs
#define C64_UP 0
#define C64_DOWN 1
#define C64_LEFT 2
#define C64_RIGHT 3
#define C64_FIRE 4

#define TURBO_LED A1
#define BJUMP_LED A2

// select toggles B buttom mode
// true for UP, false for FIRE
bool selectPressed = false;
bool selectPressed_ = false;
bool bJump = false;

// start toggles turbo mode
// true on, false off natch
bool startPressed = false;
bool startPressed_ = false;
bool turboOn = false;

// turbo vars and defs
#define TURBO_FREQ 25
uint64_t turboDelay = 1000 / TURBO_FREQ / 2;
bool firing = true;
uint64_t lastTurboToggle = 0;

// data read from NES controller
// 8 bits: ABStSeUDLR
uint8_t nesData = 0;

// data to be sent to C64
// 8 bits: ___FRLDU
uint8_t c64Data = 0;

bool turboFire() {
  if ( turboOn ) {
    // turbo on
    uint64_t crtTime = millis();
    if ( crtTime - lastTurboToggle > turboDelay ) {
      firing = !firing;
    };
    return firing;
  } else {
    // turbo off, always fire
    return true;
  }
}

void setup() {
    // pins are set as inputs to emulate open collector outputs
    DDRB = B00000000;
    // set low
    PORTB = B00000000;
    // mode indicator LEDs
    pinMode(TURBO_LED, OUTPUT);
    pinMode(BJUMP_LED, OUTPUT);
}

void loop() {
  // reset c64 data
  c64Data = B00000000;
  // read NES data
  nesData = nes.read();

  // toggle "start" state when button is pressed
  startPressed_ = startPressed;
  startPressed = bitRead(nesData, bStart);
  if( startPressed && !startPressed_) {
    turboOn = !turboOn;
    digitalWrite( TURBO_LED, turboOn);
    if ( turboOn )  {
      firing = true;
      lastTurboToggle = millis();
    }
  }

  // toggle "select" state when button is pressed
  selectPressed_ = selectPressed;
  selectPressed = bitRead(nesData, bSelect);
  if( selectPressed && !selectPressed_) {
    bJump = !bJump;
    digitalWrite(BJUMP_LED, bJump);
  }

  // C64 FIRE with optional turbo if ( NES A is pressed )
  if (bitRead(nesData, bA)) {
    bitWrite(c64Data, C64_FIRE, turboFire());
  }

  // C64 FIRE without turbo if ( NES B is pressed and NES B is in fire mode)
  // useful for firing single shots with B while button A is in turbo mode
  if ( bitRead(nesData, bB) && !bJump ) {
    bitWrite(c64Data, C64_FIRE, 1);
  }

  // C64 UP if ( NES UP is pressed ) OR ( NES B is pressed and NES B is in jump mode)
  if (bitRead(nesData, bUp) || ( bitRead(nesData, bB) && bJump )) {
    bitWrite(c64Data, C64_UP, 1);
  }

  // the rest is direct mapping
  bitWrite(c64Data, C64_DOWN, bitRead(nesData, bDown));
  bitWrite(c64Data, C64_LEFT, bitRead(nesData, bLeft));
  bitWrite(c64Data, C64_RIGHT, bitRead(nesData, bRight));

  // pins corresponding to pressed buttons will be set as outputs, rest are inputs
  DDRB = c64Data;
}
