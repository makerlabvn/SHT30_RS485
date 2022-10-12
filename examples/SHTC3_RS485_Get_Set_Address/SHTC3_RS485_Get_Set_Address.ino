/*
  Link product: 
  - https://hshop.vn/products/mach-chuyen-giao-tiep-uart-ttl-to-rs485-v3
  - https://hshop.vn/products/vietduino-uno
  - https://hshop.vn/products/cam-bien-do-am-nhiet-do-khong-khi-shtc3-temperature-humidity-sensor-ip67-v1-rs485-modbus-rtu
  - https://hshop.vn/products/cam-bien-do-am-nhiet-do-khong-khi-shtc3-temperature-humidity-sensor-v2-rs485-modbus-rtu
  - https://hshop.vn/products/cam-bien-do-am-nhiet-do-khong-khi-shtc3-temperature-humidity-sensor-v3-rs485-modbus-rtu
  - https://hshop.vn/products/cam-bien-do-am-nhiet-do-khong-khi-shtc3-temperature-humidity-sensor-v4-rs485-modbus-rtu


  Wiring:

        Uno/Mega2560                RS485-TTL V3  ---------------SHTC3_RS485
        Vcc-5V -------------------------Vcc--------------------------Vcc
        GND   --------------------------GND--------------------------GND
        11(RX) <--------------<-----RX_RS485_TTL_V3
        12(TX) --------------->-----TX_RS485_TTL_V3
                                    RS485_TTL_V3_A -------------------A
                                    RS485_TTL_V3_B -------------------B
        

*/

#include "SHTC3_RS485.h"

#define TX_RS485_TTL_V3     12
#define RX_RS485_TTL_V3     11
unsigned int delayBetween2Sensor = 5;

SHTC3_RS485 shtc3_rs485(RX_RS485_TTL_V3, TX_RS485_TTL_V3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // 4800 if SHTC3_RS485 connect Hardware Serial
  Serial.println("Start Set Address for SHTC3_RS485 ! Please connect only 1 sensor to Arduino");

  // init module
  shtc3_rs485.begin(); // default SHTC3_RS485 Baudrate: 4800
  shtc3_rs485.setTimeout(100);

  uint8_t mySensorAddress = shtc3_rs485.getAddress();

  if(mySensorAddress != 0xff){
    Serial.println("Curent Sensor address: " + String(mySensorAddress));
    Serial.println("Please type your new Address from 1 to 254");
    while(1){
      if(Serial.available()){
        int newAddress = Serial.readStringUntil('\n').toInt();

        if((newAddress > 0) && (newAddress < 255)){
          if(shtc3_rs485.setAddress(mySensorAddress, newAddress) == true){
            mySensorAddress = newAddress;
            Serial.println("Set Address successfully!");
          }else{
            Serial.println("Set Address Fail !");
          }
        }
        Serial.println("Please type your new Address from 1 to 254");
      }
    }
  }else{
    Serial.println("No Sensor detected!");
  }
  
}

void loop() {
  
}