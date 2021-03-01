#include <GSmartMBLib.h>
GSmartMB mb;
#define DHT_PIN D0
float temp;
float humi;
int readTemperature();
void setup() {
  Serial.begin(115200);
  Serial.print("\nInitializing...");
  mb.begin(true);  
  Serial.println("Done.");    
}
void loop() {
  if(readTemperature()){
      Serial.printf("Temperature : %.2f°C, Humidity: %.1f%\n",temp,humi);
  }
  delay(1000);
}



uint32_t wait_signal(int pin,int signal,uint32_t timeout){
  uint32_t us = micros();  
  delayMicroseconds(5);
  while(micros()<(us+timeout) && digitalRead(signal) != signal) delayMicroseconds(5);
  return micros()-us;
}

int readTemperature(){
  byte data[5];
  pinMode(DHT_PIN,OUTPUT);  
  digitalWrite(DHT_PIN,LOW);
  delayMicroseconds(500);
  digitalWrite(DHT_PIN,HIGH);
  delayMicroseconds(5);
  pinMode(DHT_PIN, INPUT_PULLUP);
  uint32_t us = wait_signal(DHT_PIN, HIGH, 100);
  if(us<80){
    Serial.printf("Response signal in %u us.\n",us);
  }
  return 0;
}

