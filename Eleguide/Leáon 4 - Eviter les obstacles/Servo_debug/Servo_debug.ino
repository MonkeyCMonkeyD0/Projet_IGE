//www.elegoo.com
#include <Servo.h>
Servo myservo;

void setup(){
  myservo.attach(3);
  myservo.write(170);// move servos to center position -> 90°
} 
void loop(){

}
