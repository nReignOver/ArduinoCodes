// #include <SPI.h>
// #include <SD.h>
#include <Adafruit_ADXL345_U.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <StreamUtils.h>

Adafruit_ADXL345_Unified adxl = Adafruit_ADXL345_Unified(12345);
SoftwareSerial nodemcu(5, 6); // Rx 5 Tx 6
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 0;
const unsigned long stop = 10000;
int number = 1;


void setup() {
  nodemcu.begin(74880);
  Serial.begin(74880);
  adxl.begin();
  startMillis = millis();

}


void loop() { 
  StaticJsonDocument<64> sensor;
  sensors_event_t event;
  adxl.getEvent(&event);
  currentMillis = millis();
      
      //sensor["t"]= currentMillis;
      //float x = 
      sensor["x"] = event.acceleration.x;
      //float y = 
      sensor["y"] = event.acceleration.y;
      //float z = 
      sensor["z"] = event.acceleration.z;;
      
      serializeJson(sensor, nodemcu);
      //serializeJson(sensor, Serial);
      //Serial.println("");
      // Serial.print(currentMillis); Serial.print(" "); Serial.print(number++); Serial.print(" ");
      // Serial.print(x); Serial.print(" ");
      // Serial.print(y); Serial.print(" ");
      // Serial.println(z); 
  delay(250);
}

//So i use buffer? lets try
