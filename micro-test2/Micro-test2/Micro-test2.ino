#include <ArduinoJson.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>



Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
  
void setup() {
  Serial.begin(9600);
     if(!accel.begin()){
      Serial.println("No ADXL345 sensor detected.");
      while(1);
   }
  
}

void loop(){
  StaticJsonDocument<1000> vibrationx;
  StaticJsonDocument<1000> vibrationy;
  StaticJsonDocument<1000> vibrationz;
  JsonArray motionx = vibrationx.to<JsonArray>();
  JsonArray motiony = vibrationy.to<JsonArray>();
  JsonArray motionz = vibrationz.to<JsonArray>();

  int i=0;
  int maxSample=100;
  float x_acc;
  float y_acc;
  float z_acc;
  
   sensors_event_t event; 
   accel.getEvent(&event);
   
     x_acc = event.acceleration.x;
     y_acc = event.acceleration.y;
     z_acc = event.acceleration.z;

  while ( i < maxSample){
  motionx.add(x_acc);
  motiony.add(y_acc);
  motionz.add(z_acc);
        ++i;
  }
  Serial.println(" ");
  serializeJson(vibrationx, Serial);
  Serial.println(" ");
    //Serial.println(motionx.size());
 serializeJson(vibrationy, Serial);
  Serial.println(" ");
   // Serial.println(motiony.size());
 serializeJson(vibrationz, Serial);
  Serial.println(" ");
    Serial.println(motionz.size());
  delay(1000);
  vibrationx.clear();
  vibrationy.clear();
  vibrationz.clear();
  }
