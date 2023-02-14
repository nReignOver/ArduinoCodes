// Use to send data from arduino to ESP
// Use large file after successful

                          // NODEMCU SIDE //
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial nodemcu(D6, D5); // Rx D6 Tx D5

void setup() {
  Serial.begin(9600);
  nodemcu.begin(9600); 
//while(!Serial) continue;

}
void loop(){
    StaticJsonBuffer<100> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(nodemcu);    
    Serial.println("invalid Json Object.");
  jsonBuffer.clear();
  return;
  float hum = data["hum"];
  Serial.println (hum);
}
