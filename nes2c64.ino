#include "C64Joy.h"
#include "NesController.h"
#include "MultiFunction.h"
#include "SoftBounce.h"

NesController nes(4,3,2);
C64Joy c64;

SoftBounce startDebounced;
SoftBounce selectDebounced;

MultiFunction multiA;
MultiFunction multiB;

void wrapper_fire() {
  c64.pressFire();
}

void wrapper_jump() {
  c64.pressUp();
}

void wrapper_autofire() {
  static uint16_t lastTriggeredMs;
  static uint16_t currentMs;
  static uint16_t lastStateChangeMs;
  static uint16_t stateDurationMs = 50;
  static bool state;

  currentMs = millis();

  if (currentMs - lastTriggeredMs >= stateDurationMs / 5) {
    state = HIGH;
    lastStateChangeMs = currentMs;
  } else if (currentMs - lastStateChangeMs >= stateDurationMs) {
    state = !state;
    lastStateChangeMs = currentMs;
  }

  lastTriggeredMs = currentMs;

  if ( state ) c64.pressFire();
}

void setup() {
  // set the list of functions for "programmable" buttons
  static ptr_func callbacks[] = { wrapper_fire, wrapper_jump, wrapper_autofire }; // ptr_func defined in MultiFunction.h
  multiA.setFunctions( callbacks, 3 );
  multiB.setFunctions( callbacks, 3 );
}

void loop() {

  // NES in
  nes.read();

  // START and SELECT buttons are debounced, used as function select for "programmable" buttons
  startDebounced.update( nes.buttonPressed(NES_START) );
  selectDebounced.update( nes.buttonPressed(NES_SELECT) );

  // change "programmable" button functions when function select buttons are pressed
  if ( startDebounced.rose() ) multiA.changeFunction();
  if ( selectDebounced.rose() ) multiB.changeFunction();

  // A and B are "programmable"
  if ( nes.buttonPressed(NES_A) ) multiA.doFunction();
  if ( nes.buttonPressed(NES_B) ) multiB.doFunction();

  // the rest is direct mapping from NES to c64 buttons
  if ( nes.buttonPressed(NES_UP) ) c64.pressUp();
  if ( nes.buttonPressed(NES_DOWN) ) c64.pressDown();
  if ( nes.buttonPressed(NES_LEFT) ) c64.pressLeft();
  if ( nes.buttonPressed(NES_RIGHT) ) c64.pressRight();

  // c64 out
  c64.update();

}
