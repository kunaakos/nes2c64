#ifndef NESCONTROLLER_H
#define NESCONTROLLER_H

#include <Arduino.h>

#define bA 7
#define bB 6
#define bStart 4
#define bSelect 5
#define bUp 3
#define bDown 2
#define bLeft 1
#define bRight 0

class NesController
{
	public:
		NesController(byte clock, byte latch, byte datin);
		byte read();
		boolean buttonPressed(byte butt);

	private:
		byte controller_data;
		byte _clock;
		byte _latch;
		byte _datin;
};

#endif
