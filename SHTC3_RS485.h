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
    /**
     * @brief Construct a new shtc3 rs485 object
     * 
     */
    SHTC3_RS485();

    /**
     * @brief Destroy the shtc3 rs485 object
     * 
     */
    virtual ~SHTC3_RS485(){}

    /**
     * @brief Construct a new shtc3 rs485 object
     * 
     * @param serial 
     */
    SHTC3_RS485(HardwareSerial * serial);

    /**
     * @brief Construct a new shtc3 rs485 object
     * 
     * @param serial 
     */
    SHTC3_RS485(SoftwareSerial * serial);

    SHTC3_RS485(int rxPin, int txPin);
    
    /**
     * @brief 
     * 
     */
    void begin();

    /**
     * @brief Set the Timeout object
     * 
     * @param _ui_timeOut 
     */
    void setTimeout(unsigned int _ui_timeOut);

    /**
     * @brief Get the Data object
     * 
     * @return SHTC3_RS485_info 
     */
    SHTC3_RS485_info getData();

    /**
     * @brief 
     * 
     * @param buf 
     * @param len 
     * @return uint16_t 
     */
    uint16_t ModRTU_CRC(byte * buf, int len);

    /**
     * @brief Get the Address object
     * 
     * @return uint8_t 
     */
    uint8_t getAddress();

    /**
     * @brief Set the Address object
     * 
     * @param fromAddr_ 
     * @param toAddr_ 
     * @return true 
     * @return false 
     */
    bool setAddress(uint8_t fromAddr_, uint8_t toAddr_);

    /**
     * @brief Get the Data object
     * 
     * @param address_ 
     * @return SHTC3_RS485_info 
     */
    SHTC3_RS485_info getData(uint8_t address_);
    
};

#endif
