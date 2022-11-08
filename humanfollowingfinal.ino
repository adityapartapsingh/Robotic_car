#include<AFMotor.h>
#include<NewPing.h>
#include<Servo.h>

#define TRIG_PIN A3
#define ECHO_PIN A4
#define MAX_DISTANCE 200
               // set speed of dc motor ....
              //........

#define RIGHTir A0
#define LEFTir A2
unsigned UsDistance =0;
unsigned RightValue=0;
unsigned LeftValue=0;

NewPing sonar(TRIG_PIN,ECHO_PIN,MAX_DISTANCE);

AF_DCMotor motor1(1,MOTOR12_1KHZ);
AF_DCMotor motor2(2,MOTOR12_1KHZ);
AF_DCMotor motor3(3,MOTOR34_1KHZ);
AF_DCMotor motor4(4,MOTOR34_1KHZ);
Servo myservo;

                      
int speedSet =0;                        

void setup(){
 Serial.begin(9600);
 myservo.attach(9);
 myservo.write(115);
 
pinMode(RIGHTir,INPUT);
pinMode(LEFTir,INPUT);
}

void loop(){
  UsDistance = sonar.ping_cm();
  
  Serial.print("UsDistance");
  Serial.println(UsDistance);

  RightValue=digitalRead(RIGHTir);
  LeftValue = digitalRead(LEFTir);

  Serial.print("RIGHTir");
  Serial.println(RightValue);
 
  Serial.print("LEFTir");
  Serial.println(LeftValue);
 

  if((UsDistance>1)&&(UsDistance<10)){
    moveForward();
  }
  else if((RightValue==0)&&(LeftValue==1)){
    turnLeft();
    delay(50);
  }
  else if((RightValue==1)&&(LeftValue==0)){
    turnRight();
    delay(50);
  }
  else if(UsDistance>10){
    moveStop();
  }
    
}

void moveStop(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward(){
  
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    for(speedSet = 0 ; speedSet < 200; speedSet +=2){           // slowly bring the speed up to avoid loading down the batteries too quickly
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
     
    }
  }



void turnRight(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(10);
}

void turnLeft(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(10);
}
