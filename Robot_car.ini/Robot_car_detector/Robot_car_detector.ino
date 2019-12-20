#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(3);
  servo.write(100);
}

void loop() {
  delay(1000);
  servo.write(0);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(180);
}
