/*
  Low power delay for periodical task

  This example uses LowPower files from Rocket Scream.

  In the defines, WAIT_DURATION is set in seconds for the amount
  the arduino will sleep between task executions.

  You can insert code in the loop() in the "user code" section or just call your
  own function from here.

  The circuit:
  - Uses the onboard LED.
  - Note: Most Arduinos have an on-board LED you can control. On the UNO, MEGA
    and ZERO it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN
    is set to the correct LED pin independent of which board is used.
    If you want to know what pin the on-board LED is connected to on your
    Arduino model, check the Technical Specs of your board at:
    https://www.arduino.cc/en/Main/Products

  created 2022
  by Alminko Kasibovic

  This example code is in the public domain.

  https://github.com/iamalminko/how_to_arduino
*/

// includes
#include "LowPower.h"

// defines
#define WAIT_DURATION 12*1    // sleep period between task executions in seconds
#define DURATION_8S 9.3       // duration of 8S sleep (SHOULD BE MANUALLY ADJUSTED)
#define DURATION_500MS 0.562  // duration of 500MS sleep (SHOULD BE MANUALLY ADJUSTED)

// global variabless
boolean toggle = 0;

// functions
void toggle_led();
void system_sleep(int seconds);

void setup()
{
  // set built-in led pin as output
  pinMode(13, OUTPUT);
}

void loop()
{
  // Here goes your code to be executed periodically
  toggle_led();

  // End of user code section
   
  system_sleep(WAIT_DURATION);
}

// function that is executed periodically
void toggle_led()
{
  if (toggle)
  {
    digitalWrite(13,HIGH);
    toggle = 0;
  }
  else
  {
    digitalWrite(13,LOW);
    toggle = 1;
  }
}

/*
  Delay function.
  
  Values should be adjusted for your board.
  1s mismatch results in 86400/8 = 10800s in just one day (that's 3hrs).
  
  Instructions to adjust periods:
  Put LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); in the void loop()
  and measure with your phone's stopwatch what is the actual period of
  a built-in diode blinking. 
  
  You can start the stopwatch and count a few cycles (the more the better)
  and then just divide the time passed with the count of cycles. 
  That way you reduce the measuring error.
*/
void system_sleep(int seconds)
{
  // transfer seconds to float for better precision
  float sec = seconds;

  // in case you need better precision, add more while loops with:
  // SLEEP_15MS - 15 ms sleep
  // SLEEP_30MS - 30 ms sleep
  // SLEEP_60MS - 60 ms sleep
  // SLEEP_120MS - 120 ms sleep
  // SLEEP_250MS - 250 ms sleep
  // SLEEP_500MS - 500 ms sleep
  // SLEEP_1S - 1 s sleep
  // SLEEP_2S - 2 s sleep
  // SLEEP_4S - 4 s sleep
  // SLEEP_8S - 8 s sleep
  // see LowPower.cpp (123)
  while(sec > DURATION_8S)
  {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    sec -= DURATION_8S;
  }
  while(sec > DURATION_500MS)
  {
    LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
    sec -= DURATION_500MS;
  }
}
