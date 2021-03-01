#include <GSmartMBLib.h>
GSmartMB mb;
void setup() {
  Serial.begin(115200);
  Serial.print("\nInitializing...");
  mb.begin(true);  
  Serial.println("Done.");  
  mb.pinMode(0,DIGITAL_IO_MODE_PWM);//Setup I/O mode for D0 to PWM Output
  mb.pwmFrequency(0,20000);//Set frequency (CH1) to 20.0KHz
  mb.pwmWrite(0,40); //Set duty+ to 40.0%
}

void loop() {
}