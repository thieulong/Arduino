#include "Arduino_SensorKit.h"

void setup() {
  Oled.begin();
  Oled.setFlipMode(true);
  Environment.begin();
}

void loop() {
  int random_value = random(0, 1023);   // create a random value

  Oled.setFont(u8x8_font_chroma48medium8_r); 
  Oled.setCursor(0, 0);
  Oled.print("Temperature:\n\n");
  Oled.print(Environment.readTemperature());
  Oled.print(" C");
  Oled.print("\n\nHumidity:\n\n");
  Oled.print(Environment.readHumidity()); 
  Oled.println(" %");
  delay(1000);

}
