/*
  Link product: 
  - https://hshop.vn/products/mach-chuyen-giao-tiep-uart-ttl-to-rs485-v3
  - https://hshop.vn/products/vietduino-uno
  - https://hshop.vn/products/cam-bien-do-am-nhiet-do-khong-khi-shtc3-temperature-humidity-sensor-ip67-v1-rs485-modbus-rtu
  - https://hshop.vn/products/cam-bien-do-am-nhiet-do-khong-khi-shtc3-temperature-humidity-sensor-v2-rs485-modbus-rtu
  - https://hshop.vn/products/cam-bien-do-am-nhiet-do-khong-khi-shtc3-temperature-humidity-sensor-v3-rs485-modbus-rtu
  - https://hshop.vn/products/cam-bien-do-am-nhiet-do-khong-khi-shtc3-temperature-humidity-sensor-v4-rs485-modbus-rtu


  Wiring:

        Uno/Mega2560                RS485-TTL V3  ---------------SHTC3_RS485(1)-------SHTC3_RS485(2)
        Vcc-5V -------------------------Vcc--------------------------Vcc-------------------Vcc
        GND   --------------------------GND--------------------------GND-------------------GND
        11(RX) <--------------<-----RX_RS485_TTL_V3
        12(TX) --------------->-----TX_RS485_TTL_V3
                                    RS485_TTL_V3_A -------------------A---------------------A
                                    RS485_TTL_V3_B -------------------B---------------------B
        

*/

#include "SHTC3_RS485.h"

#define TX_RS485_TTL_V3     12
#define RX_RS485_TTL_V3     11
unsigned int delayBetween2Sensor = 10;

SHTC3_RS485 shtc3_rs485(RX_RS485_TTL_V3, TX_RS485_TTL_V3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start test SHTC3_RS485 ! ++++");

  // init module
  shtc3_rs485.begin(); // default SHTC3_RS485 Baudrate: 4800
  shtc3_rs485.setTimeout(100);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  //Get data from your SHTC3_RS485, every 2s (See document)
  SHTC3_RS485_info SHTC3_RS485_Data = shtc3_rs485.getData(0x01);

  Serial.print(SHTC3_RS485_Data.temperature);
  Serial.print(F(" C\t\t"));

  Serial.print(SHTC3_RS485_Data.humidity);
  Serial.print(F(" %\t\t"));

  delay(delayBetween2Sensor); // add delay of at least 10ms. It 's very important!!

  SHTC3_RS485_info SHTC3_RS485_Data2 = shtc3_rs485.getData(0x05);

  Serial.print(SHTC3_RS485_Data2.temperature);
  Serial.print(F(" C\t\t"));

  Serial.print(SHTC3_RS485_Data2.humidity);
  Serial.print(F(" %\t\t"));

  Serial.println();
  delay(2000);
  
}