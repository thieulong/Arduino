/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-ds1307-rtc-module
 */

// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <RTClib.h>

// UNCHANGABLE PARAMATERS
#define SUNDAY    0
#define MONDAY    1
#define TUESDAY   2
#define WEDNESDAY 3
#define THURSDAY  4
#define FRIDAY    5
#define SATURDAY  6

// event on Monday, from 13:50 to 14:10
uint8_t WEEKLY_EVENT_DAY_2      = MONDAY;
uint8_t WEEKLY_EVENT_DAY_1      = SATURDAY;
uint8_t WEEKLY_EVENT_START_HH = 23; // event start time: hour
uint8_t WEEKLY_EVENT_START_MM = 51; // event start time: minute
uint8_t WEEKLY_EVENT_END_HH   = 23; // event end time: hour
uint8_t WEEKLY_EVENT_END_MM   = 52; // event end time: minute

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

void setup () {
  Serial.begin(9600);

  // SETUP RTC MODULE
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // sets the RTC to the date & time on PC this sketch was compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // sets the RTC with an explicit date & time, for example to set
  // January 21, 2021 at 3am you would call:
  // rtc.adjust(DateTime(2021, 1, 21, 3, 0, 0));

}

void loop () {
  DateTime now = rtc.now();
  if (now.dayOfTheWeek() == WEEKLY_EVENT_DAY_1      ||
      now.dayOfTheWeek() == WEEKLY_EVENT_DAY_2      &&
      now.hour()         >= WEEKLY_EVENT_START_HH &&
      now.minute()       >= WEEKLY_EVENT_START_MM &&
      now.hour()         <=  WEEKLY_EVENT_END_HH   &&
      now.minute()       <  WEEKLY_EVENT_END_MM) {
    Serial.println("It is on scheduled time");
    Serial.println("----------------------------------");
  } else {
    Serial.println("It is NOT on scheduled time");
  }
  printTime(now);
  Serial.println(WEEKLY_EVENT_DAY_1);
  delay(1000);
}

void printTime(DateTime time) {
  Serial.print("TIME: ");
  Serial.print(time.year(), DEC);
  Serial.print('/');
  Serial.print(time.month(), DEC);
  Serial.print('/');
  Serial.print(time.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[time.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(time.hour(), DEC);
  Serial.print(':');
  Serial.print(time.minute(), DEC);
  Serial.print(':');
  Serial.println(time.second(), DEC);
}
