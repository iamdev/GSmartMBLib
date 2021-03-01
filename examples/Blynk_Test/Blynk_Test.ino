
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

NtpServer ntp;
bool isSync = false;

void task_update_relay();
void task_update_digital_state();
void task_update_analog();
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
  ntp.begin();
  WiFi.begin(wifi_ssid, wifi_pass);
  Blynk.config(blynk_auth,blynk_server,blynk_port);
  Task.create(task_update_relay,20);
  Task.create(task_update_digital_state,20);
  Task.create(task_update_analog,100);
  Task.create([]{
    DateTime dt = DateTime(mb.getTime());
    Serial.printf("%02u/%02u/%04u %02u:%02u:%02u\n",dt.day,dt.month,dt.year,dt.hour,dt.minute,dt.second);
  },1000);
}

void loop()
{
  uint32_t ms = millis();
  if(WiFi.status() == WL_CONNECTED){
    Blynk.run();
  }
  if(!isSync && WiFi.status() == WL_CONNECTED){
    Serial.println("Starting get time from server...");        
    time_t tt = ntp.getTime(); 
    DateTime dt = DateTime(tt);
    if(dt.year>=2020){
        Serial.printf("Server Time : %02u/%02u/%04u %02u:%02u:%02u\n",dt.day,dt.month,dt.year,dt.hour,dt.minute,dt.second);
        mb.setTime(tt);    
        isSync = true;
        Serial.println("Sync server time success!");
    }else{
        Serial.println("Failed to get time from server");
    }
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
      Blynk.virtualWrite(V7+i,s?0:255);
      _state[i] = s;
    }    
  }
  
}

void task_update_analog(){
  static float _analogs[4] = {-1,-1,-1,-1};
  for(int i=0;i<4;i++){
    float a = mb.analogRead(i);
    if(abs(a-_analogs[i])>0.01){
      Serial.printf("Analog A0 : %.2f\n",a);
      Blynk.virtualWrite(V11+i,a);
      _analogs[i] = a;
    }    
  }  
}

BLYNK_WRITE(V15){ 
  if(param.asInt())
    mb.buzzerOn();
  else 
    mb.buzzerOff();
}