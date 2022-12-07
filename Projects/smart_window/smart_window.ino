#include <AFMotor.h>
#include <Servo.h>
//#include "SD.h"
//#include <Wire.h>
//#include "RTClib.h"

//#define LOG_INTERVAL  1000
//#define SYNC_INTERVAL 1000
//uint32_t syncTime = 0;

// Data logging shield
//const int chipSelect = 10;
//File logfile;

// RTC
//RTC_DS1307 RTC;

// Light sensor
int light_sensor = A0; 
int light;

// Rain sensor
int rain_sensor = A1;
int rain;

// Window & Curtain status
int windowStatus;
int curtainStatus;

// Light and Rain threshold
int lightThreshold = 1;
int rainThreshold = 1;

// DC motor 
AF_DCMotor dc_motor(1, MOTOR12_64KHZ);
int motorFlag = 0;

// Servo motor 
Servo servo1;
Servo servo2;
int servoFlag = 0;

void setup() {
  
  Serial.begin(9600);

//  initSDcard();
//  
//  createFile();
//
//  initRTC();
//
//  logfile.println("millis,stamp,datetime,light,rain,window,curtain");
  Serial.println("millis,stamp,datetime,light,rain,window,curtain");

  dc_motor.setSpeed(80);

  servo1.attach(9);
  servo2.attach(10);
  
}

void loop() {
//  DateTime now;
//  delay((LOG_INTERVAL - 1) - (millis() % LOG_INTERVAL));
//
//  uint32_t m = millis();
//  logfile.print(m);           
//  logfile.print(", ");
//  
//  now = RTC.now();
//
//  logfile.print(now.unixtime()); 
//  logfile.print(", ");
//  logfile.print(now.year(), DEC);
//  logfile.print("/");
//  logfile.print(now.month(), DEC);
//  logfile.print("/");
//  logfile.print(now.day(), DEC);
//  logfile.print(" ");
//  logfile.print(now.hour(), DEC);
//  logfile.print(":");
//  logfile.print(now.minute(), DEC);
//  logfile.print(":");
//  logfile.print(now.second(), DEC);

  int raw_light = analogRead(light_sensor); 
  int light = map(raw_light, 0, 1023, 0, 10); 

  int raw_rain = analogRead(rain_sensor);
  int rain = map(raw_rain, 0, 1023, 0, 10);

//  logfile.print(", ");
//  logfile.print(light);
//  logfile.print(", ");
//  logfile.print(rain);
// 
  Serial.print(", "); 
  Serial.print(light); 
  Serial.print(", ");
  Serial.print(rain);

   if(rain < rainThreshold) {
      // Not raining
      if (light > lightThreshold){
        // Daytime
        openWindow();
        windowStatus = 1;
        delay(500);
        if (motorFlag == 0){
          openCurtain();
          stopCurtain();
          curtainStatus = 1;
          motorFlag++;
        }
      }else{
        // Nighttime
        if (motorFlag == 1){
          closeCurtain();
          stopCurtain();
          curtainStatus = 0;
          motorFlag--;
        }
        closeWindow();
        windowStatus = 0;
        delay(500);
      }
   }else{
      // Raining
      windowStatus = 0;
      closeWindow();
      delay(500);
   }

//  logfile.print(", ");
//  logfile.print(windowStatus);
//  logfile.print(", ");
//  logfile.println(curtainStatus);

  Serial.print(", "); 
  Serial.print(windowStatus); 
  Serial.print(", ");
  Serial.println(curtainStatus);

//   if ((millis() - syncTime) < SYNC_INTERVAL) return;
//   syncTime = millis();
//
//   logfile.flush();
}

void openWindow() {
  servo1.write(0);
  servo2.write(180);
}

void closeWindow() {
  servo1.write(90);
  servo2.write(90);
}

void openCurtain() {
  dc_motor.run(FORWARD);
  delay(400);
}

void closeCurtain() {
  dc_motor.run(BACKWARD);
  delay(300);
}

void stopCurtain() {
  dc_motor.run(RELEASE);
}

//void error(char const *str)
//{
//  Serial.print("error: ");
//  Serial.println(str);
//
//  while (1);
//}
//
//void initSDcard()
//{
//  Serial.print("Initializing SD card...");
//  pinMode(10, OUTPUT);
//  if (!SD.begin(chipSelect)) {
//    Serial.println("Card failed, or not present");
//    return;
//  }
//  Serial.println("card initialized.");
//
//}
//
//void createFile()
//{
//  char filename[] = "MLOG00.CSV";
//  for (uint8_t i = 0; i < 100; i++) {
//    filename[4] = i / 10 + '0';
//    filename[5] = i % 10 + '0';
//    if (! SD.exists(filename)) {
//      logfile = SD.open(filename, FILE_WRITE);
//      break;  
//    }
//  }
//
//  if (! logfile) {
//    error("Couldnt create file");
//  }
//
//  Serial.print("Logging to: ");
//  Serial.println(filename);
//}
//
//void initRTC()
//{
//  Wire.begin();
//  if (!RTC.begin()) {
//    logfile.println("RTC failed");
//    Serial.println("RTC failed");
//  }
//}
