#ifndef _HSHOP_VN_H_PZEM004T_V2_H__
#define _HSHOP_VN_H_PZEM004T_V2_H__

#include "arduino.h"
#include "SHTC3_RS485_define.h"
#include "SoftwareSerial.h"

enum {
  SHT30_RS485_HARD_SERIAL,
  SHT30_RS485_SOFT_SERIAL
};

#define writeToSerial(...)      { port->write(__VA_ARGS__); }

//#define EN_DEBUG_SHTC3_RS485

#if defined(EN_DEBUG_SHTC3_RS485)
  #define debug                   Serial
  #define DB(...)                 debug.print(__VA_ARGS__);
  #define DB_LN(...)              debug.println(__VA_ARGS__);
#else
  #define debug                   Serial
  #define DB(...)                 
  #define DB_LN(...)              
#endif

extern byte getValue_para_SHTC3_RS485[8];
extern byte resetEnergy_para[4];

class SHTC3_RS485{
  private:
    uint8_t typeSerial;
    Stream * port;
    unsigned int ui_timeOut;
    void begin(unsigned long _tembaud);
    
  public:
     SHTC3_RS485();

    virtual ~SHTC3_RS485(){}

    SHTC3_RS485(HardwareSerial * serial);

    SHTC3_RS485(SoftwareSerial * serial);

    SHTC3_RS485(int rxPin, int txPin);
    
    void begin();

    void setTimeout(unsigned int _ui_timeOut);

    SHTC3_RS485_info getData();
};

#endif
