#include <Arduino.h>
#include "C64Joy.h"

C64Joy::C64Joy()
{
	// pins are set as inputs to emulate open collector outputs
	DDRB = B00000000;
	// set low
	PORTB = B00000000;
}

void C64Joy::pressUp() {
	bitWrite(controllerData, C64_UP , 1);
}

void C64Joy::pressDown() {
	bitWrite(controllerData, C64_DOWN , 1);
}

void C64Joy::pressLeft() {
	bitWrite(controllerData, C64_LEFT , 1);
}

void C64Joy::pressRight() {
	bitWrite(controllerData, C64_RIGHT , 1);
}

void C64Joy::pressFire() {
	bitWrite(controllerData, C64_FIRE , 1);
}


void C64Joy::update() {
	// pins corresponding to pressed buttons will be set as outputs, rest are inputs
  DDRB = controllerData;
	controllerData = 0;
}
