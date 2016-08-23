#ifndef SOFTCLOCK_H
#define SOFTCLOCK_H

// #include <Arduino.h>

class SoftClock
{
	public:
		SoftClock();

    void setPeriod(uint16_t _period);
    void update();
		void reset();
		void get();

	private:
		uint16_t lastTransition;
    uint16_t period;
    uint8_t state;
};

#endif
