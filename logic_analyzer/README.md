# Logic Analyzer

In this folder you can find implementation of logic analyzer for Arduino.

## Info

The application reads changes on a set digital pin and stores every change in a buffer along with a timestamp in microseconds.

The applications listens on serial port. If 'G' is sent it will send the buffer through serial port.

Python script "logic_analyzer.py" is doing exactly this and plotting the received array.

You can run "test_..." applications on another arduino to test for different protocols and combinations of byte streams. Just make sure you connect the correct output pin from test device, using a jumper, to the correct input pin on the logic_analyzer device (pin 10 by default).

## Serial communication

Upload "logic_analyzer.ino" to one board and "test_software_serial.ino" to another. sConnect pin10 and pin11 respectively.

Set the test device so that it constantly sends "my_array" every 500mS by uncommenting "mySerial.print(my_array);".

On your host/desktop machine run "python logic_analyzer.py" in the "logic_analyzer" directory.

You should get a plot like this:

![Serial comm output](https://raw.githubusercontent.com/iamalminko/how_to_arduino/master/resources/serial_plot_my_array.png "Serial plot: my_array")


## Service Info

```
Sketch uses 2518 bytes (7%) of program storage space. Maximum is 32256 bytes.
Global variables use 512 bytes (25%) of dynamic memory, leaving 1536 bytes for local variables. Maximum is 2048 bytes.
```