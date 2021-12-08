//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

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
char a='a';
//  if (Serial.available()) {
//    SerialBT.write(Serial.read());
//  }
  while (SerialBT.available()>0) //返回当前剩余字符个数，当SerialBT.available()>0时，说明串口接受到了数据
  {
//    Serial.write(SerialBT.read());
  char inchar=SerialBT.read();
a=(char)inchar;
    delay(10);
//      a=SerialBT.read();
//       SerialBT.println(a);
//      if(a=="OK")
//        Serial.println("ok");
  }
  if(a!='a')
  {
    Serial.println(a);
    }
    if(a=='O')
    Serial.println("yes");
  delay(20);
}
