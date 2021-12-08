#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Wire.h>
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";
AsyncWebServer server(80);
void setup(){
  Serial.begin(115200);
   Serial.println(F("DHT11 test!"));
  Serial.println();
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.begin();

}
 
void loop(){
  
//    server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
//    request->send_P(200, "text/plain","ERROR");
//  });
  delay(2000);
}
