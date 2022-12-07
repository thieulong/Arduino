#define PIR_MOTION_SENSOR 2
#include <Servo.h>

Servo servo;

int pos = 0; 
 
void setup()
{
    pinMode(PIR_MOTION_SENSOR, INPUT);
    servo.attach(9);
    Serial.begin(9600);  
}
 
void loop()
{
    if(digitalRead(PIR_MOTION_SENSOR)){
        Serial.println("Movement detected!");
        servo.write(75);
    }else{
        Serial.println("Waiting ...");
        servo.write(0);
    }
 delay(10);
}
