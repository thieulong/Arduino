#include <avr/sleep.h>
#include <avr/power.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  // Set the device to sleep mode
  set_sleep_mode(SLEEP_MODE_STANDBY);
  sleep_enable();
  power_all_disable();
  sleep_cpu();

  // The device wakes up here after the sleep period is over
  power_all_enable();
  sleep_disable();
}

.
