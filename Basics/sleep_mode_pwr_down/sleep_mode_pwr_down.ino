#include <avr/sleep.h>
#include <LowPower.h>

void setup() {
  // Set up any necessary pins or peripherals here
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Do any necessary processing here
  
  // Put the Nano to sleep
  //set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Choose a sleep mode (in this case, the deepest sleep mode)
  //sleep_enable(); // Enable sleep mode
  //sleep_mode(); // Put the Nano to sleep
  //sleep_disable(); // Disable sleep mode when waking up
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 
}
