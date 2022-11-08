#include<AFMotor.h>
#include<NewPing.h>
#include<Servo.h>

#define TRIG_PIN A3                // trig pin for ultrasonic sensor
#define ECHO_PIN A2               // echo pin for ultrasonic sensor
#define MAX_DISTANCE 200
#define MAX_SPEED 250                // set speed of dc motor
#define MAX_SPEED_OFFSET 20
int BACK_IR=2;                       // back ir pin 

#define RIGHTir A4               // front right ir     
#define LEFTir A5                 // front left ir 

#define  Left_Line_IR A0         // left line folowing ir 
#define  Right_Line_IR A1         // right line following ir 

unsigned UsDistance =0;
unsigned RightValue=0;
unsigned LeftValue=0;              

NewPing sonar(TRIG_PIN,ECHO_PIN,MAX_DISTANCE);

AF_DCMotor motor1(1,MOTOR12_1KHZ);
AF_DCMotor motor2(2,MOTOR12_1KHZ);
AF_DCMotor motor3(3,MOTOR34_1KHZ);
AF_DCMotor motor4(4,MOTOR34_1KHZ);

Servo myservo;

String mode;
String voice;
String command;

boolean goesForward=false;
int distance = 100;
int speedSet =0;

void setup(){
   Serial.begin(9600);
  myservo.attach(9);
  myservo.write(115);
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  pinMode(RIGHTir,INPUT);
  pinMode(LEFTir,INPUT);
  pinMode(BACK_IR,INPUT);
  pinMode(Left_Line_IR,INPUT);
  pinMode(Right_Line_IR,INPUT); 
}

void loop(){
  if(Serial.available()>0){
    mode="";
    delay(100);
    mode=Serial.readString();
    delay(100);
    Serial.println(mode);
    }

   while(mode=="o"){
     distance = readPing();
     RightValue=digitalRead(RIGHTir);
     LeftValue = digitalRead(LEFTir);
       int distanceR=0;
       int distanceL=0;


  if(distance<=15){
    moveStop();
    delay(100);
    moveBackward();
    delay(200);
    moveStop();
    delay(100);
    distanceR = lookRight();
    delay(100);
    distanceL = lookLeft();
    delay(100);
    if(distanceR>=distanceL){
      turnRight();
      delay(500);
      moveStop();
    }
    else{
      turnLeft();
      delay(500);
      moveStop();
    }
  }
  else if( RightValue==1){
   moveStop();
    delay(100);
    moveBackward();
    delay(200);
    moveStop();
    delay(100);
    turnLeft();
    delay(500);
    moveStop();
  }
  else if (LeftValue==1){
   moveStop();
    delay(100);
    moveBackward();
    delay(200);
    moveStop();
    delay(100);
    turnRight();
    delay(500);
    moveStop();
  }
  else{
    moveForward();
    }
  distance = readPing();
  if(Serial.available()>0){
    moveStop();
    break;
  }
   }

  while(mode=="h"){
    distance = readPing();
    RightValue=digitalRead(RIGHTir);
    LeftValue = digitalRead(LEFTir);

    if((distance>1)&&(distance<15)){
      Forward();
  }
  else if((RightValue==0)&&(LeftValue==1)){
    turnLeft();
    delay(50);
  }
  else if((RightValue==1)&&(LeftValue==0)){
    turnRight();
    delay(50);
  }
  else if(distance>15){
    moveStop();
  }

  if(Serial.available()>0){
    moveStop();
    break;
  }
  }

  while(mode=="v"){
     if(Serial.available()>0){
    voice="";
    delay(100);
    voice=Serial.readString();
    delay(100);
    }

    if(voice=="turn left" || voice=="left" ){
      lookLeft();
      delay(100);
      turnLeft();
      delay(500);
      moveStop();
    }
    else if(voice=="turn right" || voice=="right"){
      lookRight();
      delay(100);
      turnRight();
      delay(500);
      moveStop();
    }

     else if(voice=="stop"){
      moveStop();
    }
    
    else if(voice=="turn around"){
      turnLeft();
      delay(2500);
      moveStop();
    }  
    
    while(voice=="move forward" || voice=="move" || voice=="forward"){
      moveForward_voice();
      if(Serial.available()>0){
        moveStop();
        break;
        }
    }

   while(voice=="move backward" || voice=="move backwards" || voice=="backward" || voice=="backwards" || voice=="back"){
       moveBackward_voice();
      if(Serial.available()>0){
         moveStop();
        break;
        }
    } 
    
    if ( voice =="o" || voice=="h" || voice=="l" || voice=="M" || voice=="s"){
         mode=voice;
         break;
    }
    
    voice="";
  }

  while (mode=="s"){
    moveStop();
    if(Serial.available()>0){
    break;
  }
  }

  while (mode=="l"){
    
    if(digitalRead(Left_Line_IR)==1 && digitalRead(Right_Line_IR)==1){
      Forward();
    }
    else if(digitalRead(Left_Line_IR)==0 && digitalRead(Right_Line_IR)==1){
      turnLeft();
    }
    else if(digitalRead(Left_Line_IR)==1 && digitalRead(Right_Line_IR)==0){
      turnRight();
    }
    else if(digitalRead(Left_Line_IR)==0 && digitalRead(Right_Line_IR)==0 ){
      moveStop();
    }
    if(Serial.available()>0){
    break;
    Serial.println("out");
    }
}

  while (mode=="M"){

    if(Serial.available()>0){
    command="";
    delay(200);
    command=Serial.readString();
    delay(2);
    }

    if (command=="L"){
      turnLeft();
      delay(500);
    }
    if (command=="R"){
      turnRight();
      delay(500);
    }
    if (command=="F" || command=="U"){
      Forward();
    }
    if (command=="B" || command=="D"){
      Backward();
    }
    if ( command =="o" || command=="h" || command=="l" || command=="v" || command=="s"){
         mode=command;
         break;
    }
    if (command=="0"|| command=="S"){
      moveStop();
    }
    
  }
   
}

int lookRight(){
  myservo.write(50);
  delay(100);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
}

int lookLeft(){
  myservo.write(180);
  delay(100);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0){
    cm = 250;
  }
  return cm;
}

void moveStop(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward(){
  if(!goesForward){
    goesForward = true;
      Forward();
  }
}
void Forward(){
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    for(speedSet = 0 ; speedSet < MAX_SPEED; speedSet +=2){           // slowly bring the speed up to avoid loading down the batteries too quickly
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
    }
}

void moveForward_voice(){
  if(readPing()< 10){
    moveStop();
    voice="";
  }
  else{  motor1.run(FORWARD);
      Forward();
    }
}

void moveBackward_voice(){
  int Back_IR_distance=digitalRead(BACK_IR);
  if(Back_IR_distance==1){
    moveStop();
    voice="";
  }
  else{
    Backward();
    }
}

void Backward(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  for(speedSet = 0 ; speedSet < MAX_SPEED; speedSet +=2){           // slowly bring the speed up to avoid loading down the batteries too quickly
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
    }
}

void moveBackward(){
  goesForward=false;
      Backward();
}

void turnRight(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

}

void turnLeft(){
   motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
