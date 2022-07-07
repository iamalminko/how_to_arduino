# Logic Analyzer

In this folder you can find implementation of logic analyzer for Arduino.

## Info

The application reads changes on a set digital pin and stores every change in a buffer along with a timestamp in microseconds. The applications listens on serial port. If `'G'` is sent it will send the buffer through serial port. Python script `logic_analyzer.py` is doing exactly this and plotting the received array. You can run `test_<?>.ino` applications on another arduino to test for different protocols and combinations of byte streams. Just make sure you connect the correct output pin from test device, using a jumper, to the correct input pin on the logic_analyzer device (pin 10 by default).

## Serial communication

Upload `logic_analyzer.ino` to one board and `test_software_serial.ino` to another. sConnect pin10 and pin11 respectively. Set the test device so that it constantly sends `my_array` every 500mS by uncommenting `mySerial.print(my_array);`. On your host/desktop machine run `python logic_analyzer.py` in the `logic_analyzer` directory.

You should get a plot like this:

![Serial comm output](https://raw.githubusercontent.com/iamalminko/how_to_arduino/master/resources/serial_plot_my_array.png "Serial plot: my_array")

Signal high in this setup is idle. The signal initially performs a HI/LO transition, followed by a high(0, green) start bit. After this we have 4 bytes transmitted. After each one, we have a stop(1,LO, red) bit then a start(0, HI, green) bit that signals to the other device beginning of transmission. Keep in mind that serial sends LSB first. That means that individual bytes are read from right to left (the bits are inverted on the plot). This plot has been recorded while sending bytes from test device with 9600baud rate. It took 4mS to receive 4 bytes which is as it should be (1.04mS per byte).

Let's take a look at what happens if we send a string "ALMINKO" (9600baud):

![Sending string "ALMINKO"](https://raw.githubusercontent.com/iamalminko/how_to_arduino/master/resources/serial_plot_alminko.png "Sending a string")

The plot above looks a bit too tedious to verify manually. We can uncomment code in `logic_analyzer.py`:

```
# A/D conversion
A_D_conversion(x, y)
```

This will print us a stream of 0's and 1's. For the string "ALMINKO" we will get the following sequence:

```
010000010100011001010101100101010010010100111001010110100101011110010

# Split the stream into bytes and start/stop bits:
0 10000010 10 00110010 10 10110010 10 10010010 10 01110010 10 11010010 10 11110010

# Individual bytes (from left to right), when inverted:
# byte # ASCII symbol
01000001 # A
01001100 # L
01001101 # M
01001001 # I
01001110 # N
01001011 # K
01001111 # O
```


## Service Info

```
Sketch uses 2518 bytes (7%) of program storage space. Maximum is 32256 bytes.
Global variables use 512 bytes (25%) of dynamic memory, leaving 1536 bytes for local variables. Maximum is 2048 bytes.
```

We can safely go up to 38400baud rate. Be cautious if you go with higher baud rates. For example at 115200baud rate, the communication is so fast that Arduino digitalRead can't capture every change, hence you will get garbage output. This example uses `SoftwareSerial.h.` Of course you can use the built-in `Serial` pins but I noticed that there is interference when the TX pin should be idle. Arduino will restart every time we connect to it through serial. That is why we have to leave enough delay for the board to start and fill the buffer. If you need better performance, check out logic_analyzer_lite folder.