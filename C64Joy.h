#ifndef C64JOY_H
#define C64JOY_H

#include <Arduino.h>

#define C64_UP 0
#define C64_DOWN 1
#define C64_LEFT 2
#define C64_RIGHT 3
#define C64_FIRE 4

class C64Joy
{
	public:
		C64Joy();
		void pressUp();
		void pressDown();
		void pressLeft();
		void pressRight();
		void pressFire();
		void update();
	private:
		// 8 bits: ___FRLDU
		byte controllerData;
};

#endif
