#include <AFMotor.h>

// DC motor 
AF_DCMotor front_left(1);
AF_DCMotor front_right(2);
AF_DCMotor rear_right(3);
AF_DCMotor rear_left(4);

void setup() {
  Serial.begin(9600);
  front_right.setSpeed(255);
  front_left.setSpeed(255);
  rear_right.setSpeed(255);
  rear_left.setSpeed(255);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    Serial.print("Command: ");
    Serial.println(data);
    if (data == "forward"){
      runForward();
    } else if (data == "backward"){
      runBackward();
    } else if (data == "left"){
      turnLeft();
    } else if (data == "right"){
      turnRight();
    } else if (data == "stop"){
      stopRunning();
    }
  }
}

void stopRunning() {
  front_right.run(RELEASE);
  front_left.run(RELEASE);
  rear_right.run(RELEASE);
  rear_left.run(RELEASE);
}

void runForward() {
  front_right.run(BACKWARD);
  front_left.run(BACKWARD);
  rear_right.run(BACKWARD);
  rear_left.run(BACKWARD);
}

void runBackward() {
  front_right.run(FORWARD);
  front_left.run(FORWARD);
  rear_right.run(FORWARD);
  rear_left.run(FORWARD);
}

void turnRight() {
  front_right.run(FORWARD);
  front_left.run(BACKWARD);
  rear_right.run(FORWARD);
  rear_left.run(BACKWARD);
}

void turnLeft() {
  front_right.run(BACKWARD);
  front_left.run(FORWARD);
  rear_right.run(BACKWARD);
  rear_left.run(FORWARD);
}
