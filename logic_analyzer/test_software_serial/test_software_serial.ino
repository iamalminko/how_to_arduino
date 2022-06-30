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
  mySerial.print(my_array);
  //mySerial.print("ALMINKO");
  
  delay(500);
}
