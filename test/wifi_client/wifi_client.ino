#include "ESPAsyncWebServer.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <M5Core2.h>
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";
const char* serverNameTemp = "http://192.168.4.1/temperature";
#include <Wire.h>
String temperature;
unsigned long previousMillis = 0;
const long interval = 5000; 
AsyncWebServer server(80);
void setup() {
  Serial.begin(115200);
  M5.begin(); //Init M5Core2.  初始化 M5Core2
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
      Serial.println(HTTP_GET);
        server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain","OK");
  });
      temperature = httpGETRequest(serverNameTemp);
    
      Serial.println("Temperature: " + temperature);
  
      previousMillis = currentMillis;
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
