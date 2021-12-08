#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Wire.h>
#include <HTTPClient.h>
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";
#include "BluetoothSerial.h"
const char* serverNameTemp = "http://192.168.4.1/temperature";
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
String temperature;
unsigned long previousMillis = 0;
const long interval = 5000; 
BluetoothSerial SerialBT;
AsyncWebServer server(80);
void setup(){
  Serial.begin(115200);
    SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  Serial.println();
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.begin();

}
 
void loop(){
  
 unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval) {
     // Check WiFi connection status

        server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain","OK");
  });
      temperature = httpGETRequest(serverNameTemp);
    
      Serial.println("Temperature: " + temperature);
  
      previousMillis = currentMillis;
    
  
  }
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
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
