const int sensorPin = A4; 
float voltage;
float current;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect
  }
  Serial.println("Starting...");
}

void loop() {
  voltage = (analogRead(sensorPin) / 1024.0) * 5.0;
  current = (voltage - 2.5) / 0.066;
  
  Serial.print(voltage);
  Serial.print(",");
  Serial.println(current);
  delay(1000);
}
