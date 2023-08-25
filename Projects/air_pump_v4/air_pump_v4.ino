#include <Wire.h>
#include <Adafruit_BMP085.h>

#define RELAY_1  4  // the Arduino pin, which connects to the relay 1
#define RELAY_2  7  // the Arduino pin, which connects to the relay 2
#define RELAY_3  8  // the Arduino pin, which connects to the relay 3
#define RELAY_4  12 // the Arduino pin, which connects to the relay 4

#define BUTTON_PIN A1

Adafruit_BMP085 bmp;
long standardAirPressure;
  
void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
  Serial.println("[!] Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
  pinMode(BUTTON_PIN, INPUT);
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);
  standardAirPressure = bmp.readPressure();
}

int measure_methane() {
  int methaneLevel;
  methaneLevel=analogRead(0);
  Serial.print("Methane Level:");
  Serial.println(methaneLevel,DEC);
  return methaneLevel;
}

int measure_pressure() {
  long airPressure;
  airPressure=bmp.readPressure();
  Serial.print("Air Pressure (Pa): ");
  Serial.println(airPressure);
  return airPressure;
}

void pump_air() {
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_3, HIGH);
  digitalWrite(RELAY_4, HIGH);
}

void vacuum_air() {
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_3, HIGH);
  digitalWrite(RELAY_4, LOW);
}

void cycle_air() {
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_3, HIGH);
  digitalWrite(RELAY_4, LOW);
}

void stop_pump() {
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_3, LOW);
  digitalWrite(RELAY_4, LOW);
}

void fan_on() {
  digitalWrite(RELAY_2, HIGH);
}

void fan_off() {
  digitalWrite(RELAY_2, LOW);
}

void test() {
  Serial.println("[TEST] Vacuuming Air ...");
  vacuum_air();
  delay(3000);
  Serial.println("[TEST] Stop pump");
  stop_pump();
  delay(3000);
  Serial.println("[TEST] Pumping Air ...");
  pump_air();
  delay(3000);
  Serial.println("[TEST] Stop pump");
  stop_pump();
  delay(3000);
  Serial.println("[TEST] Fan on");
  fan_on();
  delay(3000);
  Serial.println("[TEST] Fan off!");
  fan_off();
}

void air_recycle() {
  // Vacuuming Air Out
  fan_off();
  Serial.println("[!] Vacuuming Air");
  vacuum_air();
  delay(15000);
  measure_methane();
  measure_pressure();
  // Stop
  stop_pump();
  // Activate Fan
  fan_on();
  delay(5000);
  measure_methane();
  measure_pressure();
  // Pumping Air In
  fan_off();
  Serial.println("[!] Pumping Air");
  pump_air();
  delay(15000);
  measure_methane();
  measure_pressure();
  // Stop
  stop_pump();
}

void loop() {
  Serial.println("--------------------");
  int methaneLevel = measure_methane();
  long airPressure = measure_pressure();
  int lowerBoundPressure = standardAirPressure - 50;
  int upperBoundPressure = standardAirPressure + 50;
  Serial.print("Standard Air Pressure (Pa): ");
  Serial.println(standardAirPressure);
  delay(1000);
  if (digitalRead(BUTTON_PIN) == LOW) {
    test();
  }
  if (methaneLevel>=10) {
    air_recycle();
  } else if (airPressure<lowerBoundPressure) {
    Serial.println("[!] Air Pressure Low!");
    fan_on();
    delay(5000);
    fan_off();
  } else if (airPressure>upperBoundPressure) {
    Serial.println("[!] Air Pressure High!");
    vacuum_air();
    delay(5000);
    stop_pump();
  } else {
    fan_off();
    stop_pump();
  }
}
           
