/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
  Based on Bounce2 Main by Thomas O Fredericks (tof@t-o-f.info)
	https://github.com/thomasfredericks/Bounce2/
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SOFTBOUNCE_H
#define SOFTBOUNCE_H

// #include <Arduino.h>

class SoftBounce
{
	public:
		SoftBounce();

    // Sets the debounce interval
    void interval(uint16_t interval_millis);

    // Updates the pin
    bool update(bool currentState);

    // Returns the updated pin state
    bool high();

    // Returns the falling pin state
    bool fell();

    // Returns the rising pin state
    bool rose();

	private:
		unsigned long previous_millis;
    uint16_t interval_millis;
    uint8_t state;
};

#endif
