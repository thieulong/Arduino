#include <AFMotor.h> 
AF_DCMotor motor(1, MOTOR12_64KHZ);

void setup() {
  // put your setup code here, to run once:
  motor.setSpeed(40);
}

void loop() {
  // put your main code here, to run repeatedly:
  runForward();       
  stopRunning();       
  delay(1000); 
  runBackward();      
  stopRunning();       
  delay(1000); 
}

void runForward() {
  motor.run(FORWARD); 
  delay(750);
}

void runBackward() {
  motor.run(BACKWARD);
  delay(750);
}

void stopRunning() {
  motor.run(RELEASE);
}
