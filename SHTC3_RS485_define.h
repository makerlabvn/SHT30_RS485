#ifndef HSHOP_VN_H_PZEM004T_V2_DEFINE_H_
#define HSHOP_VN_H_PZEM004T_V2_DEFINE_H_

#include "arduino.h"

#define SHT3C_RS485_SCALE               (0.1)

#define MAX_PZEM_TIMEOUT      (20000) //ms
#define MIN_PZEM_TIMEOUT      (100) //ms

#define SHT3C_RS485_CONVERT(low,high)        (((high<<8) + low) * SHT3C_RS485_SCALE)
#define SHT3C_RS485_GET_VALUE(unit)       (float)(SHT3C_RS485_CONVERT(myBuf[_SHT3C_RS485_##unit##_L__], myBuf[_SHT3C_RS485_##unit##_H__]))

#define _SHT3C_RS485_RESPONSE_SIZE_GETADDR    7
#define _SHT3C_RS485_RESPONSE_SIZE_SETADDR    8

enum{
  _SHT3C_RS485_address__ = 0,
  _SHT3C_RS485_funnctionCode__,
  _SHT3C_RS485_numOfByteValid__,
  _SHT3C_RS485_humidity_H__,
  _SHT3C_RS485_humidity_L__,
  _SHT3C_RS485_temperature_H__,
  _SHT3C_RS485_temperature_L__,
  _SHT3C_RS485_crc_L__,
  _SHT3C_RS485_crc_H__,
  _SHT3C_RS485_RESPONSE_SIZE_GETDATA
};

typedef struct SHTC3_RS485_info{
  float temperature;
  float humidity;
};

#endif
