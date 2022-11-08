#include<AFMotor.h>
#include<NewPing.h>
#include<Servo.h>

#define TRIG_PIN A3
#define ECHO_PIN A4
#define MAX_DISTANCE 200
#define MAX_SPEED 250                // set speed of dc motor
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN,ECHO_PIN,MAX_DISTANCE);

AF_DCMotor motor1(1,MOTOR12_1KHZ);
AF_DCMotor motor2(2,MOTOR12_1KHZ);
AF_DCMotor motor3(3,MOTOR34_1KHZ);
AF_DCMotor motor4(4,MOTOR34_1KHZ);
Servo myservo;

boolean goesForward=false;
int distance = 100;
int speedSet =0;

void setup(){
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
}

void loop(){
  int distanceR=0;
  int distanceL=0;
//  delay(40);

  if(distance<=15){
    moveStop();
    delay(100);
    moveBackward();
    delay(100);
    moveStop();
    delay(100);
    distanceR = lookRight();
    delay(100);
    distanceL = lookLeft();
    delay(100);

    if(distanceR>=distanceL){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{moveForward();}
  distance = readPing();
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
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    for(speedSet = 0 ; speedSet < MAX_SPEED; speedSet +=2){           // slowly bring the speed up to avoid loading down the batteries too quickly
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward(){
  goesForward=false;
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  for(speedSet = 0 ; speedSet < MAX_SPEED; speedSet +=2){           // slowly bring the speed up to avoid loading down the batteries too quickly
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
}

void turnRight(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(500);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void turnLeft(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(500);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
