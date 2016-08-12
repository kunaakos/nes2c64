// http://atariage.com/forums/topic/232752-5v-to-atari-joystick-ports/
// http://www.instructables.com/id/Arduino-lets-you-play-Atari-2600-and-ZX-Spectrum-u/

#include "C64Joy.h"
#include "NesController.h"

NesController nes(4,3,2);
C64Joy c64;

void setup() {

}

void loop() {
  nes.read();

  // the rest is direct mapping
  if ( nes.buttonPressed(NES_A) ) c64.pressFire();
  if ( nes.buttonPressed(NES_UP) ) c64.pressUp();
  if ( nes.buttonPressed(NES_DOWN) ) c64.pressDown();
  if ( nes.buttonPressed(NES_LEFT) ) c64.pressLeft();
  if ( nes.buttonPressed(NES_RIGHT) ) c64.pressRight();

  c64.update();
}
