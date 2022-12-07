void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {  // check for incoming serial data
      String command = Serial.readString();  // read command from serial port
      if (command == "led_on") {  // turn on LED
         digitalWrite(LED_BUILTIN, HIGH);
      } else if (command == "led_off") {  // turn off LED
         digitalWrite(LED_BUILTIN, LOW);
      } else if (command == "read_a0") {  // read and send A0 analog value
         Serial.println(analogRead(A0));
      }
   }
}
