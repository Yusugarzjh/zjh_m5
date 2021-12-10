#define RELAY_PIN 4
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
pinMode(RELAY_PIN, OUTPUT);
digitalWrite(RELAY_PIN, HIGH);
}

void loop() {
 char a;
  if (SerialBT.available()) {
  a=SerialBT.read();
  if(a=='Y')
  { 
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("very good");
  }
  if(a=='N')
    {
       digitalWrite(RELAY_PIN, LOW);
      Serial.println("well");
      }
                            }

}
