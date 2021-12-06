#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "DHT.h"
#define DHTPIN 14     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";
AsyncWebServer server(80);

String readTemp() {
  return String(dht.readTemperature());
  //return String(1.8 * bme.readTemperature() + 32);
}

String readHumi() {
  return String(dht.readHumidity());
}

String readobject() {
  return String(mlx.readObjectTempC());
}
void setup(){
  Serial.begin(115200);
  mlx.begin();
   Serial.println(F("DHT11 test!"));
  Serial.println();
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();
    dht.begin();
}
 
void loop(){
  
    server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain",readTemp().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain",readHumi().c_str());
  });
  server.on("/objectTem", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain",readobject().c_str());
  });
  delay(2000);
}
