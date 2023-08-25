#define BUTTON_PIN 8

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("Button pressed!");
  }
  else {
    Serial.println("...");
  } 
  delay(500);
}
