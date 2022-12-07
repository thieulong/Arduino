#include "LedControl.h"
#include "binary.h"

/*
 Left LED Matrix
 DIN - pin 13
 CS - pin 12
 CLK - pin 11
 
 Right LED Matrix
 DIN - pin 10
 CS - pin 9
 CLK - pin 8
*/

LedControl leftLED = LedControl(13,11,12,1);
LedControl rightLED = LedControl(10,8,9,1);

byte mood[8];

byte neutral[8]= {B00111100,B01000010,B10000001,B10011001,B10011001,B10000001,B01000010,B00111100};
byte blinking[8] = {B00000000,B00011000,B00011000,B00011000,B00011000,B00011000,B00011000,B00000000};
byte lookingLeft[8] = {B00111100,B01000010,B10011001,B10011001,B10000001,B10000001,B01000010,B00111100};
byte lookingRight[8] = {B00111100,B01000010,B10000001,B10000001,B10011001,B10011001,B01000010,B00111100};
byte lookingUp[8] = {B00111100,B01000010,B10000001,B10110001,B10110001,B10000001,B01000010,B00111100};
byte lookingDown[8] = {B00111100,B01000010,B10000001,B10001101,B10001101,B10000001,B01000010,B00111100};
byte eyebrownUpHigh[8] = {B00000000,B00001000,B00000100,B00000100,B00000100,B00000100,B00001000,B00000000};
byte eyebrownUpLow[8] = {B00000000,B00000100,B00000010,B00000010,B00000010,B00000010,B00000100,B00000000};
byte eyebrownDownHigh[8] = {B00000000,B00010000,B00100000,B00100000,B00100000,B00100000,B00010000,B00000000};
byte eyebrownDownLow[8] = {B00000000,B00100000,B01000000,B01000000,B01000000,B01000000,B00100000,B00000000};

void setup() {
  leftLED.shutdown(0,false);
  rightLED.shutdown(0,false);
  
  leftLED.setIntensity(0,8);
  rightLED.setIntensity(0,8);
  
  leftLED.clearDisplay(0);  
  rightLED.clearDisplay(0); 
}

void eyeExpression(char mood[]){
  leftLED.setRow(0,0,mood[0]);
  leftLED.setRow(0,1,mood[1]);
  leftLED.setRow(0,2,mood[2]);
  leftLED.setRow(0,3,mood[3]);
  leftLED.setRow(0,4,mood[4]);
  leftLED.setRow(0,5,mood[5]);
  leftLED.setRow(0,6,mood[6]);
  leftLED.setRow(0,7,mood[7]);

  rightLED.setRow(0,0,mood[0]);
  rightLED.setRow(0,1,mood[1]);
  rightLED.setRow(0,2,mood[2]);
  rightLED.setRow(0,3,mood[3]);
  rightLED.setRow(0,4,mood[4]);
  rightLED.setRow(0,5,mood[5]);
  rightLED.setRow(0,6,mood[6]);
  rightLED.setRow(0,7,mood[7]);
}

void neutralMood(){
  eyeExpression(neutral);
  delay(1000);
  eyeExpression(blinking);
  delay(200);
  eyeExpression(neutral);
  delay(2000);
  eyeExpression(blinking);
  delay(200);
  eyeExpression(neutral);
  delay(500);
  eyeExpression(blinking);
  delay(100);
  eyeExpression(neutral);
  delay(100);
  eyeExpression(blinking);
  delay(100);
  eyeExpression(neutral);
  delay(500);
  eyeExpression(lookingLeft);
  delay(1000);
  eyeExpression(lookingRight);
  delay(1000);
  eyeExpression(neutral);
  delay(500);
  eyeExpression(blinking);
  delay(100);
  eyeExpression(neutral);
  delay(500);
  eyeExpression(lookingUp);
  delay(750);
  eyeExpression(lookingDown);
  delay(750);
  eyeExpression(neutral);
  delay(200);
  eyeExpression(blinking);
  delay(100);
}

void happyMood(){
  eyeExpression(eyebrownUpHigh);
  delay(100);
  eyeExpression(eyebrownUpLow);
  delay(100);
}

void sleepingMood(){
  eyeExpression(eyebrownDownHigh);
  delay(2000);
  eyeExpression(eyebrownDownLow);
  delay(2000);
}

void loop(){
  neutralMood();
  //happyMood();
  ///sleepingMood();
}
