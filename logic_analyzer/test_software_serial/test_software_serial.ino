#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup()
{
  mySerial.begin(115200);
}

char my_array[4] = {
  B10100100,
  B01010101,
  B01110000,
  B01101000,
  };
void loop()
{
  //mySerial.print(B10100100); // sending one byte doesn't work well
  mySerial.print(my_array); // gives a mistake in 5th bit of 1st byte, missing parity
  //mySerial.print("ALMINKO"); // works as expected
  
  delay(500);
}
