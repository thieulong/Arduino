const int RELAY1_PIN = A0; // Relay 1 connected to A0
const int RELAY2_PIN = A1; // Relay 2 connected to A1
const int ON_TIME = 5000; // Relay on time in milliseconds (20 seconds)
const int OFF_TIME = 5000; // Relay off time in milliseconds (10 seconds)

void setup() {
  pinMode(RELAY1_PIN, OUTPUT); // Set Relay 1 pin as output
  pinMode(RELAY2_PIN, OUTPUT); // Set Relay 2 pin as output
}

void loop() {
  // Turn on Relay 1 and wait for ON_TIME milliseconds
  digitalWrite(RELAY1_PIN, HIGH);
  delay(ON_TIME);
  
  // Turn off Relay 1 and wait for OFF_TIME milliseconds
  digitalWrite(RELAY1_PIN, LOW);
  delay(OFF_TIME);
  
  // Turn on Relay 2 and wait for ON_TIME milliseconds
  digitalWrite(RELAY2_PIN, HIGH);
  delay(ON_TIME);
  
  // Turn off Relay 2 and wait for OFF_TIME milliseconds
  digitalWrite(RELAY2_PIN, LOW);
  delay(OFF_TIME);
}
