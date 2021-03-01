#include <GSmartMBLib.h>
GSmartMB mb;
void setup() {
  Serial.begin(115200);
  Serial.print("\nInitializing...");
  mb.begin(true);  
  Serial.println("Done.");  
}
float a0 = 0;
void loop() {
  float _a0 = mb.analogRead(0);
  if(abs(_a0-a0)>0.01){
    a0 = _a0;
    Serial.printf("Analog A0 : %.2f\n",a0);
  }
  delay(100);
}