# Timer Interrupt

This example demonstrates a an interrupt routine that is executed every second. In the meantime, the board can go to sleep or do some other tasks.

This example is intended for Arduino Uno.

Uno has 3 timers:
	- timer0 - 8bit (255 ticks)
	- timer1 - 16bit (65535 ticks)
	- timer2 - 8bit (255 ticks)

This example uses timer1 because timer0 and timer2 are very short and their timing can't be noticed by human eye.
Arduino Mega2560 has 5 timers (timer3, timer4 which are also 16bit).
