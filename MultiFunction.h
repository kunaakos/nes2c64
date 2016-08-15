#ifndef MULTIFUNCTION_H
#define MULTIFUNCTION_H

#include <Arduino.h>

typedef void (*ptr_func) (void);

class MultiFunction
{
	public:
		MultiFunction();
		void changeFunction();
		void doFunction();
		void setFunctions( ptr_func _callbacks[], uint8_t _nrOfFunctions );
	private:
		uint8_t currentFunction = 0;
		uint8_t nrOfFunctions = 0;
		ptr_func *callbacks;
};

#endif
