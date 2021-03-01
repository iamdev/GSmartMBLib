
#define BLYNK_MSG_LIMIT 250
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <GSmartMBLib.h>
GSmartMB mb;

char blynk_server[] = "blynk-cloud.com";
int blynk_port = 80;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char blynk_auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char wifi_ssid[] = "YourNetworkName";
char wifi_pass[] = "YourPassword";


void task_update_relay();
void task_update_digital_state();

void setup()
{
  Serial.begin(115200);
  Serial.print("\nInitializing...");
  mb.begin(true);
  Serial.println("Done.");
  mb.pinMode(0,DIGITAL_IO_MODE_INPUT);
  mb.pinMode(1,DIGITAL_IO_MODE_INPUT);
  mb.pinMode(2,DIGITAL_IO_MODE_INPUT);
  mb.pinMode(3,DIGITAL_IO_MODE_INPUT);
  WiFi.begin(wifi_ssid, wifi_pass);
  Blynk.config(blynk_auth,blynk_server,blynk_port);
  Task.create(task_update_relay,20);
  Task.create(task_update_digital_state,20);
}

void loop()
{
  uint32_t ms = millis();
  if(WiFi.status() == WL_CONNECTED){
    Blynk.run();
  }
  Task.loop();
}
#define BLYNK_WRITE_RELAY(n) BLYNK_WRITE(V##n){ \
  mb.relayWrite(n,param.asInt());\
}

BLYNK_WRITE_RELAY(1);
BLYNK_WRITE_RELAY(2);
BLYNK_WRITE_RELAY(3);
BLYNK_WRITE_RELAY(4);
BLYNK_WRITE_RELAY(5);
BLYNK_WRITE_RELAY(6);

void task_update_relay(){    
  static uint8_t _state[6];
  uint8_t state = mb.relayState();  
  for(int i=0;i<6;i++){
    uint8_t s = (state&(1<<i))?1:0;
    if(s!=_state[i]){
      Blynk.virtualWrite(V1+i,s);
      _state[i] = s;
    }    
  }
}
void task_update_digital_state(){    
  static uint8_t _state[4];
  uint8_t state = mb.digitalState();  
  for(int i=0;i<4;i++){
    uint8_t s = (state&(1<<i))?1:0;
    if(s!=_state[i]){
      Blynk.virtualWrite(V7+i,s);
      _state[i] = s;
    }    
  }
}