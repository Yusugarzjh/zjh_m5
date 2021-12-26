#include <Arduino.h>
#include "SPI.h"
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Wire.h>
#include "Adafruit_MLX90614.h"
// #include "DHT.h"
// #define DHTPIN 14     // Digital pin connected to the DHT sensor
// #define DHTTYPE DHT11   // DHT 11
// DHT dht(DHTPIN, DHTTYPE);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
const char *ssid = "ESP32test";
const char *password = "123456789";
AsyncWebServer server(80);
#include "BluetoothSerial.h"
#define A_one 14
#define A_two 27
#define B_one 18
#define B_two 19
int speakerPin = 12; 

int length = 15; // the number of notes 
char notes[] = "CaCaCaCaCaCaCa"; // a space represents a rest 
int beats[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; 
int tempo = 300; 

void playTone(int tone, int duration) { 
  for (long i = 0; i < duration * 1000L; i += tone * 2) { 
    digitalWrite(speakerPin, HIGH); 
    delayMicroseconds(tone); 
    digitalWrite(speakerPin, LOW); 
    delayMicroseconds(tone); 
  } 
} 

void playNote(char note, int duration) { 
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' }; 
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 }; 

  // play the tone corresponding to the note name 
  for (int i = 0; i < 8; i++) { 
    if (names[i] == note) { 
      playTone(tones[i], duration); 
    } 
  } 
} 


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
char a='v';
BluetoothSerial SerialBT;
// String readTemp() {
//   return String(dht.readTemperature());
//   //return String(1.8 * bme.readTemperature() + 32);
// }

// String readHumi() {
//   return String(dht.readHumidity());
// }

String readobject()
{
  return String(mlx.readObjectTempC());
}

void xTaskOne(void *xTask1)
{
  while (1)
  {Serial.print(2);
    server.on("/objectTem", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/plain", readobject().c_str()); });
    delay(20);
  }
}
void xTaskTwo(void *xTask2)
{
  while (1)
  {
      Serial.print(3);
    if(a=='P')
    {
         for (int i = 0; i < length; i++) { 
    if (notes[i] == ' ') { 
      delay(beats[i] * tempo); // rest 
    } else { 
      playNote(notes[i], beats[i] * tempo); 
    } 

    // pause between notes 
    delay(tempo / 2);  
  } 
    }
    delay(20);
  }
}

void setup()
{
  Serial.begin(115200);
  xTaskCreatePinnedToCore(xTaskOne, "TaskOne", 4096, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(xTaskTwo, "TaskTwo", 4096, NULL, 1, NULL, 1);
  mlx.begin();
  // Serial.println(F("DHT11 test!"));
  // Serial.println();
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  SerialBT.begin("ESP32test"); // Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  server.begin();
  
  // dht.begin();
  pinMode(speakerPin, OUTPUT); 
  pinMode(A_one, OUTPUT);
  pinMode(A_two, OUTPUT);
  pinMode(B_one, OUTPUT);
  pinMode(B_two, OUTPUT);
  digitalWrite(A_one, 0);
  digitalWrite(A_two, 0);
  digitalWrite(B_one, 0);
  digitalWrite(B_two, 0);
}

void loop()
{
  // Serial.print(digitalRead(A_one));
  if (SerialBT.available())
  { a = SerialBT.read();
    if (a == 'T')
    {
      digitalWrite(A_one, 0);
      digitalWrite(A_two, 0);
      digitalWrite(B_one, 1);
      digitalWrite(B_two, 0);
      Serial.println("toword");
      Serial.print(digitalRead(A_one));
    }
    else if (a == 'R')
    {
      digitalWrite(A_one, 0);
      digitalWrite(A_two, 1);
      digitalWrite(B_one, 0);
      digitalWrite(B_two, 0);
      Serial.println("right");
    }
    else if (a == 'L')
    {
      digitalWrite(A_one, 1);
      digitalWrite(A_two, 0);
      digitalWrite(B_one, 1);
      digitalWrite(B_two, 0);
      Serial.println("left");
    }
    // else if (a == 'P')
    // {
        
    // }

  }
  else
  {
    //  Serial.print(digitalRead(A_one));
    digitalWrite(A_one, 1);
    digitalWrite(A_two, 0);
    digitalWrite(B_one, 0);
    digitalWrite(B_two, 0);
  }
}
