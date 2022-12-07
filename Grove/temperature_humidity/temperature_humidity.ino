//#define DHTPIN 3
#include "Arduino_SensorKit.h"
 
void setup() {
  Serial.begin(9600);
  Environment.begin();
}
 
void loop() {

  Serial.print("Humidity: ");
  Serial.print(Environment.readHumidity());
  Serial.print(" %, Temperature: ");
  Serial.print(Environment.readTemperature());
  Serial.println(" Celsius");
  delay(2000);
  
}
