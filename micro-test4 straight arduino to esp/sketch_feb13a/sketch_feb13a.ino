#include <Arduino.h>
#include <ArduinoJson.h>
#include <FS.h>

const int bufferSize = 200;
StaticJsonDocument<200> buffer[bufferSize];
int bufferIndex = 0;

void setup() {
  SPIFFS.begin();
}

void loop() {
  // Add data to the buffer
  StaticJsonDocument<200> doc;
  doc["sensor"] = "gps";
  doc["time"] = millis();
  buffer[bufferIndex] = doc;
  bufferIndex++;

  // Write the buffer to the flash memory if it's full
  if (bufferIndex == bufferSize) {
    bufferIndex = 0;
    writeBufferToFlash();
  }
}


void writeBufferToFlash() {
  File file = SPIFFS.open("/sensorData.bin", "a");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  for (int i = 0; i < bufferSize; i++) {
    size_t len = serializeJson(buffer[i], (char*)0, 0);
    file.write((uint8_t*)&len, sizeof(size_t));
    file.write(buffer[i].as<char*>(), len);
  }
  file.close();
}
