// micro=test4 esp side
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include "FS.h"
#include <StreamUtils.h>

SoftwareSerial nodemcu(D6, D5); // Rx D6 Tx D5


void setup() {
    Serial.begin(74880);
  nodemcu.begin(74880); 
  SPIFFS.begin();
  //SPIFFS.format();
  //startMillis = millis();

}

void loop() {
  //File file = SPIFFS.open("file.txt", "w");
  //currentMillis = millis();
  // long x = random();
  StaticJsonDocument<64> sensor;
    deserializeJson(sensor, nodemcu);
 String jsonString;
  serializeJson(sensor,jsonString);


    File file = SPIFFS.open("/data.bin", "w");
  if (!file) {
    Serial.println("An Error has occurred while opening the file");
    return;
  }
  file.write((uint8_t*)jsonString.c_str(), jsonString.length());
  file.close();
  

 }



}

  



