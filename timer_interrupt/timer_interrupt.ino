/*
  Timer activated interrupt

  timer1 activates interrupt function ISR(TIMER1_COMPA_vect) every 1s.
  
  timer1 is has 16bit counter and since Arduino Uno has a 16MHz clock,
  that means that 15624 ticks are 1s.

  Maximum time that we can wait is 65535 ticks, which converts for Arduino Uno
  to 4.19s. In case you need longer intervals, you can define global counter
  variable and implement some logic in ISR(TIMER1_COMPA_vect) function to
  work for your benefit.

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

// global variables
boolean toggle = 0;

void setup()
{
  // set built-in led pin as output
  pinMode(13, OUTPUT);

  cli(); // stop all interrupts

  //set timer1 interrupt at 1Hz
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624; // = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei(); //allow interrupts
}

// interrupt routine
// timer1 interrupt 1Hz toggles pin 13 (LED)
ISR(TIMER1_COMPA_vect){
  // this interrupt is invoked every 1s (1Hz) and it toggles LED
  if (toggle){
    digitalWrite(13,HIGH);
    toggle = 0;
  }
  else{
    digitalWrite(13,LOW);
    toggle = 1;
  }
}

void loop(){
  // do some other things in parallel here
}
