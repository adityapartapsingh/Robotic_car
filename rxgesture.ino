#include<AFMotor.h>
#include<VirtualWire.h>

#define MAX_SPEED 250  
int speedSet =0;

AF_DCMotor motor1(1,MOTOR12_1KHZ);
AF_DCMotor motor2(2,MOTOR12_1KHZ);
AF_DCMotor motor3(3,MOTOR34_1KHZ);
AF_DCMotor motor4(4,MOTOR34_1KHZ);


void setup(){
  vw_set_ptt_inverted(true);
  vw_set_rx_pin(13);
  vw_setup(4000);
  vw_rx_start();
  Serial.begin(9600);
  
}

void loop(){
   Serial.println("start");
  delay(500);
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf,buflen)){
    Serial.println("recive");
    delay(500);
    if(buf[0]=='f'){
      moveForward();
      delay(500);
      Serial.println("forward");
    }
    else if(buf[0]=='b'){
      moveBackward();
      delay(500);
      Serial.println("backward");
    }
    else if(buf[0]=='r'){
      turnRight();
      delay(500);
      Serial.println("right");
    }
     else if(buf[0]=='l'){
      turnLeft();
      delay(500);
      Serial.println("left");
    }
    else if(buf[0]=='s'){
      Stop();
      delay(500);
      Serial.println("stop");
    }
    
    
  }

Serial.println("end");
delay(500);
}



void moveForward(){
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
 


void moveBackward(){
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


void turnRight(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void turnLeft(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void Stop(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
