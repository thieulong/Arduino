#include <Wire.h>
#include "MMA7660.h"
#include <Servo.h>

MMA7660 accelemeter;
Servo myservo;

int pos = 90;

void setup() {
    accelemeter.init();
    myservo.attach(9);
    Serial.begin(9600);
}

void loop() {
    int8_t x;
    int8_t y;
    int8_t z;
    float ax, ay, az;
    accelemeter.getXYZ(&x, &y, &z);

    Serial.print("x = ");
    Serial.println(x);
    Serial.print("y = ");
    Serial.println(y);
    Serial.print("z = ");
    Serial.println(z);
    Serial.println("----------");
    
    if (y<3 && y>-3){
      if (pos>89){
        pos -= 1;
        myservo.write(pos);
      } else if (pos<91){
        pos += 1;
        myservo.write(pos);
      }
    } if (y>=3 && y<=5){
        if (pos<135){
          pos += 1;
          myservo.write(pos);
      } else if (pos>135){
          pos -= 1;
          myservo.write(pos);
      }
    } if (y>5){
        if (pos<181){
          pos += 1;
          myservo.write(pos);
      }
    } if (y<=-3 && y>=-5){
        if (pos<45){
          pos += 1;
          myservo.write(pos);
      } else if (pos>45){
          pos -= 1;
          myservo.write(pos);
      }
    } if (y<-5){
        if (pos>-1){
          pos -= 1;
          myservo.write(pos);
        }
    }
    delay(1000);
}
