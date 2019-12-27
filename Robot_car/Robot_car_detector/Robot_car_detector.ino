// servo left = 170 deg
// servo right = 0 deg
// servo middle = 85 deg

#include <Servo.h>

#define Echo A4
#define Trig A5
#define Servo_center_pos 85
#define nb_mesure 3

Servo servo;
float dist_l, dist_c, dist_r, dist;
int deg, ecart = 75, dist_min = 8, dist_max = 12;


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

void servo_at(int deg, int dt) {
  servo.write(deg);
  Serial.print("Servo @ ");
  Serial.print(deg);
  Serial.println(" degres");
  delay(dt);
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
  int t = 15*ecart;
  float tab[nb_mesure];
  servo_left(t);
  for (int i = 0; i < nb_mesure; i++){
    tab[i] = mesure_distance();
    delay(5);
  }
  dist_l = get_median(tab);
  servo_center(t);
  for (int i = 0; i < nb_mesure; i++){
    tab[i] = mesure_distance();
    delay(5);
  }
  dist_c = get_median(tab);
  servo_right(t);
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

void set_distances2() {
  int dt = 150;
  float tab[nb_mesure];
  dist = 3000.0;
  for (int i = Servo_center_pos - ecart; i <= Servo_center_pos + ecart; i += 25){
    servo_at(i,dt);
    
    for (int j = 0; j < nb_mesure; j++){
      tab[j] = mesure_distance();
      delay(2);
    }

    if (dist >= get_median(tab)){
      dist = get_median(tab);
      deg = i;
    }
  }
  Serial.print("Objet @ ");
  Serial.print(dist);
  Serial.print(" cm & @ ");
  Serial.print(deg);
  Serial.println(" degres");
}

void face_object() {
  set_distances2();
  
  servo_at(deg,0);

  if (deg - Servo_center_pos >= 0){
    Serial.print(deg - Servo_center_pos);
    Serial.println(" degres left ------------------------");
  } else {
    Serial.print(Servo_center_pos - deg);
    Serial.println(" degres right -----------------------");
  }

  if (dist > dist_max) {
    Serial.print("moving forward (cm) ");
    Serial.println(dist-dist_max);
  } else if (dist < dist_min) {
    Serial.print("moving backward (cm) ");
    Serial.println(dist-dist_min);
  }
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
  servo_center(50);
}

void loop() {
  face_object();
  delay(10000);
//  ecart = (ecart < 20) ? ecart : ecart / 1.5;
}
