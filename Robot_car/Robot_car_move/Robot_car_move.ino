#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11


void stop(){ 
  digitalWrite(ENA,LOW); //enable L298n A channel
  digitalWrite(ENB,LOW); //enable L298n B channel
  digitalWrite(IN1,LOW); //set IN1 low level
  digitalWrite(IN2,LOW); //set IN2 low level
  digitalWrite(IN3,LOW); //set IN3 low level
  digitalWrite(IN4,LOW); //set IN4 low level
  Serial.println("Stop"); //send message to serial monitor
}


void forward(float cm, int speed){
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

void backward(float cm, int speed){ 
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

void left(float deg){
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
  Serial.println("Left");
  delay(deg*43/9);
}

void right(float deg){
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.println("Right");
  delay(deg*43/9);
}


void setup() {
  Serial.begin(9600); //open serial and set the baudrate
  pinMode(IN1,OUTPUT); //before using io pin, pin mode must be set first 
  pinMode(IN2,OUTPUT); //before using io pin, pin mode must be set first 
  pinMode(IN3,OUTPUT); //before using io pin, pin mode must be set first 
  pinMode(IN4,OUTPUT); //before using io pin, pin mode must be set first 
  pinMode(ENA,OUTPUT); //before using io pin, pin mode must be set first 
  pinMode(ENB,OUTPUT); //before using io pin, pin mode must be set first 
}

void loop() {
  // put your main code here, to run repeatedly:
  forward(50,150);
  stop();
  forward(20,255);
  stop();
  right(360);
  stop();
  backward(70,80);
  stop();
  delay(20000);
}
