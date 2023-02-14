// Use to send data from arduino to ESP
// Use large file after successful

                          // ARDUINO SIDE //


float hum = 75.5;          
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial nodemcu(5,6); // Arduino Rx-5 Tx-6

void setup() {
nodemcu.begin(9600);
Serial.begin(9600);
}

void loop() {
 
  StaticJsonBuffer<100> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();
  data["hum"]=hum;
  data.printTo(nodemcu);
   jsonBuffer.clear();
   delay(500);
  data.printTo(Serial);
}
