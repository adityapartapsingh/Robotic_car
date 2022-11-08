#include<AFMotor.h>
#include<NewPing.h>
#include<Servo.h>

#define TRIG_PIN A3
#define ECHO_PIN A4
#define MAX_DISTANCE 200
#define MAX_SPEED 250                // set speed of dc motor
int BACK_IR=2;

NewPing sonar(TRIG_PIN,ECHO_PIN,MAX_DISTANCE);

AF_DCMotor motor1(1,MOTOR12_1KHZ);
AF_DCMotor motor2(2,MOTOR12_1KHZ);
AF_DCMotor motor3(3,MOTOR34_1KHZ);
AF_DCMotor motor4(4,MOTOR34_1KHZ);
Servo myservo;
String voice;

int speedSet =0;

void setup(){
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(115);
  pinMode(BACK_IR,INPUT);
}

void loop(){
 while(Serial.available()>0){
    voice="";
    delay(100);
    voice=Serial.readString();
    delay(100);
    Serial.println(voice);
    }

    if(voice=="turn left"){
      lookLeft();
      delay(100);
      turnLeft();
      Stop();
    }
    else if(voice=="turn right"){
      lookRight();
      delay(100);
      turnRight();
      Stop();
    }
     else if(voice=="left"){
      lookLeft();
      delay(100);
      turnLeft();
      Stop();
    }
    else if(voice=="right"){
      lookRight();
      delay(100);
      turnRight();
      Stop();
    }
     else if(voice=="stop"){
      Stop();
    }
    else if(voice=="turn around"){
      turnLeft();
      delay(3500);
      Stop();
    }  
    while(voice=="move forward"){
      moveForward();
      if(Serial.available()>0){
        break;
        }
    }
    while(voice=="move"){
      moveForward();
      if(Serial.available()>0){
        break;
        }
    }
   while(voice=="forward"){
      moveForward();
      if(Serial.available()>0){
        break;
        }
    }
   while(voice=="move backward"){
      moveBackward();
      if(Serial.available()>0){
        break;
        }
    }
   while(voice=="backward"){
      moveBackward();
      if(Serial.available()>0){
        break;
        }
    }
    while(voice=="backwards"){
      moveBackward();
      if(Serial.available()>0){
        break;
        }
    }
    while(voice=="back"){
      moveBackward();
      if(Serial.available()>0){
        break;
        }
    }   
    voice="";

}


int lookRight(){
  myservo.write(50);
  delay(500);
  myservo.write(115);
}

int lookLeft(){
  myservo.write(180);
  delay(500);
  myservo.write(115);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0){
    cm = 250;
  }
  return cm;
}

void moveForward(){
  if(readPing()< 10){
    Stop();
    voice="";
  }
  else{
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
  }
 


void moveBackward(){
  int Back_IR_distance=digitalRead(BACK_IR);
  Serial.println(Back_IR_distance);
  if(Back_IR_distance==1){
    Stop();
    voice="";
  }
  else{
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
}


void turnRight(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(500);
}

void turnLeft(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(500);
}

void Stop(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
