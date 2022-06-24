# Arduino practical examples

Here you will find various examples for advanced embedded systems developers.

## Setup steps

- Clone the repository with __git clone__ or download zip
- Open any folder
- Check for individual README.md for hardware/software dependencies
- Upload the code to your board using [Arduino IDE](https://www.arduino.cc/en/software "Download Page")

## Contents

| Folder                      | Info                                                                                                                                                                                         |
|-----------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| internal_temperature_sensor | Example usage of built-in temperature sensor in ATmega328P chip                                                                                                                              |
| low_power_delay             | Implementation of a delay that puts the board to sleep for a specified amount of time in seconds. Very useful for low-energy applications if one block of code needs to be run periodically. |
| timer_interrupt             | Interrupt routine activated by timer1 (blink LED every 1s)                                                                                                                                   |
| watchdog                    | Watchdog implementation to reset board in case of errors/infinite loops                                                                                                                              | 
