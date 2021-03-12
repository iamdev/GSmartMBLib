//Example : Invert logic D0 and D1

#include <GSmartMBLib.h>
GSmartMB mb;
#define DHT_PIN D0
float temp;
float humi;
int readTemperature();
void taskCheckInput();
void setup() {
  Serial.begin(115200);
  Serial.print("\nInitializing...");
  mb.begin(true);
  Serial.println("Done.");
  mb.pinMode(0,DIGITAL_IO_MODE_INPUT);
  mb.pinMode(1,DIGITAL_IO_MODE_OUTPUT);
  Task.create(taskCheckInput,10);
}

void loop() { 
  Task.loop();  
}

void taskCheckInput(){
  static int _state = 0;
  int state = mb.digitalRead(0);
  if(state!=_state){
    _state = state;
    mb.digitalWrite(1, state?0:1);
  }
}