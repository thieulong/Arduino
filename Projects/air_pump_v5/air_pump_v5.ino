#include <Wire.h>
#include "RTClib.h"

#define SUNDAY    0
#define MONDAY    1
#define TUESDAY   2
#define WEDNESDAY 3
#define THURSDAY  4
#define FRIDAY    5
#define SATURDAY  6

// event on Monday and Thursday every week, from 8:00 PM to 8:45 PM
uint8_t WEEKLY_EVENT_DAY_1      = MONDAY;
uint8_t WEEKLY_EVENT_DAY_2      = SATURDAY;
uint8_t WEEKLY_EVENT_START_HH = 16; 
uint8_t WEEKLY_EVENT_START_MM = 45; 
uint8_t WEEKLY_EVENT_END_HH   = 16; 
uint8_t WEEKLY_EVENT_END_MM   = 46 ;

RTC_DS3231 rtc;

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
const int RELAY_3 = A2;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2023, 2, 6, 20, 43   , 0));
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
}

void vacuum_air() {
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, HIGH);
  digitalWrite(RELAY_3, LOW);
}

void pump_air() {
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, HIGH);
  digitalWrite(RELAY_3, HIGH );
}

void stop_pump() {
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, LOW);
}

void clean_cycle() {
  vacuum_air();
  delay(15000);
  stop_pump();
  delay(5000);
  pump_air();
  delay(15000);
  stop_pump();
  delay(5000);
}

void test_cycle() {
  vacuum_air();
  delay(5000);
  stop_pump();
  delay(2000);
  pump_air();
  delay(5000);
  stop_pump();
  delay(2000);
}

//void sleepNow() {
//  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
//  sleep_enable();
//  sleep_mode();
//  sleep_disable();
//}

void loop() {
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(1000);
  if (now.dayOfTheWeek() == WEEKLY_EVENT_DAY_1      ||
      now.dayOfTheWeek() == WEEKLY_EVENT_DAY_2      &&
      now.hour()         >= WEEKLY_EVENT_START_HH &&
      now.minute()       >= WEEKLY_EVENT_START_MM &&
      now.hour()         <=  WEEKLY_EVENT_END_HH   &&
      now.minute()       <  WEEKLY_EVENT_END_MM) {
    //test_cycle();
    clean_cycle();
  }
  test_cycle();
  //LowPower.sleep(SLEEP_1S);
  //sleepNow();
  //rtc.standbyMode(); 
}
