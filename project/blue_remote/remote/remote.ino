#include "BluetoothSerial.h"
#include <M5Core2.h>
BluetoothSerial SerialBT;
String name = "ESP32test";
bool connected;
void setup() {
  Serial.begin(115200);
  SerialBT.begin("m5stacktest",true); 
  Serial.println("The device started in master mode, make sure remote BT device is on!");
  connected = SerialBT.connect(name);
  if(connected) {
    Serial.println("Connected Succesfully!");
  } else {
    while(!SerialBT.connected(10000)) {
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app."); 
    }
  }
//   disconnect() may take upto 10 secs max
  if (SerialBT.disconnect()) {
    Serial.println("Disconnected Succesfully!");
  }
  // this would reconnect to the name(will use address, if resolved) or address used with connect(name/address).
  SerialBT.connect();
   M5.begin();
   M5.Lcd.fillScreen(BLACK);
   M5.Lcd.setCursor(10, 10); //Move the cursor position to (x,y).  移动光标位置到 (x,y)处
  M5.Lcd.setTextColor(WHITE); //Set the font color to white.  设置字体颜色为白色
  M5.Lcd.setTextSize(3);  //Set the font size.  设置字体大小
  M5.Lcd.printf("connected!");  //Serial output format string.  输出格式化字符串
     
  
}

void loop() {
  M5.update();
if(M5.BtnA.wasReleased())
    SerialBT.print("Y");
if(M5.BtnB.wasReleased())
    SerialBT.print("N");
    

 
}
