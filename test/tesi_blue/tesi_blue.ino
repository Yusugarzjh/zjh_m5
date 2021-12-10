//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"
#include <string.h>
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
// if (Serial.available()) {

      SerialBT.println("asd");
  
//    SerialBT.write(Serial.read());
//  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }

  

  delay(1000);
}
//    String inString="";
//  while (Serial.available()>0) {
//    char inChar = (char)Serial.read();
//    inString += inChar;
//    
//delay(10);
//  }
//  if(inString!="")
//  {   
//    if(inString=="OK\n")
//    Serial.print(inString);
//    Serial.print(inString);
//   Serial.write(inString.c_str());
//      Serial.println(strlen(inString.c_str()));
//  }
//if(strcmp("OK",inString.c_str()))
    
      
//  if (SerialBT.available()) {
//    Serial.write(SerialBT.read());
//  }
