#include <Arduino.h>
#include "NesController.h"

NesController::NesController(uint8_t clock, uint8_t latch, uint8_t datin)
{
	_clock = clock;
	_latch = latch;
	_datin = datin;

	pinMode(_latch,OUTPUT);
	pinMode(_clock,OUTPUT);
	pinMode(_datin,INPUT);

	digitalWrite(_latch,HIGH);
	digitalWrite(_clock,HIGH);
	digitalWrite(_latch,LOW);
	digitalWrite(_clock,LOW);
}

uint8_t NesController::read() {

	controller_data = 0;

	digitalWrite(_latch,HIGH);
	delayMicroseconds(2);
	digitalWrite(_latch,LOW);

	controller_data = digitalRead(_datin);

	for (int i = 1; i <= 7; i ++) {
		digitalWrite(_clock,HIGH);
		delayMicroseconds(2);
		controller_data = controller_data << 1;
		controller_data = controller_data + digitalRead(_datin) ;
		delayMicroseconds(4);
		digitalWrite(_clock,LOW);
	}

	controller_data = ~controller_data;

	return(controller_data);
}

boolean NesController::buttonPressed(uint8_t butt){
	return(bitRead(controller_data,butt));
};
