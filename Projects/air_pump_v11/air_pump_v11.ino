#include <SdFat.h>
#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SUNDAY    0
#define MONDAY    1 
#define TUESDAY   2
#define WEDNESDAY 3
#define THURSDAY  4
#define FRIDAY    5
#define SATURDAY  6

char daysOfTheWeek[7][12] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

RTC_DS1307 RTC;          
#define DS1307_I2C_ADDRESS 0x68
SdFat SD;            
const int chipSelect = 10;
char tmeStrng[] = "0000/00/00,00:00:00";
const String device = "Pondi_1";

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

  // SD Card initialization
  Serial.print("SD card status: ");
  if (!SD.begin(chipSelect)) {
    Serial.println("FAILED!");
    while (1);
  }
  Serial.println("PASSED!");

  // Logging header
  Serial.print("Logging to microSD card as ");
  String filename = device + ".csv";
  Serial.println(filename);
  Serial.println();

  Serial.println("Date|Time|Water Temperature|Turbidity");
  Serial.println();

  File dataFile = SD.open(filename.c_str(), FILE_WRITE);
  if (dataFile) {
    dataFile.print("Blue Carbon Lab - ");
    dataFile.print(device);
    dataFile.println("date,time,water_temp,turbidity");
    dataFile.close();
  } else {
    Serial.println("[!] File Error");
  }

  waterTempSensor.begin();
}

void loop() {
  DateTime now = RTC.now();
  int week = (now.day() + 6) / 7;

  // Water temperature
  waterTempSensor.requestTemperatures();
  waterTempCelsius = waterTempSensor.getTempCByIndex(0);

  // Water turbidity
  int waterTurbiditySensor = analogRead(waterTurbidityPin);
  float turbidityVoltage = waterTurbiditySensor * (5.0 / 1024.0);
  int turbidity = map(turbidityVoltage, 0, 4.5, 100, 0);

  // Logging data
  logData(now, waterTempCelsius, turbidity);

  // Check pump activation time
  if (isPumpActivationTime(now, week)) {
    runPumps();
  }
}

void logData(DateTime now, float waterTemp, int turbidity) {
  char tmeStrng[] = "0000/00/00,00:00:00";
  sprintf(tmeStrng, "%04d/%02d/%02d,%02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  String filename = device + ".csv";
  File dataFile = SD.open(filename.c_str(), FILE_WRITE);
  if (dataFile) {
    dataFile.print(tmeStrng);
    dataFile.print(",");
    dataFile.print(waterTemp);
    dataFile.print(",");
    dataFile.println(turbidity);
    dataFile.flush();
    dataFile.close();

    Serial.print(tmeStrng);
    Serial.print(",");
    Serial.print(waterTemp);
    Serial.print(",");
    Serial.println(turbidity);
  } else {
    Serial.println("[!] File Error");
  }
}

bool isPumpActivationTime(DateTime now, int week) {
  if (week == 1 || week == 3 || week == 5) {
    return (now.dayOfTheWeek() == MONDAY && now.hour() == 2 && now.minute() == 0);
  } else if (week == 2 || week == 4) {
    return (now.dayOfTheWeek() == MONDAY && now.hour() == 2 && now.minute() == 0);
  }
  return false;
}

void runPumps() {
  unsigned long startTime = millis();
  unsigned long pumpDuration = 20000; // Duration for each pump (in milliseconds)
  unsigned long pumpInterval = 10000; // Interval between pump switches (in milliseconds)

  while (millis() - startTime < 3600000) { // Run for 1 hour
    Serial.println("[!] Air Pump 1 is running!");
    digitalWrite(RELAY_1, HIGH); // Activate pump 1
    delay(pumpDuration);
    Serial.println("[!] Air Pump 1 stopped!");
    digitalWrite(RELAY_1, LOW); // Turn off pump 1
    delay(pumpInterval);
    Serial.println("[!] Air Pump 2 is running!");
    digitalWrite(RELAY_2, HIGH); // Activate pump 2
    delay(pumpDuration);
    Serial.println("[!] Air Pump 2 is stopped!");
    digitalWrite(RELAY_2, LOW); // Turn off pump 2
    delay(pumpInterval);
  }
  Serial.println("[!] Both Air Pumps have stopped!");
  digitalWrite(RELAY_1, LOW); // Ensure pumps are off after 1 hour
  digitalWrite(RELAY_2, LOW);
  delay(5000); // A short delay after pumps stop before the Arduino sleeps again
}
