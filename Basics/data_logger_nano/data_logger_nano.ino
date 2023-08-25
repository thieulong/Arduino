#include <SdFat.h>         
#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>  
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LowPower.h>

// Date & Time to activate Air Pumps
#define SUNDAY    0
#define MONDAY    1 
#define TUESDAY   2
#define WEDNESDAY 3
#define THURSDAY  4
#define FRIDAY    5
#define SATURDAY  6

uint8_t DAY = WEDNESDAY;
uint8_t START_HH_ODD_WEEK = 1; 
uint8_t START_HH_EVEN_WEEK = 1; 
uint8_t START_MM = 20; 

char daysOfTheWeek[7][12] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

// Device name
const String device = "Pondi_1";

// Data-Logger
RTC_DS1307 RTC;          
#define DS1307_I2C_ADDRESS 0x68
SdFat SD;            
const int chipSelect = 10;  
char tmeStrng[] = "0000/00/00,00:00:00"; 

// Water temperature
const int waterTempPin = 8;
OneWire oneWire(waterTempPin); 
DallasTemperature waterTempSensor(&oneWire);
float waterTempCelsius;

// Water turbidity
const int waterTurbidityPin = A2;
float minVoltage = 0;
float maxVoltage = 4.5;
int turbidityMinValue = 100;
int turbidityMaxValue = 0;

// Air pump's relay
const int RELAY_1 = A0;
const int RELAY_2 = A1;

void setup() {
  Serial.begin(9600);   
  Wire.begin();         
  RTC.begin();           

  Serial.print("Blue Carbon Lab - ");
  Serial.print(device);
  Serial.println();
  Serial.println();
  Serial.print("SD card status: "); 
  if (!SD.begin(chipSelect)) {
    Serial.println("FAILED!");
    while(1);
  }
  Serial.println("PASSED!");
  Serial.println();
  Serial.print("Logging to microSD card as ");
  String filename = device + ".csv";
  Serial.println(filename);
  Serial.println();
  
  DateTime now = RTC.now();

  Serial.print("Current time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  Serial.println();
  
  Serial.println("All setup succeed! This device will keep logging data from now on.");
  Serial.println();
  Serial.println();
  
  File dataFile = SD.open(filename.c_str(), FILE_WRITE);
  if (dataFile) {
    dataFile.println("date,time,water_temp,turbidity");
    dataFile.close();
  }
  else {
    Serial.println("[!] File Error");
  }
  waterTempSensor.begin();
}

void loop() {
  // Time
  DateTime now = RTC.now();  
  //Week
  int week = (now.day() + 6) / 7;       
  if (now.dayOfTheWeek() == DAY) {
    if (week == 1 || week == 3 || week == 5) {
      if (now.hour() == START_HH_ODD_WEEK && now.minute() >= START_MM){
        activate_pump_1();
        activate_pump_2();
      } else {
        sleep_mode();
      }
  } else if (week == 2 || week == 4) {
      if (now.hour() == START_HH_EVEN_WEEK && now.minute() >= START_MM){
        activate_pump_1();
        activate_pump_2();
      } else {
        sleep_mode();
      }
    }
  } else {
    sleep_mode();
  }
  log_data();
}

void activate_pump_1(){
  //Serial.println("[!] Pump 1 is running");
  digitalWrite(RELAY_1, HIGH); 
  delay(30000);
  digitalWrite(RELAY_1, LOW);
  //Serial.println("[!] Pump 1 has stopped");
}

void activate_pump_2(){
  //Serial.println("[!] Pump 2 is running");
  digitalWrite(RELAY_2, HIGH);
  delay(30000);
  digitalWrite(RELAY_2, LOW); 
  //Serial.println("[!] Pump 2 has stopped");
}

void deactivate_pumps(){
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
}

void log_data(){
  // Water temperature
  waterTempSensor.requestTemperatures();
  waterTempCelsius = waterTempSensor.getTempCByIndex(0);
  // Water turbidity
  int waterTurbiditySensor = analogRead(waterTurbidityPin);
  float turbidityVoltage = waterTurbiditySensor * (5.0 / 1024.0);
  int turbidity = map(turbidityVoltage,0,4.5,100,0);
  // Time
  DateTime now = RTC.now();
  sprintf(tmeStrng, "%04d/%02d/%02d,%02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second()); 
  String filename = device + ".csv";
  File dataFile = SD.open(filename.c_str(), FILE_WRITE);  // write the data to the SD card:
  if (dataFile) {
    dataFile.print(tmeStrng);
    dataFile.print(",");
    dataFile.print(waterTempCelsius);
    dataFile.print(",");
    dataFile.println(turbidity);
    dataFile.flush(); 
    dataFile.close();
  }
  else {
    Serial.println("[!] File Error");
  } 
}

void sleep_mode(){
  //for (int i = 0; i < 3; i++) {
    //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
  //}
}
