#include "SHTC3_RS485.h"

/*
 Prototype:
  - setAddress tu 5 sang 1: (chú ý byte 0 và byte 5), 2 byte cuối là crc
    TX: 0x05 0x06 0x07 0xD0 0x00 0x01 0x49 0x03
    RX: 0x05 0x06 0x07 0xD0 0x00 0x01 0x49 0x03

  - setAddress tu 1 sang 5: (chú ý byte 0 và byte 5), 2 byte cuối là crc
    TX: 0x01 0x06 0x07 0xD0 0x00 0x05 0x49 0x44
    RX: 0x01 0x06 0x07 0xD0 0x00 0x05 0x49 0x44

  - GetAddress:
    TX: 0xff 0x03 0x07 0xD0 0x00 0x01 0x91 0x59
    RX: 01 03 02 00 01 79 84  (address là 1)
    RX: 05 03 02 00 05 89 87  (address là 5)
*/

// byte getValue_para_SHTC3_RS485[8] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};
byte getValue_para_SHTC3_RS485[8] = {0x05, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC5, 0x8f};
byte getAddress_para_SHTC3_RS485[8] = {0xff, 0x03, 0x07, 0xD0, 0x00, 0x01, 0xC5, 0x8f};

SHTC3_RS485::SHTC3_RS485()
{
  Serial.begin(4800);
  this->port = &Serial;
  typeSerial = SHT30_RS485_HARD_SERIAL;
  setTimeout(MIN_PZEM_TIMEOUT);
}

SHTC3_RS485::SHTC3_RS485(HardwareSerial *serial)
{
  this->port = serial;
  typeSerial = SHT30_RS485_HARD_SERIAL;
  setTimeout(MIN_PZEM_TIMEOUT);
}

SHTC3_RS485::SHTC3_RS485(SoftwareSerial *serial)
{
  //  serial->begin(9600);
  this->port = serial;
  typeSerial = SHT30_RS485_SOFT_SERIAL;
  setTimeout(MIN_PZEM_TIMEOUT);
}

SHTC3_RS485::SHTC3_RS485(int rxPin, int txPin)
{
  SoftwareSerial *yy = new SoftwareSerial(rxPin, txPin);
  //  yy->begin(9600);
  this->port = yy;
  typeSerial = SHT30_RS485_SOFT_SERIAL;
  setTimeout(MIN_PZEM_TIMEOUT);
}

void SHTC3_RS485::begin(unsigned long _tembaud)
{
  if (typeSerial == SHT30_RS485_HARD_SERIAL)
  {
    HardwareSerial *tt = (HardwareSerial *)port;
    tt->begin(_tembaud);
  }
  else
  {
    SoftwareSerial *tt = (SoftwareSerial *)port;
    tt->begin(_tembaud);
  }
}

void SHTC3_RS485::begin()
{
  this->begin(4800);
}

void SHTC3_RS485::setTimeout(unsigned int _ui_timeOut)
{
  if (_ui_timeOut < MIN_PZEM_TIMEOUT)
  {
    ui_timeOut = MIN_PZEM_TIMEOUT;
  }
  else if (_ui_timeOut > MAX_PZEM_TIMEOUT)
  {
    ui_timeOut = MAX_PZEM_TIMEOUT;
  }
  else
    ui_timeOut = _ui_timeOut;
}

SHTC3_RS485_info SHTC3_RS485::getData()
{
  SHTC3_RS485_info temp_valueObject;
  while (this->port->available())
  {
    this->port->read();
  }
  DB("this->port->write");
  this->port->write(getValue_para_SHTC3_RS485, sizeof(getValue_para_SHTC3_RS485));

  unsigned long temTime = millis();
  bool b_complete = false;
  uint8_t myBuf[_SHT3C_RS485_RESPONSE_SIZE_GETDATA];

  while ((millis() - temTime) < ui_timeOut)
  {
    if (this->port->available())
    {
      this->port->readBytes(myBuf, _SHT3C_RS485_RESPONSE_SIZE_GETDATA);
      b_complete = true;
      DB_LN("this->port->available");
      yield();
      break;
    }
  }

  if (b_complete)
  {

    temp_valueObject.humidity = SHT3C_RS485_GET_VALUE(humidity);
    temp_valueObject.temperature = SHT3C_RS485_GET_VALUE(temperature);
  }
  else
  {
    DB_LN(F("Read fail"));
    temp_valueObject.temperature = 0.0;
    temp_valueObject.humidity = 0.0;
  }
  return temp_valueObject;
}

uint16_t SHTC3_RS485::ModRTU_CRC(byte *buf, int len)
{
  uint16_t crc = 0xFFFF;

  for (int pos = 0; pos < (len - 2); pos++)
  {
    crc ^= (uint16_t)buf[pos]; // XOR byte into least sig. byte of crc

    for (int i = 8; i != 0; i--)
    { // Loop over each bit
      if ((crc & 0x0001) != 0)
      {            // If the LSB is set
        crc >>= 1; // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else         // Else LSB is not set
        crc >>= 1; // Just shift right
    }
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
  buf[len - 2] = (0xff & crc);
  buf[len - 1] = (0xff & (crc >> 8));
  // Serial.println("++++++++++++++");
  // Serial.println(buf[len - 1], HEX);
  // Serial.println(buf[len - 2], HEX);
  // Serial.println("________________");
  return crc;
}

uint8_t SHTC3_RS485::getAddress()
{
  uint8_t tempCommandBuf[]={0xff, 0x03, 0x07, 0xD0, 0x00, 0x01, 0x91, 0x59};
  while (this->port->available())
  {
    this->port->read();
  }
  DB("this->port->write");
  this->port->write(tempCommandBuf, sizeof(tempCommandBuf));

  unsigned long temTime = millis();
  bool b_complete = false;
  uint8_t myBuf[_SHT3C_RS485_RESPONSE_SIZE_GETADDR];

  while ((millis() - temTime) < ui_timeOut)
  {
    if (this->port->available())
    {
      this->port->readBytes(myBuf, _SHT3C_RS485_RESPONSE_SIZE_GETADDR);
      b_complete = true;
      DB_LN("this->port->available");
      yield();
      break;
    }
  }

  if (b_complete)
  {

    return myBuf[0];
  }
  else
  {
    DB_LN(F("Read fail"));
    return 0xff;
  }
}

bool SHTC3_RS485::setAddress(uint8_t fromAddr_, uint8_t toAddr_)
{
  uint8_t tempCommandBuf[]={fromAddr_, 0x06, 0x07, 0xD0, 0x00, toAddr_, 0x49, 0x44};
  this->ModRTU_CRC(tempCommandBuf, sizeof(tempCommandBuf));

  while (this->port->available())
  {
    this->port->read();
  }
  DB("this->port->write");
  this->port->write(tempCommandBuf, sizeof(tempCommandBuf));

  unsigned long temTime = millis();
  bool b_complete = false;
  uint8_t myBuf[_SHT3C_RS485_RESPONSE_SIZE_SETADDR];

  while ((millis() - temTime) < ui_timeOut)
  {
    if (this->port->available())
    {
      this->port->readBytes(myBuf, _SHT3C_RS485_RESPONSE_SIZE_SETADDR);
      b_complete = true;
      DB_LN("this->port->available");
      yield();
      break;
    }
  }

  if (b_complete)
  {
    for(int cf = 0; cf < _SHT3C_RS485_RESPONSE_SIZE_SETADDR; cf++){
      if(myBuf[cf] != tempCommandBuf[cf]) return false;
    }
    return true;
  }
  else
  {
    DB_LN(F("Read fail"));
    return false;
  }
}

SHTC3_RS485_info SHTC3_RS485::getData(uint8_t address_)
{
  SHTC3_RS485_info temp_valueObject;
  uint8_t tempCommandBuf[]={address_, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC5, 0x8f};
  this->ModRTU_CRC(tempCommandBuf, sizeof(tempCommandBuf));
  while (this->port->available())
  {
    this->port->read();
  }
  DB("this->port->write");
  this->port->write(tempCommandBuf, sizeof(tempCommandBuf));

  unsigned long temTime = millis();
  bool b_complete = false;
  uint8_t myBuf[_SHT3C_RS485_RESPONSE_SIZE_GETDATA];

  while ((millis() - temTime) < ui_timeOut)
  {
    if (this->port->available())
    {
      this->port->readBytes(myBuf, _SHT3C_RS485_RESPONSE_SIZE_GETDATA);
      b_complete = true;
      DB_LN("this->port->available");
      yield();
      break;
    }
  }

  if (b_complete)
  {

    temp_valueObject.humidity = SHT3C_RS485_GET_VALUE(humidity);
    temp_valueObject.temperature = SHT3C_RS485_GET_VALUE(temperature);
  }
  else
  {
    DB_LN(F("Read fail"));
    temp_valueObject.temperature = 0.0;
    temp_valueObject.humidity = 0.0;
  }
  return temp_valueObject;
}