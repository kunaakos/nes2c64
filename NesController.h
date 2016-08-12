#ifndef NESCONTROLLER_H
#define NESCONTROLLER_H

#include <Arduino.h>

#define NES_A 7
#define NES_B 6
#define NES_START 4
#define NES_SELECT 5
#define NES_UP 3
#define NES_DOWN 2
#define NES_LEFT 1
#define NES_RIGHT 0

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
