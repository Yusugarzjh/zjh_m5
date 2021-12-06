#### 红外传感器

#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup()
{
Serial.begin(115200);
mlx.begin();
}

void loop()
{
Serial.print("Ambient = ");
Serial.print(mlx.readAmbientTempC());
Serial.print("*C\tObject = ");
Serial.print(mlx.readObjectTempC());
Serial.println("*C");
Serial.print("Ambient = ");
Serial.print(mlx.readAmbientTempF());
Serial.print("*F\tObject = ");
Serial.print(mlx.readObjectTempF());
Serial.println("*F");

Serial.println();
delay(1000);
}

#### 舵机

#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo

// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 26;

void setup() {
  myservo.setPeriodHertz(50); 
  myservo.attach(servoPin);
}

void loop() {
  myservo.write(0); 
  delay(2000);
  myservo.write(180);
  delay(2000);

}

#### 温湿度传感器

#include "DHT.h"

#define DHTPIN 14     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}

#### 主板显示屏
#include <M5Core2.h>
#include "CUF_24px.h"

void setup()
{
  M5.begin(); //Init M5Stack.  初始化M5Core2
  M5.Lcd.setFreeFont(&unicode_24px);  //Set the GFX font to use.  设置要使用的GFX字体
  M5.Lcd.setTextDatum(TC_DATUM);  //Set text alignment to center-up alignment. 设置文本对齐方式为居中向上对齐
}

void loop()
{
  M5.Lcd.fillScreen(0);
  M5.Lcd.drawString("Hello world", 160, 60, 1); //Hello world is displayed in font 1 on (1600.60).
  M5.Lcd.drawString("你好  世界", 160, 90, 1);    //在(160,60)处以字体1显示hello world
  M5.Lcd.drawString("Здравствуй  мир", 160, 120, 1);
  M5.Lcd.drawString("こんにちは  せかい", 160, 150, 1);
  delay(3000);

  M5.Lcd.fillScreen(0); //Fill the screen with black (used to clear the screen) is equivalent to clear ().  使屏幕充满黑色(用来清屏)等同于clear()
  M5.Lcd.setCursor(0, 30);  // Set the text cursor 0,30 position.  设置文本光标在(0,30)处
  M5.Lcd.printf("☀☁☂☃");
  delay(3000);

  M5.Lcd.fillScreen(0);
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.printf("⛣⛤⛥⛦");
  delay(3000);
}

#### 无线客户机

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

//Your IP address or domain name with URL path
const char* serverNameTemp = "http://192.168.4.1/temperature";
//const char* serverNameHumi = "http://192.168.4.1/humidity";
//const char* serverNamePres = "http://192.168.4.1/pressure";

#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>

//#define SCREEN_WIDTH 128 // OLED display width, in pixels
//#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
//#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String temperature;
//String humidity;
//String pressure;

unsigned long previousMillis = 0;
const long interval = 5000; 

void setup() {
  Serial.begin(115200);

//  // Address 0x3C for 128x64, you might need to change this value (use an I2C scanner)
//  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
//    Serial.println(F("SSD1306 allocation failed"));
//    for(;;); // Don't proceed, loop forever
//  }
//  display.clearDisplay();
//  display.setTextColor(WHITE);
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
//      humidity = httpGETRequest(serverNameHumi);
//      pressure = httpGETRequest(serverNamePres);
      Serial.println("Temperature: " + temperature);
      
//      display.clearDisplay();
//      
//      // display temperature
//      display.setTextSize(2);
//      display.setTextColor(WHITE);
//      display.setCursor(0,0);
//      display.print("T: ");
//      display.print(temperature);
//      display.print(" ");
//      display.setTextSize(1);
//      display.cp437(true);
//      display.write(248);
//      display.setTextSize(2);
//      display.print("C");
//      
//      // display humidity
//      display.setTextSize(2);
//      display.setCursor(0, 25);
//      display.print("H: ");
//      display.print(humidity);
//      display.print(" %"); 
//      
//      // display pressure
//      display.setTextSize(2);
//      display.setCursor(0, 50);
//      display.print("P:");
//      display.print(pressure);
//      display.setTextSize(1);
//      display.setCursor(110, 56);
//      display.print("hPa");
//           
//      display.display();
//      
//      // save the last HTTP GET Request
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

#### 无线服务端

// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Wire.h>

//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>

// Set your access point network credentials
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/

//Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

//String readTemp() {
//  return String(bme.readTemperature());
//  //return String(1.8 * bme.readTemperature() + 32);
//}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();

  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain","OK");
  });
//
//  bool status;

  // default settings
  // (you can also pass in a Wire library object like &Wire2)
//  status = bme.begin(0x76);  
//  if (!status) {
//    Serial.println("Could not find a valid BME280 sensor, check wiring!");
//    while (1);
//  }

  // Start server
  server.begin();
}

void loop(){

}