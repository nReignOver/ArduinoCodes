#include <Wire.h>
#include <Adafruit_ADXL345_U.h>
#include <ArduinoJson.h>

Adafruit_ADXL345_Unified adxl = Adafruit_ADXL345_Unified(12345);
const int dataCount = 20;

void setup() {
  Serial.begin(9600);
  adxl.begin();
}

void loop() {
  StaticJsonDocument<1200> doc; // to hold all data
  JsonArray xArr = doc.createNestedArray("x");
  JsonArray yArr = doc.createNestedArray("y");
  JsonArray zArr = doc.createNestedArray("z");

  for(int i = 0; i <=10; i++) {
    sensors_event_t event;
    adxl.getEvent(&event);
  
    xArr.add(event.acceleration.x);
    yArr.add(event.acceleration.y);
    zArr.add(event.acceleration.z);
  }
  serializeJson(doc, Serial);
  Serial.println("");
  delay(1000);
}
