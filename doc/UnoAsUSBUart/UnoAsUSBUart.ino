#include "SoftwareSerial.h"
SoftwareSerial unoAsUSB_Uart(2,3);

#define BAUD_SHTC3_RS485  4800

void setup()
{
  Serial.begin(9600);
  Serial.println("Start communicate SHTC3_RS485 with Baud: " + String(BAUD_SHTC3_RS485));
  unoAsUSB_Uart.begin(BAUD_SHTC3_RS485);
}

void loop(){
  if(unoAsUSB_Uart.available()){
    Serial.write(unoAsUSB_Uart.read());
  }

  if(Serial.available()){
    unoAsUSB_Uart.write(Serial.read());
  }
}