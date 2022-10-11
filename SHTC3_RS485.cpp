#include "SHTC3_RS485.h"

byte getValue_para_SHTC3_RS485[8] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};

 SHTC3_RS485::SHTC3_RS485() {
  Serial.begin(9600);
  port = &Serial;
  typeSerial = SHT30_RS485_HARD_SERIAL;
  setTimeout(MIN_PZEM_TIMEOUT);
}

SHTC3_RS485::SHTC3_RS485(HardwareSerial * serial) {
//  serial->begin(9600);
  port = serial;
  typeSerial = SHT30_RS485_HARD_SERIAL;
  setTimeout(MIN_PZEM_TIMEOUT);
}

SHTC3_RS485::SHTC3_RS485(SoftwareSerial * serial) {
//  serial->begin(9600);
  port = serial;
  typeSerial = SHT30_RS485_SOFT_SERIAL;
  setTimeout(MIN_PZEM_TIMEOUT);
}

SHTC3_RS485::SHTC3_RS485(int rxPin, int txPin) {
  SoftwareSerial * yy = new SoftwareSerial(rxPin, txPin);
//  yy->begin(9600);
  port = yy;
  typeSerial = SHT30_RS485_SOFT_SERIAL;
  setTimeout(MIN_PZEM_TIMEOUT);
}

void SHTC3_RS485::begin(unsigned long _tembaud) {
  if (typeSerial == SHT30_RS485_HARD_SERIAL) {
    HardwareSerial * tt = (HardwareSerial *)port;
    tt->begin(_tembaud);
  } else {
    SoftwareSerial * tt = (SoftwareSerial *) port;
    tt->begin(_tembaud);
  }
}

void SHTC3_RS485::begin() {
  this->begin(4800);
}

void SHTC3_RS485::setTimeout(unsigned int _ui_timeOut) {
  if (_ui_timeOut < MIN_PZEM_TIMEOUT) {
    ui_timeOut = MIN_PZEM_TIMEOUT;
  } else if (_ui_timeOut > MAX_PZEM_TIMEOUT) {
    ui_timeOut = MAX_PZEM_TIMEOUT;
  } else
    ui_timeOut = _ui_timeOut;
}

SHTC3_RS485_info SHTC3_RS485::getData(){
  SHTC3_RS485_info temp_valueObject;
  while (port->available()) {
    port->read();
  }
  DB("port->write");
  port->write(getValue_para_SHTC3_RS485, sizeof(getValue_para_SHTC3_RS485));

  unsigned long temTime = millis();
  bool b_complete = false;
  uint8_t myBuf[RESPONSE_SIZE];

  while ((millis() - temTime) < ui_timeOut) {
    if (port->available()) {
      port->readBytes(myBuf, RESPONSE_SIZE);
      b_complete = true;
      DB_LN("port->available");
      yield();
      break;
    }
  }

  if (b_complete) {
    
    temp_valueObject.humidity = SHT3C_RS485_GET_VALUE(humidity);
    temp_valueObject.temperature = SHT3C_RS485_GET_VALUE(temperature);

  } else {
    DB_LN(F("Read fail"));
    temp_valueObject.temperature = 0.0;
    temp_valueObject.humidity = 0.0;
  }
  return temp_valueObject;
}

