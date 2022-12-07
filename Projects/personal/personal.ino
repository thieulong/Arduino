#include "Arduino_SensorKit.h"

#define button 7

const int light = 3;
int buttonState = 0;
int lightFlag = 0;
int delayval = 500;

void setup() {
  pinMode(light, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  buttonState = digitalRead(button);
  if(buttonState == HIGH){
    if(lightFlag == 0){
      lightFlag = 1;
      digitalWrite(light, HIGH);
    }else{
    lightFlag = 0;
    digitalWrite(light, LOW);
    }
    delay(500); 
  }
}
