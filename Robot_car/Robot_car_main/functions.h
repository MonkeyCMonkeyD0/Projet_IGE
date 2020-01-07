#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Servo.h>

using namespace std;

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define Echo A4
#define Trig A5


void stop();
void forward (float cm, unsigned int speed);
void backward (float cm, unsigned int speed);
void left (float deg);
void right (float deg);
void servo_left ();
void servo_center ();
void servo_right ();
void servo_at (unsigned int deg);
float mesure_distance();
void swap (float tab[], unsigned int a, unsigned int b);
void sort_tab (float tab[]);
float get_median (float tab[]);
int get_max(float ** tab);
void set_distances();
void set_distances2();
void set_distances3();
float rad_to_deg (float x);
float deg_to_rad (float x);
float get_car_distance (float dist, float angle);
float get_car_angle (float dist, float angle);
void turn_servo_to_face_object();
void turn_to_face_object();
void debug();

#ifdef __cplusplus
} // extern "C"
#endif

#endif