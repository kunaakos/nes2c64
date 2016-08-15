// http://atariage.com/forums/topic/232752-5v-to-atari-joystick-ports/
// http://www.instructables.com/id/Arduino-lets-you-play-Atari-2600-and-ZX-Spectrum-u/

#include "C64Joy.h"
#include "NesController.h"
#include "MultiFunction.h"

#define DEBUG

NesController nes(4,3,2);
C64Joy c64;

MultiFunction multiA;
MultiFunction multiB;

void wrapper_fire() {
  c64.pressFire();
  #ifdef DEBUG
  Serial.println("fire!");
  #endif
}
void wrapper_jump() {
  c64.pressUp();
  #ifdef DEBUG
  Serial.println("jump!");
  #endif
}

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  Serial.println("test start");
  #endif

  static ptr_func callbacks[] = { wrapper_fire, wrapper_jump }; // ptr_func defined in MultiFunction.h
  multiA.setFunctions( callbacks, 2 );
  multiB.setFunctions( callbacks, 2 );

  pinMode(13, OUTPUT);
}

void loop() {
  nes.read();

  // multi-function buttons
  if ( nes.buttonPressed(NES_START) ) multiA.changeFunction();
  if ( nes.buttonPressed(NES_A) ) multiA.doFunction();
  if ( nes.buttonPressed(NES_SELECT) ) multiB.changeFunction();
  if ( nes.buttonPressed(NES_B) ) multiB.doFunction();

  // the rest is direct mapping
  if ( nes.buttonPressed(NES_UP) ) c64.pressUp();
  if ( nes.buttonPressed(NES_DOWN) ) c64.pressDown();
  if ( nes.buttonPressed(NES_LEFT) ) c64.pressLeft();
  if ( nes.buttonPressed(NES_RIGHT) ) c64.pressRight();

  c64.update();
}
