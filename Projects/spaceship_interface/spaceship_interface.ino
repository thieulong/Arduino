int green = 3;
int red1 = 4;
int red2 = 5;
int switchState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(green, OUTPUT);
  pinMode(red1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  switchState = digitalRead(2);
  if (switchState == LOW){
    digitalWrite(green, HIGH);
    digitalWrite(red1, LOW);
    digitalWrite(red2, LOW);
  }
  else{
    digitalWrite(green, LOW);
    digitalWrite(red1, LOW);
    digitalWrite(red2, HIGH);
    delay(250);
    digitalWrite(red1, HIGH);
    digitalWrite(red2, LOW);
    delay(250);
  }
}
