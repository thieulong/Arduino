#include <AFMotor.h>

// DC motor 
AF_DCMotor m1(1);
AF_DCMotor m2(2);
AF_DCMotor m3(3);
AF_DCMotor m4(4);

void setup() {
  Serial.begin(9600);
  m1.setSpeed(255);
  m2.setSpeed(255);
  m3.setSpeed(255);
  m4.setSpeed(255);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    Serial.print("Command: ");
    Serial.println(data);
    if (data == "m1-forward"){
      forwardM1();
    } else if (data == "m2-forward"){
      forwardM2();
    } else if (data == "m3-forward"){
      forwardM3();
    } else if (data == "m4-forward"){
      forwardM4();
    } else if (data == "m1-backward"){
      backwardM1();
    } else if (data == "m2-backward"){
      backwardM2();
    } else if (data == "m3-backward"){
      backwardM3();
    } else if (data == "m4-backward"){
      backwardM4();
    } else if (data == "m1-stop"){
      stopM1();
    } else if (data == "m2-stop"){
      stopM2();
    } else if (data == "m3-stop"){
      stopM3();
    } else if (data == "m4-stop"){
      stopM4();
    }
  }
}

void stopM1() {
  m1.run(RELEASE);
}

void stopM2() {
  m2.run(RELEASE);
}

void stopM3() {
  m3.run(RELEASE);
}

void stopM4() {
  m4.run(RELEASE);
}

void forwardM1() {
  m1.run(FORWARD);
}

void forwardM2() {
  m2.run(FORWARD);
}

void forwardM3() {
  m3.run(FORWARD);
}

void forwardM4() {
  m4.run(FORWARD);
}

void backwardM1() {
  m1.run(BACKWARD);
}

void backwardM2() {
  m2.run(BACKWARD);
}

void backwardM3() {
  m3.run(BACKWARD);
}

void backwardM4() {
  m4.run(BACKWARD);
}
