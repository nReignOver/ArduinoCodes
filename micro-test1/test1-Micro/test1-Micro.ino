#include <ArduinoJson.h>

int i = 0;
int sample = 100;
int j = 1;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
}

void myArray() {
  
 int excel[sample];
 while (i<sample){
  excel[i]=j;
    Serial.println(excel[i]);
  ++i;
  ++j;
  delay(20);
    
  }
  
}
void letsSee(){
  
  myArray();
  excel;
  StaticJsonBuffer<1000> jsonBuffer;
  JsonArray& number = jsonBuffer.parseArray(excel);
  
  
  



}
