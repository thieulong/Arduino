#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

#define SUNDAY    0
#define MONDAY    1
#define TUESDAY   2
#define WEDNESDAY 3
#define THURSDAY  4
#define FRIDAY    5
#define SATURDAY  6

uint8_t WEEKLY_EVENT_DAY_1    = WEDNESDAY;
uint8_t WEEKLY_EVENT_DAY_2    = MONDAY;
uint8_t WEEKLY_EVENT_START_HH = 8; 
uint8_t WEEKLY_EVENT_START_MM = 0; 
uint8_t WEEKLY_EVENT_END_HH   = 9; 
uint8_t WEEKLY_EVENT_END_MM   = 1;

char daysOfTheWeek[7][12] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

const int RELAY_1 = A0;
const int RELAY_2 = A1;

void setup() {
  
  Serial.begin(9600);
  while (!Serial); 

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
}

void vacuum_air() {
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, LOW);
}

void pump_air() {
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, HIGH);
}

void stop_pump() {
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
}

void clean_cycle() {
  vacuum_air();
  delay(25000);
  stop_pump();
  delay(5000);
  pump_air();
  delay(25000);
  stop_pump();
  delay(5000);
}

void test_cycle() {
  vacuum_air();
  delay(5000);
  stop_pump();
  delay(5000);
  pump_air();
  delay(5000);
  stop_pump();
  delay(5000);
}


void loop() {
  DateTime now = rtc.now();
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
  delay(1000);
  if (now.dayOfTheWeek() == WEEKLY_EVENT_DAY_1    &&
      now.hour()         >= WEEKLY_EVENT_START_HH &&
      now.minute()       >= WEEKLY_EVENT_START_MM &&
      now.hour()         <=  WEEKLY_EVENT_END_HH   &&
      now.minute()       <  WEEKLY_EVENT_END_MM) {
      Serial.println("Event triggered!");
      //test_cycle();
      clean_cycle();
  }
  if (now.dayOfTheWeek() == WEEKLY_EVENT_DAY_2    &&
      now.hour()         >= WEEKLY_EVENT_START_HH &&
      now.minute()       >= WEEKLY_EVENT_START_MM &&
      now.hour()         <=  WEEKLY_EVENT_END_HH   &&
      now.minute()       <  WEEKLY_EVENT_END_MM) {
      Serial.println("Event triggered!");
      //test_cycle();
      clean_cycle();
  } 
}
