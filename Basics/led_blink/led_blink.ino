#define LED 8 // the pin the LED is connected to

void setup() {
  pinMode(LED, OUTPUT); // Declare the LED as an output
}

void loop() {
  digitalWrite(LED, HIGH); // Turn the LED on
  delay(1000); // Wait for 1000 milliseconds (1 second)
  digitalWrite(LED, LOW); // Turn the LED off
  delay(1000); // Wait for 1000 milliseconds (1 second)
}
