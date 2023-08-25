#define BUTTON_BLUE 2
#define BUTTON_GREEN 3
#define BUTTON_RED 4

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_RED, INPUT_PULLUP);
}

void loop()
{
  byte buttonBlue = digitalRead(BUTTON_BLUE);
  byte buttonGreen = digitalRead(BUTTON_GREEN);
  byte buttonRed = digitalRead(BUTTON_RED);
  
  if (buttonBlue == LOW) {
      Serial.println("Blue button is pressed");
  } else if (buttonGreen == LOW) {
      Serial.println("Green button is pressed");
  } else if (buttonRed == LOW) {
      Serial.println("Red button is pressed");
  }
  delay(100);
}
