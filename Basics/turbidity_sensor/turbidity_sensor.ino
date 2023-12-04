const int relayTurbidityPin = 4;

void setup() {
  Serial.begin(9600); // Baud rate: 9600
  pinMode(relayTurbidityPin, OUTPUT);
}

void loop() {
  digitalWrite(relayTurbidityPin, HIGH);
  delay(2000);
  int sensorValue = analogRead(A3); // Read the input on analog pin A2
  float voltage = sensorValue * (5.0 / 1024.0); // Convert the sensor reading to voltage (0 - 5V)


  // Map the voltage range (0 - 4.5V) to the range (0 - 3500)
  float minVoltage = 0.0;
  float maxVoltage = 4.5;
  int newMinValue = 100;
  int newMaxValue = 0;
  int mappedValue = (voltage - minVoltage) * (newMaxValue - newMinValue) / (maxVoltage - minVoltage) + newMinValue;


  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print("\tVoltage: ");
  Serial.print(voltage, 2);
  Serial.print("V\tMapped Value: ");
  Serial.println(mappedValue);

  digitalWrite(relayTurbidityPin, LOW);
  delay(2000);
}
