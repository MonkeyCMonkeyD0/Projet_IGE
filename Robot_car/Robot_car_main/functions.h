#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif


#include <Servo.h>

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define Echo A4
#define Trig A5


void stop();
void forward (float cm, int speed);
void backward (float cm, int speed);
void left (float deg);
void right (float deg);
void servo_left (int d);
void servo_center (int d);
void servo_right (int d);
void servo_at (int deg, int dt);
float mesure_distance();
void swap (float tab[], int a, int b);
void sort_tab (float tab[]);
float get_median (float tab[]);
void set_distances();
void set_distances2();
void face_object();

#ifdef __cplusplus
} // extern "C"
#endif

#endif