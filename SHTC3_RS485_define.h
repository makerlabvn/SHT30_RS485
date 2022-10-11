#ifndef HSHOP_VN_H_PZEM004T_V2_DEFINE_H_
#define HSHOP_VN_H_PZEM004T_V2_DEFINE_H_

#include "arduino.h"

#define SHT3C_RS485_SCALE               (0.1)

#define MAX_PZEM_TIMEOUT      (20000) //ms
#define MIN_PZEM_TIMEOUT      (100) //ms

#define SHT3C_RS485_CONVERT(low,high)        (((high<<8) + low) * SHT3C_RS485_SCALE)
#define SHT3C_RS485_GET_VALUE(unit)       (float)(SHT3C_RS485_CONVERT(myBuf[_##unit##_L__], myBuf[_##unit##_H__]))

enum{
  _SHT3C_RS485_address__ = 0,
  _SHT3C_RS485_funnctionCode__,
  _SHT3C_RS485_numOfByteValid__,
  _humidity_H__,
  _humidity_L__,
  _temperature_H__,
  _temperature_L__,
  _crc_H__,
  _crc_L__,
  RESPONSE_SIZE
};

typedef struct SHTC3_RS485_info{
  float temperature;
  float humidity;
};

#endif
