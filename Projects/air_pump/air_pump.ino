#include <Wire.h>
#include "rgb_lcd.h"
#include <SPL06-007.h>

// 2x Air Pump Relay
const int IN_PUMP = 3;
const int OUT_PUMP = 5; 

// 16x2 LCD Screen
rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

void setup() {
  Wire.begin();
  SPL_init();
  
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  
  pinMode(IN_PUMP, OUTPUT);
  pinMode(OUT_PUMP, OUTPUT);
}

void pump_air() {
  digitalWrite(IN_PUMP, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("Pumping Air...");
}

void vacuum_air() {
  digitalWrite(OUT_PUMP, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("Vacuuming Air...");
}

void stop_pump() {
  digitalWrite(IN_PUMP, LOW);
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void stop_vacuum() {
  digitalWrite(OUT_PUMP, LOW);
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Pressure:");
  lcd.setCursor(9, 0);
  lcd.print(get_pressure(),1);
  vacuum_air(); 
  delay(3000);
  stop_vacuum();
  delay(3000);
  pump_air(); 
  delay(10000);
  stop_pump(); 
  delay(5000);
}
