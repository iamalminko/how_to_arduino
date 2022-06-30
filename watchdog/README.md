# Watchdog

This example demonstrates how to use the ATmega328 watchdog.

## Info

The application uses LowPower files (LowPower.cpp and LowPower.h, combined size 41KB) provided by Rocket Scream https://github.com/rocketscream/Low-Power

## Warning

Be cautious with the reset functionality as you can brick your board if you flash the code that resets the board too often.
Make sure that the board doesn't reset at least for some time on power up (that way you can definitely flash some other code later).

## Service Info

```
Sketch uses 4266 bytes (13%) of program storage space. Maximum is 32256 bytes.
Global variables use 201 bytes (9%) of dynamic memory, leaving 1847 bytes for local variables. Maximum is 2048 bytes.
```