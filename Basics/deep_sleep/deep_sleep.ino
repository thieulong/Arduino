#include <LowPower.h>
#include <avr/sleep.h>

void setup() {
  CLKPR = 0x80;
  CLKPR = 0x04;
//  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
//  digitalWrite(LED_BUILTIN, HIGH);
//  delay(1000);
//  digitalWrite(LED_BUILTIN, LOW);
//  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu();
}
