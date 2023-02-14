                          // NODEMCU SIDE //

//Wifi libraries

  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>

#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial nodemcu(D6, D5); // Rx D6 Tx D5
//Online creds
  const char* ssid = "Ejames";
  const char* password = "12020076";
  const char* serverName = "http://trial.bumosy.tech/esp-post-data.php";
   const char* serverName = "http://trial.bumosy.tech/try.php";
  String apiKeyValue = "tPmAT5Ab3j7F9";
  String sensorLocation = "Room201";
  unsigned long lastTime = 0;
  unsigned long timerDelay = 2000;

void setup() {
  Serial.begin(115200);
  nodemcu.begin(115200); 

//WIFI
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
  //Json
        StaticJsonDocument<500> sensor;
    DeserializationError error = deserializeJson(sensor, nodemcu);
    boolean sense = sensor.isNull();
//Make sure only with values go through
if(sense == 0){

//To the internet
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Stuff
      float hum = sensor["humidity"] ;
      float temp = sensor["temperature"];
      float lux = sensor["illuminance"];
      float motion = sensor["movement"];

      //Prepare your HTTP POST request data


      String httpRequestData = "api_key=" + apiKeyValue + "&location=" + sensorLocation + "&temp=" + String(temp)
                            + "&hum=" + String(hum) + "&light=" + String(lux) + "&motion=" + String(motion) + "";
      // Serial.print("httpRequestData: ");
      // Serial.println(httpRequestData);
    


      

      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      // If you need an HTTP request with a content type: text/plain
      //http.addHeader("Content-Type", "text/plain");
      //int httpResponseCode = http.POST("Hello, World!");

      // If you need an HTTP request with a content type: application/json, use the following:
      //http.addHeader("Content-Type", "application/json");
      //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");

      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
    }

  }

}


