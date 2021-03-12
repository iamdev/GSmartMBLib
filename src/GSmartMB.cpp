#include "Arduino.h"
#include "SPI.h"
#include "GSmartMB.h"
#include "DateTime.h"
#include "NtpServer.h"
#define CMD_TIMEOUT   100000
#define SPI_SS        15
#define SPI_FREQ      18000000

uint8_t getCRC8(const uint8_t *data,int length);

GSmartMB::GSmartMB(uint8_t spi_ss):_spiSSPin(spi_ss)
{
}

void GSmartMB::begin(bool waitready)
{
  pinMode(_spiSSPin, OUTPUT);
  digitalWrite(_spiSSPin, HIGH);
  SPI.begin();
  SPI.beginTransaction(SPISettings(SPI_FREQ, MSBFIRST, SPI_MODE0));
  if(waitready){
    int d = 50;
    delay(d);
    while(!ready()){
      delay(d);      
      d+=50;
    }
  }
}

int GSmartMB::sendCommand(ExpCommands cmd,const uint32_t data,uint32_t *ret){  
  int n=0;
  uint8_t trx_id = micros()&0xFF;
  uint8_t _cmd[7];  
  uint32_t * pData = (uint32_t*)((uint8_t*)(_cmd+1));
  *pData = data;
  _cmd[5] = trx_id;
  while(n<5){
    GPOC = 1<<SPI_SS;
    _cmd[0] = cmd;     
    _cmd[6] = 0x3A;
    _cmd[6] = getCRC8(_cmd,7);
    //Serial.printf("cmd=%d, data=%d[0x%08X : 0x%02X,0x%02X,0x%02X,0x%02X]\n",_cmd[0],*pData,*pData, _cmd[1],_cmd[2],_cmd[3],_cmd[4]);  

    uint8_t _ret[7];
    SPI.transferBytes(_cmd,_ret,7);
    _cmd[0] = 0;
    delayMicroseconds(45);
    uint32_t t = micros();  
    bool isvalid = false;
    int m = 0;

    while(m<50){
      uint32_t _t = micros();
      SPI.transferBytes(_cmd,_ret,7);
      uint8_t trx_id_out = _ret[5];
      if(trx_id_out == trx_id){
        uint8_t crc = _ret[6];      
        _ret[6] =  0x3A;
        isvalid = (crc == getCRC8(_ret,7));      
        if(isvalid) break;
      }      
      m++;
      delayMicroseconds(25);
    }

    if(isvalid && ret!=NULL ){    
      *ret=*((uint32_t*)((uint8_t*)(_ret+1)));
      //Serial.printf("ret=%d[0x%08X : 0x%02X,0x%02X,0x%02X,0x%02X]\n",*ret,*ret,_ret[2],_ret[3],_ret[4],_ret[5]);
    }
    GPOS = 1<<SPI_SS;  
    if(isvalid) return 1;
    delayMicroseconds(50);
    n++;
  }
  #ifdef DEBUG
    err_count ++;
  #endif  
  return 0;
}

#ifdef DEBUG
int GSmartMB::errorCount(bool reset){
  int cnt = err_count;
  if(reset)err_count= 0;
  return cnt;
}
      
#endif  

void GSmartMB::loop(){

}

void GSmartMB::setTime(time_t tt){
  uint32_t ret;
  sendCommand(EXP_CMD_SET_TIME,(uint32_t)tt,&ret); 
}        
time_t GSmartMB::getTime(){
  uint32_t ret;
  sendCommand(EXP_CMD_GET_TIME,0,&ret); 
  return (time_t)ret; 
}

void GSmartMB::relayWrite(uint8_t n,uint8_t state){
  uint32_t ret;
  sendCommand(EXP_CMD_RELAY_WRITE,(n<<1)|(state?1:0),&ret); 
}
uint8_t GSmartMB::relayToggle(uint8_t n){
  uint32_t ret;
  sendCommand(EXP_CMD_RELAY_TOGGLE,n,&ret); 
  return ret?1:0;
}
uint8_t GSmartMB::relayRead(uint8_t n){
  uint32_t ret;
  sendCommand(EXP_CMD_RELAY_READ,n,&ret); 
  return ret?1:0;
}
uint8_t GSmartMB::relayState(){
  uint32_t ret;
  sendCommand(EXP_CMD_RELAY_STATE,0,&ret); 
  return ret&0x3F;
}
uint8_t GSmartMB::relayState(uint8_t state){
  uint32_t ret;
  sendCommand(EXP_CMD_RELAY_STATE,0x80|(state&0x3F),&ret);
  return ret&0x3F;
}

float GSmartMB::analogRead(uint8_t pin){
  uint32_t ret;
  sendCommand(EXP_CMD_ANALOG_READ,pin,&ret); 
  return *(float*)(&ret);
}

uint8_t GSmartMB::pinMode(uint8_t pin){
  uint32_t ret;
  sendCommand(EXP_CMD_DIGITAL_MODE,(pin<<4),&ret);
  return ret?1:0;
}

void GSmartMB::pinMode(uint8_t pin,uint8_t pwmMode){
  uint32_t ret;
  sendCommand(EXP_CMD_DIGITAL_MODE,(pin<<4)|(0x4)|(pwmMode&3),&ret);
}

void GSmartMB::digitalWrite(uint8_t pin,uint16_t state){
  uint32_t ret;
  sendCommand(EXP_CMD_DIGITAL_WRITE,(pin<<16)|(state?0:1),&ret);
}

void GSmartMB::pwmWrite(uint8_t pin,float duty){
  uint32_t ret;
  if(duty>100)duty=100;
  if(duty<0)duty=0;
  uint16_t value = (uint16_t)(duty*100);
  sendCommand(EXP_CMD_DIGITAL_WRITE,(pin<<16)|(value & 0xFFFF),&ret);
}


uint8_t GSmartMB::digitalState(){
  uint32_t ret;
  sendCommand(EXP_CMD_DIGITAL_STATE,0,&ret); 
  return ret&0xFF;
}
uint8_t GSmartMB::digitalState(uint8_t state){
  uint32_t ret;
  sendCommand(EXP_CMD_DIGITAL_STATE,0x100|(state&0xFF),&ret);
  return ret&0xFF;
}

uint16_t GSmartMB::digitalRead(uint8_t pin){
  uint32_t ret;
  sendCommand(EXP_CMD_DIGITAL_READ,pin,&ret);
  return ret?0:1;
}

uint32_t GSmartMB::pwmFrequency(uint8_t pin,uint32_t freq){
  uint32_t ret;
  sendCommand(EXP_CMD_PWM_FREQUENCY,(freq<<2)|(((pin>>2)&1)<<1)|(freq>0?1:0),&ret);
  return ret;  
}

uint16_t GSmartMB::readData(uint16_t addr){
  uint32_t ret;
  sendCommand(EXP_CMD_READ_DATA,addr<<16,&ret);
  return ret;  
}

void GSmartMB::writeData(uint16_t addr,uint16_t data){
  uint32_t ret;
  sendCommand(EXP_CMD_WRITE_DATA,(addr<<16)+data,&ret);
}
void GSmartMB::buzzerOn(){
  buzzerOn(0xFFFF);
}

void GSmartMB::buzzerOn(uint16_t ms){
  uint32_t ret;
  sendCommand(EXP_CMD_BUZZER_ON,ms,&ret);
}

void GSmartMB::buzzerOff(){
  uint32_t ret;
  sendCommand(EXP_CMD_BUZZER_OFF,0,&ret);
}

int GSmartMB::ready(void){
  uint32_t ret;
  sendCommand(EXP_CMD_READY,0,&ret);
  return (ret == 1)?1:0;
}


uint8_t getCRC8(const uint8_t *data,int length) 
{
   uint8_t crc = 0x00;
   uint8_t extract;
   uint8_t sum;
   for(int i=0;i<length;i++)
   {
      extract = *data;
      for (uint8_t tempI = 8; tempI; tempI--) 
      {
         sum = (crc ^ extract) & 0x01;
         crc >>= 1;
         if (sum)
            crc ^= 0x8C;
         extract >>= 1;
      }
      data++;
   }
   return crc;
}