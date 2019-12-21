#include <Servo.h>

#define Echo A4
#define Trig A5

Servo servo;
float dist_l, dist_c, dist_r;

void servo_left(int d) {
  servo.write(90);
  Serial.println("Servo Left");
  delay(d);
}

void servo_center(int d) {
  servo.write(45);
  Serial.println("Servo Center");
  delay(d);
}

void servo_right(int d) {
  servo.write(0);
  Serial.println("Servo Right");
  delay(d);
}

float mesure_distance() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);
  float Fdistance = pulseIn(Echo, HIGH);
  Fdistance = Fdistance / 58;
  Serial.print("Distance = ");
  Serial.println(Fdistance);
  return Fdistance;
} 

void set_distances() {
  int t = 200;
  servo_left(t);
  dist_l = mesure_distance();
  delay(t);
  servo_center(t);
  dist_c = mesure_distance();
  delay(t);
  servo_right(t);
  dist_r = mesure_distance();
  delay(t);
  Serial.print("Distance left = ");
  Serial.print(dist_l);
  Serial.print(", center = ");
  Serial.print(dist_c);
  Serial.print(", right = ");
  Serial.println(dist_r);
}


void setup() {
  Serial.begin(9600);
  servo.attach(3);
  servo_center(100);
}

void loop() {
  set_distances();
//  delay(1000);
}
