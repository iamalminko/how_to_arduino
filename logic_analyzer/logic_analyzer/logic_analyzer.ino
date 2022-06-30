int curr_state;
int state;
unsigned long t;

#define BUFFER_SIZE 64
long timestamps[BUFFER_SIZE];
byte values[BUFFER_SIZE];
int index = 0;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1);

  // input pin to read serial
  pinMode(10, INPUT);
  state = digitalRead(10);
  //state = 0;
}

void loop() {
  int curr_state = digitalRead(10);
  if ( curr_state != state )
  {
    state = curr_state;
    t = micros();

    timestamps[index] = t;
    values[index] = state;

    if(++index > BUFFER_SIZE-1) index = 0;
  }
  if (Serial.available())
  {
    if(Serial.read() == 'G')
    {
      for(int i=0; i<index; i++)
      {      
        Serial.print(timestamps[i]);
        Serial.print(",");
        Serial.print(values[i]);
        Serial.print(";");
      }
    }
  }  
}
