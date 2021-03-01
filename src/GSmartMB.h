#ifndef _GSMART_MB_LIB_H
#define _GSMART_MB_LIB_H
#include "SimpleTask.h"

#define DEBUG

enum ExpCommands {
  EXP_CMD_NO_COMMAND       ,
  EXP_CMD_READY            ,
  EXP_CMD_RELAY_READ       ,
  EXP_CMD_RELAY_WRITE      ,
  EXP_CMD_RELAY_TOGGLE     ,
  EXP_CMD_RELAY_STATE      ,
  EXP_CMD_RELAY_WRITE_DELAY,
  EXP_CMD_TIMER_SET_SCHDULE,
  EXP_CMD_TIMER_SET_CONTROL,
  EXP_CMD_TIMER_SET_EN     ,
  EXP_CMD_TIMER_SET_REPEAT ,
  EXP_CMD_TIMER_SET_DAYS   ,
  EXP_CMD_TIMER_SET_TIME   ,
  EXP_CMD_TIMER_SET_RELAYS ,
  EXP_CMD_SW_READ          ,
  EXP_CMD_SW_STATE         ,
  EXP_CMD_DIGITAL_MODE     ,
  EXP_CMD_DIGITAL_READ     ,
  EXP_CMD_DIGITAL_WRITE    ,
  EXP_CMD_DIGITAL_STATE    ,
  EXP_CMD_PWM_FREQUENCY    ,
  EXP_CMD_ANALOG_READ      ,
  EXP_CMD_BUZZER_ON        ,
  EXP_CMD_BUZZER_OFF       ,
  EXP_CMD_GET_TIME         ,
  EXP_CMD_SET_TIME         ,
  EXP_CMD_WRITE_DATA       ,
  EXP_CMD_READ_DATA        ,
  EXP_CMD_SERIAL_BAUD      ,
  EXP_CMD_MODBUS_ID        ,
};


enum ExpIOPin{
  EXP_PIN_RL1, //0
  EXP_PIN_RL2, //1
  EXP_PIN_RL3, //2
  EXP_PIN_RL4, //3
  EXP_PIN_RL5, //4
  EXP_PIN_RL6, //5
  EXP_PIN_SW1, //6
  EXP_PIN_SW2, //7
  EXP_PIN_SW3, //8
  EXP_PIN_SW4, //9
  EXP_PIN_SW5, //10
  EXP_PIN_SW6, //11
  EXP_PIN_D0,  //12
  EXP_PIN_D1,  //13
  EXP_PIN_D2,  //14
  EXP_PIN_D3,  //15
  EXP_PIN_D4,  //16
  EXP_PIN_D5,  //17
  EXP_PIN_D6,  //18
  EXP_PIN_D7,  //19
  EXP_PIN_A1,  //20
  EXP_PIN_A2,  //21
  EXP_PIN_A3,  //22
  EXP_PIN_A4,  //23
  EXP_PIN_NA   //24
};

static const uint8_t EXP_RELAY_PINS[] = {
  EXP_PIN_RL1,
  EXP_PIN_RL2,
  EXP_PIN_RL3,
  EXP_PIN_RL4,
  EXP_PIN_RL5,
  EXP_PIN_RL6,
};

static const uint8_t EXP_SW_PINS[] = {
  EXP_PIN_SW1,
  EXP_PIN_SW2,
  EXP_PIN_SW3,
  EXP_PIN_SW4,
  EXP_PIN_SW5,
  EXP_PIN_SW6,
};

static const uint8_t EXP_DIGITAL_PINS[] = {
  EXP_PIN_D0,
  EXP_PIN_D1,
  EXP_PIN_D2,
  EXP_PIN_D3,
};

static const uint8_t EXP_ANALOG_PINS[] = {
  EXP_PIN_A1,
  EXP_PIN_A2,
  EXP_PIN_A3,  
  EXP_PIN_A4,
};

#define DIGITAL_IO_MODE_INPUT           0
#define DIGITAL_IO_MODE_OUTPUT          1
#define DIGITAL_IO_MODE_PWM             2
#define DIGITAL_IO_MODE_INPUT_FLOATING  3


#define RELAY1_STATE_ON   0x01
#define RELAY2_STATE_ON   0x02
#define RELAY3_STATE_ON   0x04
#define RELAY4_STATE_ON   0x08
#define RELAY5_STATE_ON   0x10
#define RELAY6_STATE_ON   0x20


class GSmartMB{
    public:
        GSmartMB(uint8_t spi_ss=15);
        void begin(bool waitready=false);
        int sendCommand(ExpCommands cmd,const uint32_t data=0,uint32_t *ret = NULL);
        void loop();      
        void setTime(time_t tt);        
        time_t getTime();        
        void relayWrite(uint8_t n,uint8_t state);
        uint8_t relayToggle(uint8_t n);
        uint8_t relayRead(uint8_t n);
        uint8_t relayState(uint8_t state);
        uint8_t relayState();
        float analogRead(uint8_t pin);   
        uint32_t pwmFrequency(uint8_t pin,uint32_t freq=0);        
        uint8_t pinMode(uint8_t pin);
        void pinMode(uint8_t pin,uint8_t mode);
        void digitalWrite(uint8_t pin,uint16_t state);
        void pwmWrite(uint8_t pin,float duty);
        uint8_t digitalState(uint8_t state);
        uint8_t digitalState();
        uint16_t digitalRead(uint8_t pin);    
        void buzzerOn(uint16_t ms);
        void buzzerOn();
        void buzzerOff();
        uint16_t readData(uint16_t addr);
        void writeData(uint16_t addr,uint16_t data);
        int ready(void);
#ifdef DEBUG
        int errorCount(bool reset=true);        
#endif  
    private :    
        uint8_t _spiSSPin;
#ifdef DEBUG
        int err_count=0;
#endif  
};
#endif

