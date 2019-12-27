// servo left = 170 deg
// servo right = 0 deg
// servo middle = 85 deg

#include <Servo.h>

#define Echo A4
#define Trig A5
#define Servo_center_pos 85
#define nb_mesure 5

Servo servo;
float dist_l, dist_c, dist_r;
int ecart = 30;


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

void swap(float tab[], int a, int b){
  float tmp = tab[a];
  tab[a] = tab[b];
  tab[b] = tmp;
}

void sort_tab(float tab[]){
  for (int i = 0; i < nb_mesure; ++i){
    int p = i;
    for (int j = i; j < nb_mesure; ++j)
      if (tab[j] < tab[p])
        p = j;
    swap(tab,i,p);
  }
}

float get_median(float tab[]){
  sort_tab(tab);
  return (float) tab[(int) nb_mesure/2];
}

void set_distances() {
    int t = 5*ecart;
    float tab[nb_mesure];
    servo_left(t);
    delay(t);
    for (int i = 0; i < nb_mesure; i++){
      tab[i] = mesure_distance();
      delay(5);
    }
    dist_l = get_median(tab);
    servo_center(t);
    delay(t);
    for (int i = 0; i < nb_mesure; i++){
      tab[i] = mesure_distance();
      delay(5);
    }
    dist_c = get_median(tab);
    servo_right(t);
    delay(t);
    for (int i = 0; i < nb_mesure; i++){
      tab[i] = mesure_distance();
      delay(5);
    }
    dist_r = get_median(tab);
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
  delay(1000);
//  ecart = (ecart < 20) ? ecart : ecart / 1.5;
}
