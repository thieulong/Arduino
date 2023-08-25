// 2x Air Pump Relay
const int AIR_PUMP = 3;
const int VALVE_PUMP = 5; 

void setup() {
  pinMode(AIR_PUMP, OUTPUT);
  pinMode(VALVE_PUMP, OUTPUT);
}

void activate_air_pump() {
  digitalWrite(AIR_PUMP, HIGH);
}

void deactivate_air_pump() {
  digitalWrite(AIR_PUMP, LOW);
}

void activate_air_valve() {
  digitalWrite(VALVE_PUMP, HIGH);
}

void deactivate_air_valve() {
  digitalWrite(VALVE_PUMP, LOW);
}

void loop() {
  // Vacuum Air
  activate_air_pump();
  delay(5000);
  deactivate_air_pump();
  delay(2000);
  // Pump Air
  activate_air_valve();
  activate_air_pump();
  delay(5000);
  deactivate_air_valve();
  deactivate_air_pump();
  delay(2000);
}
