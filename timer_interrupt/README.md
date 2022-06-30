# Timer Interrupt

This example demonstrates a an interrupt routine that is executed every second. In the meantime, the board can go to sleep or do some other tasks.

## Info

This example is intended for Arduino Uno.

Uno has 3 timers:
* timer0 - 8bit (255 ticks)
* timer1 - 16bit (65535 ticks)
* timer2 - 8bit (255 ticks)

Internally, timer0 is used for the millis() function. It is not recommended to use it.
Timer1 and Timer2 are available for custom applications.
This example uses timer1 because timer2 is very short and its full cycle can't be noticed by the human eye.
Arduino Mega2560 has a total of 5 timers (timer3, timer4 which are 16bit).

## Service Info

```
Sketch uses 884 bytes (2%) of program storage space.
Global variables use 10 bytes (0%) of dynamic memory, leaving 2038 bytes for local variables.
```