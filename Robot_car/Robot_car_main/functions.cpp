#include "Arduino.h"
#include <Servo.h>
#include "functions.h"

/* -----------------------
	servo left = 170 deg
	servo middle = 85 deg
	servo right = 0 deg
   ----------------------- */

Servo servo;
float dist_l, dist_c, dist_r, dist;
unsigned int deg;

extern const unsigned int Servo_center_pos, ecart, dist_min, dist_max, nb_mesure;


void stop() { // Stop car from moving
	digitalWrite(ENA,LOW); //enable L298n A channel
	digitalWrite(ENB,LOW); //enable L298n B channel
	digitalWrite(IN1,LOW); //set IN1 low level
	digitalWrite(IN2,LOW); //set IN2 low level
	digitalWrite(IN3,LOW); //set IN3 low level
	digitalWrite(IN4,LOW); //set IN4 low level
	Serial.println("Stop"); //send message to serial monitor
}

void forward (float cm, int speed) { // move car forward of X cm at speed between 0 & 255
	analogWrite(ENB,speed);
	analogWrite(ENA,speed);
	digitalWrite(IN1,LOW);
	digitalWrite(IN2,HIGH);
	digitalWrite(IN3,HIGH);
	digitalWrite(IN4,LOW);
	Serial.println("Forward");
	delay(cm*14*255/speed);
	stop();
}

void backward (float cm, int speed) { // move car backward of X cm at speed between 0 & 255
	analogWrite(ENB,speed);
	analogWrite(ENA,speed);
	digitalWrite(IN1,HIGH);
	digitalWrite(IN2,LOW);
	digitalWrite(IN3,LOW);
	digitalWrite(IN4,HIGH);
	Serial.println("Backward");
	delay(cm*14*255/speed);
	stop();
}

void left (float deg) { // turn car left of X deg
	digitalWrite(ENA,HIGH);
	digitalWrite(ENB,HIGH);
	digitalWrite(IN1,LOW);
	digitalWrite(IN2,HIGH);
	digitalWrite(IN3,LOW);
	digitalWrite(IN4,HIGH); 
	Serial.print("turn Left for ");
	Serial.print(deg);
	Serial.println(" degres");
	delay(deg*43/9);
}

void right (float deg) { // turn car right of X deg
	digitalWrite(ENA,HIGH);
	digitalWrite(ENB,HIGH);
	digitalWrite(IN1,HIGH);
	digitalWrite(IN2,LOW);
	digitalWrite(IN3,HIGH);
	digitalWrite(IN4,LOW);
	Serial.print("turn Right for ");
	Serial.print(deg);
	Serial.println(" degres");
	delay(deg*43/9);
}

void servo_left() { // move servo to left position using d milliseconds
	servo.write(Servo_center_pos + ecart);
	Serial.println("Servo Left");
}

void servo_center() { // move servo to center position using d milliseconds
	servo.write(Servo_center_pos);
	Serial.println("Servo Center");
}

void servo_right() { // move servo to right position using d milliseconds
	servo.write(Servo_center_pos - ecart);
	Serial.println("Servo Right");
}

void servo_at (unsigned int deg) { // move servo to X deg using d milliseconds
	servo.write(deg);
	Serial.print("Servo @ ");
	Serial.print(deg);
	Serial.println(" degres");
}

float mesure_distance() { // mesure distance to nearest object straight ahead
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

void swap (float tab[], int a, int b) { 
	float tmp = tab[a];
	tab[a] = tab[b];
	tab[b] = tmp;
}

void sort_tab (float tab[]) { // appli inserting sort
	for (int i = 0; i < nb_mesure; ++i){
		int p = i;
		for (int j = i; j < nb_mesure; ++j)
			if (tab[j] < tab[p])
				p = j;
		swap(tab,i,p);
	}
}

float get_median (float tab[]) { // get median of an array
	sort_tab(tab);
	return (float) tab[(int) nb_mesure/2];
}

void set_distances() { // set left,center,right distances to object
	int t = 15*ecart;
	float tab[nb_mesure];
	servo_left();
	delay(t);
	for (int i = 0; i < nb_mesure; i++){
		tab[i] = mesure_distance();
		delay(5);
	}
	dist_l = get_median(tab);
	servo_center();
	delay(t);
	for (int i = 0; i < nb_mesure; i++){
		tab[i] = mesure_distance();
		delay(5);
	}
	dist_c = get_median(tab);
	servo_right();
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

void set_distances2() { // set the direction & distance to nearest object
	int dt = 150;
	float tab[nb_mesure];
	dist = 3000.0;
	for (int i = Servo_center_pos - ecart; i <= Servo_center_pos + ecart; i += 25){
		servo_at(i);
		delay(dt);
		
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

void face_object() { // move servo to face nearest object
	set_distances2();
	
	servo_at(deg);

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

void turn_to_face_object() { // move car to face nearest object
	stop();
	set_distances2();

	// servo_center();
	servo_at(deg);

	if ((int) deg - (int) Servo_center_pos >= 0){
		Serial.print(deg - Servo_center_pos);
		Serial.println(" degres left ------------------------");
		left((float) deg);
	} else {
		Serial.print(Servo_center_pos - deg);
		Serial.println(" degres right -----------------------");
		right((float) deg);
	}

	if (dist > dist_max) {
		Serial.print("moving forward (cm) ");
		Serial.println(dist-dist_max);
	} else if (dist < dist_min) {
		Serial.print("moving backward (cm) ");
		Serial.println(dist-dist_min);
	}
}