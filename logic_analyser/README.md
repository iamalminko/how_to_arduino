# Logic Analyser

In this folder you can find implementation of logic analyser for Arduino.

## Info

The application reads changes on a set digital pin and stores every change in 
a buffer along with a timestamp in microseconds.

The applications listens on serial port. If 'G' is sent it will send the
buffer through serial port.

Python script "logic_analyser.py" is doing exactly this and plotting
the received array.

You can run "test_..." applications on another arduino to test for different protocols
and combinations of byte streams. Just make sure you connect the correct output pin
from test device, using a jumper, to the correct input pin on the logic_analyser device
(pin 10 by default).

## Serial communication

Upload "logic_analyser.ino" to one board and "test_software_serial.ino" to another.
Connect pin10 and pin11 respectively.

Set the test device so that it constantly sends "my_array" every 500mS by uncommenting 
"mySerial.print(my_array);".

On your host/desktop machine run "python logic_analyser.py" in the "logic_analyser" 
directory.

You should get a plot like this:

![Serial comm output](../resources/serial_plot_my_array.jpg?raw=true "Serial plot: my_array")


## Service Info

```
Sketch uses 2518 bytes (7%) of program storage space. Maximum is 32256 bytes.
Global variables use 512 bytes (25%) of dynamic memory, leaving 1536 bytes for local variables. Maximum is 2048 bytes.
```