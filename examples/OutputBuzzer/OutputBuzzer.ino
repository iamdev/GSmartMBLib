#include <GSmartMBLib.h>
GSmartMB mb;
void setup() {
  Serial.begin(115200);
  Serial.print("\nInitializing...");
  mb.begin(true);  
  Serial.println("Done.");  
  mb.buzzerOn();
  delay(1000);
  mb.buzzerOff();
  delay(1000);
  mb.buzzerOn(500); //Auto off after 500ms.
}

void loop() {
}