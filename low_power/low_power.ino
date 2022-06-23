#include "LowPower.h"

// Sleep period in seconds
#define CYCLE_TIME 15*1

boolean toggle = 0;

void toggle_led();
void system_sleep(int seconds);

void setup(){
  pinMode(13, OUTPUT);
}

void loop(){
  toggle_led();

  /* Here goes your code to be executed periodically */

  
  /* _______________________________________________ */
   
  LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
  //system_sleep(CYCLE_TIME);
}

void toggle_led()
{
  if (toggle){
    digitalWrite(13,HIGH);
    toggle = 0;
  }
  else{
    digitalWrite(13,LOW);
    toggle = 1;
  }
}

/*  This is the delay function.
    Values should be adjusted for your board.
    1s mismatch results in 86400/8 = 10800s in just one day (that's 3hrs).
    
    Instructions to adjust periods:
    Put LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); in the void loop()
    and measure with your phone's stopwatch what is the actual period of
    a built-in diode blinking. 
    
    You can start the stopwatch and count a few cycles (the more the better)
    and then just divide the time passed with the count of cycles. 
    That way you reduce the measuring error.*/
void system_sleep(int seconds)
{
  float sec = seconds;
  while(sec > 9.3)
  {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    sec -= 9.3;
  }
  while(sec > 0.6)
  {
    LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
    sec -= 0.6;
  }
}
