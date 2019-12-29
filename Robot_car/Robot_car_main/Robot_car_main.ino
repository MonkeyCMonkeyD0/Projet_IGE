#include "functions.h"

extern Servo servo;
extern float dist_l, dist_c, dist_r, dist;
extern unsigned int deg;

extern const unsigned int
  Servo_center_pos = 85,
  ecart = 75,
  dist_min = 8,
  dist_max = 12,
  nb_mesure = 5;

/* -----------------------
  servo left = 170 deg
  servo middle = 85 deg
  servo right = 0 deg
   ----------------------- */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(3);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  servo_center();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  turn_to_face_object();
  delay(5000);
}
