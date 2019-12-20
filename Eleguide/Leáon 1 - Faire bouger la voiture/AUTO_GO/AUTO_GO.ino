//www.elegoo.com

//    The direction of the car's movement
//  ENA   ENB   IN1   IN2   IN3   IN4   Description  
//  HIGH  HIGH  HIGH  LOW   LOW   HIGH  Car is runing forward
//  HIGH  HIGH  LOW   HIGH  HIGH  LOW   Car is runing back
//  HIGH  HIGH  LOW   HIGH  LOW   HIGH  Car is turning left
//  HIGH  HIGH  HIGH  LOW   HIGH  LOW   Car is turning right
//  HIGH  HIGH  LOW   LOW   LOW   LOW   Car is stoped
//  HIGH  HIGH  HIGH  HIGH  HIGH  HIGH  Car is stoped
//  LOW   LOW   N/A   N/A   N/A   N/A   Car is stoped
// IN1: Avant droit

//define L298n module IO Pin
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

void stop(){ 
  digitalWrite(ENA,LOW); //enable L298n A channel
  digitalWrite(ENB,LOW); //enable L298n B channel
  digitalWrite(IN1,LOW); //set IN1 hight level
  digitalWrite(IN2,LOW); //set IN2 low level
  digitalWrite(IN3,LOW); //set IN3 low level
  digitalWrite(IN4,LOW); //set IN4 hight level
  Serial.println("Stop"); //send message to serial monitor
}


void forward(){ 
  digitalWrite(ENA,HIGH); //enable L298n A channel
  digitalWrite(ENB,HIGH); //enable L298n B channel
  digitalWrite(IN1,HIGH); //set IN1 hight level
  digitalWrite(IN2,LOW);  //set IN2 low level
  digitalWrite(IN3,LOW);  //set IN3 low level
  digitalWrite(IN4,HIGH); //set IN4 hight level
  Serial.println("Forward");//send message to serial monitor
}

void back(){
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.println("Back");
}

void left(){
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
  Serial.println("Left");
  delay(340);
}

void right(){
  
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.println("Right");
  delay(290);
}

void test(){ 
  delay(5000);
  digitalWrite(ENA,HIGH); //enable L298n A channel
  digitalWrite(ENB,HIGH); //enable L298n B channel
  digitalWrite(IN1,HIGH); //set IN1 hight level
  digitalWrite(IN2,LOW);  //set IN2 low level
  digitalWrite(IN3,LOW);  //set IN3 low level
  digitalWrite(IN4,HIGH); //set IN4 hight level
  Serial.println("Forward");//send message to serial monitor
}



//before execute loop() function, 
//setup() function will execute first and only execute once
void setup() {
  Serial.begin(9600);//open serial and set the baudrate
  pinMode(IN1,OUTPUT);//before useing io pin, pin mode must be set first 
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
}

//Repeat execution
void loop() {
 // test();
//forward();  //go forward
 
  /*delay(5000);//delay 1000 ms
  back();     //go back
 delay(5000);*/
 // left();     //turning left
  
  forward();
  delay(6000);
  right();
  forward();
  delay(3000);
  left();
  forward();
  delay(2500);
  right();
  delay(50);
  forward();
  delay(5000);
  right();
  delay(50);
  
  
  stop();
  delay(20000);
 /* right();    //turning right
  delay(500);*/
}
