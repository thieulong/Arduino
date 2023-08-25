#include <avr/sleep.h>
#include <avr/power.h>

const int interruptPin = 2; // RTC alarm interrupt pin
volatile bool wokeUp = false; // flag to indicate whether the Arduino woke up

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set the interrupt pin as input and enable the internal pull-up resistor
  pinMode(interruptPin, INPUT_PULLUP);
  
  // Enable the RTC alarm interrupt
  attachInterrupt(digitalPinToInterrupt(interruptPin), wakeUpHandler, FALLING);
  
  // Set the sleep mode to power-save mode
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);
}

void loop() {
  if (wokeUp) {
    // Arduino woke up from sleep, do your task here
    Serial.println("Woke up!");
    delay(1000);
    // Clear the flag
    wokeUp = false;
    
    // Put the Arduino back to sleep
    sleep_mode();
  }
}

void wakeUpHandler() {
  // Interrupt handler for RTC alarm
  wokeUp = true;
  
  // Disable power reduction for all peripherals to ensure they're operational after waking up
  power_all_enable();
}
