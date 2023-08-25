#define VALVE_IN_PUMP 4
#define VALVE_MID_PUMP 7
#define VALVE_OUT_PUMP 8
#define AIR_PUMP 12

void setup() {
  pinMode(AIR_PUMP, OUTPUT);
  pinMode(VALVE_OUT_PUMP, OUTPUT);
  pinMode(VALVE_MID_PUMP, OUTPUT);
  pinMode(VALVE_IN_PUMP, OUTPUT);
}
// Air Pump
void activate_air_pump() {
  digitalWrite(AIR_PUMP, HIGH);
}

void deactivate_air_pump() {
  digitalWrite(AIR_PUMP, LOW);
}
// Air valve OUT
void activate_air_valve_out() {
  digitalWrite(VALVE_OUT_PUMP, HIGH);
}

void deactivate_air_valve_out() {
  digitalWrite(VALVE_OUT_PUMP, LOW); 
}
// Air valve MID
void activate_air_valve_mid() {
  digitalWrite(VALVE_MID_PUMP, HIGH);
}

void deactivate_air_valve_mid() {
  digitalWrite(VALVE_MID_PUMP, LOW);
}
// Air valve IN
void activate_air_valve_in() {
  digitalWrite(VALVE_IN_PUMP, HIGH);
}

void deactivate_air_valve_in() {
  digitalWrite(VALVE_IN_PUMP, LOW);
}

void loop() {
  /*
  //Air pump
  activate_air_pump();
  delay(2000);
  deactivate_air_pump();
  delay(2000);
  // Air valve OUT
  activate_air_valve_out();
  delay(2000);
  deactivate_air_valve_out();
  delay(2000);
  // Air valve MID
  activate_air_valve_mid();
  delay(2000);
  deactivate_air_valve_mid();
  delay(2000);
  // Air valve IN
  activate_air_valve_in();
  delay(2000);
  deactivate_air_valve_in();
  delay(2000); 
  */

  // Vacuum Air Out
  digitalWrite(AIR_PUMP, HIGH);
  digitalWrite(VALVE_IN_PUMP, LOW);
  digitalWrite(VALVE_MID_PUMP, LOW);
  digitalWrite(VALVE_OUT_PUMP, HIGH);
//  activate_air_pump();
//  deactivate_air_valve_in();
//  deactivate_air_valve_mid();
//  activate_air_valve_out();
  delay(5000);
 
  // Stop 
  digitalWrite(AIR_PUMP, LOW);
  digitalWrite(VALVE_IN_PUMP, LOW);
  digitalWrite(VALVE_MID_PUMP, LOW);
  digitalWrite(VALVE_OUT_PUMP, LOW);
//  deactivate_air_pump();
//  deactivate_air_valve_in();
//  deactivate_air_valve_mid();
//  deactivate_air_valve_out();
  delay(5000);
 
  // Pumping Air In
  digitalWrite(AIR_PUMP, HIGH);
  digitalWrite(VALVE_IN_PUMP, HIGH);
  digitalWrite(VALVE_MID_PUMP, HIGH);
  digitalWrite(VALVE_OUT_PUMP, LOW);
//  activate_air_pump();
//  activate_air_valve_in();
//  activate_air_valve_mid();
//  deactivate_air_valve_out();
  delay(5000);
 
}
