#include <DHT.h>;

//Constants
#define DHTPIN 2   
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE); 

float temp; 

void setup()
{
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
    delay(500);
    temp= dht.readTemperature();
    Serial.print("Temperature: ");
    Serial.println(temp);
    delay(500); 
}

   
