# Arduino based NES controller to C64/Atari/ZX Spectrum adapter

No resistors or other components needed!

**On some boards you might need to connect pin 0 to pin 1 with a jumper wire, or the bootloader will keep the sketch from running.**

Wire NES controller to the following arduino pins:

4 CLOCK
3 LATCH
2 DATA IN
(and hook up 5V and GND, too)

Wire controller port to arduino pins:

8 UP
9 DOWN
10 LEFT
11 RIGHT
12 FIRE
(don't forget about 5V and GND either)

Optionally connect some LEDs with resistors to pins A1 and A2.
