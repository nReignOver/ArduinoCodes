                                            //ARDUINO SENSOR CODE                 

#include <SoftwareSerial.h>
#include "DHT.h"
#include <ArduinoJson.h >

#define DHTPIN 4
#define DHTTYPE DHT11
#define TEMT A0
#define Sensor 7

DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial nodemcu(5,6); // Arduino Rx-5 Tx-6

void setup() {
// put your setup code here, to run once:
  nodemcu.begin(115200);
  Serial.begin(115200);
    dht.begin();
    pinMode (Sensor, INPUT);
}

void loop() {
  //Json
    StaticJsonDocument<500> sensor;

  // DHT Code
    float humi  = dht.readHumidity();
    float tempC = dht.readTemperature();
    // Serial.print("Humidity: ");
    // Serial.print(humi);
    // Serial.print("  |  "); 
    // Serial.print("Temperature: ");
    // Serial.print(tempC);
    // Serial.println("");

  //TEMT6000
    float volts = analogRead(TEMT) * 5.0 / 1024.0;
    float amps = volts / 10000.0;
    float microamps = amps * 1000000;
    float lux = microamps * 2.0;
    // Serial.print("Illuminance:  ");
    // Serial.print(lux);

  //RCWL
    int motion = digitalRead(Sensor);
    // Serial.print("Movement:  ");
    // Serial.print(motion);

  //Json cont.
    sensor["humidity"] = humi;
    sensor["temperature"] = tempC;
    sensor["illuminance"] = lux;
    sensor["movement"] = motion;

  //Sending to ESP
    serializeJson(sensor, nodemcu);
    delay(2000);
}
