#define RELAY_1  4  // the Arduino pin, which connects to the relay 1
#define RELAY_2  7  // the Arduino pin, which connects to the relay 2
#define RELAY_3  8  // the Arduino pin, which connects to the relay 3
#define RELAY_4  12 // the Arduino pin, which connects to the relay 4

void setup() {
  Serial.begin(9600);

  // initialize Arduino pins as digital output pins
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, HIGH);
  digitalWrite(RELAY_4, HIGH);
  delay(5000);

  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, LOW);
  digitalWrite(RELAY_4, LOW);
  delay(3000);
  
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, HIGH);
  digitalWrite(RELAY_3, LOW);
  digitalWrite(RELAY_4, HIGH);
  delay(4000);
}
           
