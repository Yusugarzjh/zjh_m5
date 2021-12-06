
#include <WiFi.h>
#include <HTTPClient.h>
#include <M5Core2.h>
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";
const char* serverNameTemp = "http://192.168.4.1/temperature";
const char* serverNameHumi = "http://192.168.4.1/humidity";
const char* serverNameobjectTem = "http://192.168.4.1/objectTem";
#include <Wire.h>
String temperature;
String humidity;
String objectTem;
unsigned long previousMillis = 0;
const long interval = 5000; 
void setup() {
  Serial.begin(115200);
  M5.begin(); //Init M5Core2.  初始化 M5Core2
  M5.Lcd.fillScreen(BLACK); // Set the screen background.  设置屏幕底色为白色
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}
void loop() {
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval) {
     // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED ){ 
      temperature = httpGETRequest(serverNameTemp);
      humidity = httpGETRequest(serverNameHumi);
      objectTem = httpGETRequest(serverNameobjectTem);
      Serial.println("Temperature: " + temperature);
      Serial.println("humidity: " + humidity);
      Serial.println("objectTem: " + objectTem);
      previousMillis = currentMillis;
      M5.Lcd.fillScreen(BLACK); 
      M5.Lcd.setCursor(10, 10); //Move the cursor position to (x,y).  移动光标位置到 (x,y)处
      M5.Lcd.setTextColor(WHITE); //Set the font color to white.  设置字体颜色为白色
      M5.Lcd.setTextSize(3);
      M5.Lcd.printf("temperature");//Set the font size.  设置字体大小
      M5.Lcd.printf(temperature.c_str());  //Serial output format string.  输出格式化字符串
      
       M5.Lcd.setCursor(10, 80); //Move the cursor position to (x,y).  移动光标位置到 (x,y)处
      M5.Lcd.setTextColor(WHITE); //Set the font color to white.  设置字体颜色为白色
      M5.Lcd.setTextSize(3);
      M5.Lcd.printf("humidity");//Set the font size.  设置字体大小
      M5.Lcd.printf(humidity.c_str());  //Serial output format string.  输出格式化字符串
      
       M5.Lcd.setCursor(10, 160); //Move the cursor position to (x,y).  移动光标位置到 (x,y)处
      M5.Lcd.setTextColor(WHITE); //Set the font color to white.  设置字体颜色为白色
      M5.Lcd.setTextSize(3);
      M5.Lcd.printf("objectTem");//Set the font size.  设置字体大小
      M5.Lcd.printf(objectTem.c_str());  //Serial output format string.  输出格式化字符串
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
