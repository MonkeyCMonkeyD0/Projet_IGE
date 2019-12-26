// servo left max = 170 deg
// servo right max = 0 deg
// servo middle = 85 deg

#include <Servo.h>

#define Echo A4
#define Trig A5
#define Servo_center_pos 85


Servo servo;
float dist_l, dist_c, dist_r;
int ecart = 90;

void servo_left(int d) {
  servo.write(Servo_center_pos + ecart);
  Serial.println("Servo Left");
  delay(d);
}

void servo_center(int d) {
  servo.write(Servo_center_pos);
  Serial.println("Servo Center");
  delay(d);
}

void servo_right(int d) {
  servo.write(Servo_center_pos - ecart);
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
    int t = 6*ecart;
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
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
//  pinMode(IN1, OUTPUT);
//  pinMode(IN2, OUTPUT);
//  pinMode(IN3, OUTPUT);
//  pinMode(IN4, OUTPUT);
//  pinMode(ENA, OUTPUT);
//  pinMode(ENB, OUTPUT);
}

void loop() {
  set_distances();
//  delay(1000);
  ecart = (ecart < 20) ? ecart : ecart / 1.5;
}
