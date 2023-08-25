#include <RTClib.h>
#include <avr/sleep.h>

RTC_DS3231 rtc;

const int RELAY1_PIN = A0;
const int RELAY2_PIN = A1;

const int ON_TIME = 25000; // 25 seconds
const int OFF_TIME = 5000; // 5 seconds

bool relay1_state = false;
bool relay2_state = false;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  
  rtc.begin();
  //rtc.adjust(DateTime(__DATE__, __TIME__));
  
  set_sleep_mode(SLEEP_MODE_IDLE);
}

void loop() {
  DateTime now = rtc.now();
  // Check if it's time to activate the relays
  if (now.dayOfTheWeek() == 1 || now.dayOfTheWeek() == 4) {
    Serial.println("[INFO] Correct date!");
    if (now.hour() == 16 && now.minute() == 21) {
      Serial.println("[INFO] Pump activated!");
      activate_relays();
    } else if (now.hour() == 16 && now.minute() == 22) {
      stop_relays();
    }
  }
  
  // Enter sleep mode until next RTC interrupt
  sleep_mode();
}

void activate_relays() {
  int elapsed_time = 0;
  
  while (elapsed_time < 3600000) {
    digitalWrite(RELAY1_PIN, HIGH);
    relay1_state = true;
    delay(ON_TIME);
    
    digitalWrite(RELAY1_PIN, LOW);
    relay1_state = false;
    delay(OFF_TIME);
    
    digitalWrite(RELAY2_PIN, HIGH);
    relay2_state = true;
    delay(ON_TIME);
    
    digitalWrite(RELAY2_PIN, LOW);
    relay2_state = false;
    delay(OFF_TIME);
    
    elapsed_time += ON_TIME + OFF_TIME;
  }
}

void stop_relays() {
  digitalWrite(RELAY1_PIN, LOW);
  digitalWrite(RELAY2_PIN, LOW);
  relay1_state = false;
  relay2_state = false;
}
