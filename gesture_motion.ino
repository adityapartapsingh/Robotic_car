#include<Wire.h>
#include<Adafruit_Sensor.h>
#include<Adafruit_ADXL345_U.h>
#include<VirtualWire.h>                 // for rf 

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

int x_stable,y_stable,x_value,y_value,x_final,y_final;
char *data;

void setup(){
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(11);
  vw_setup(4000);
  
  Serial.begin(9600);
  
  if(!accel.begin()){
    Serial.println("no valid sensor found");
    while(1);
  }
  
sensors_event_t event;
accel.getEvent(&event);
x_stable = event.acceleration.x;
y_stable = event.acceleration.y;

}


void loop(){
  sensors_event_t event;
  accel.getEvent(&event);

x_value = event.acceleration.x;
y_value = event.acceleration.y;

x_final= x_value - x_stable;
y_final= y_value - y_stable;

if(y_final >=5){
  data="b";
  vw_send((uint8_t *)data, strlen(data));
  vw_wait_tx();
  delay (500);
  Serial.println("backward");
}
else if(y_final <=-5){
  data="f";
  vw_send((uint8_t *)data, strlen(data));
  vw_wait_tx();
  delay (500);
  Serial.println("forward");
}
else if(x_final <=-3){
  data="r";
  vw_send((uint8_t *)data, strlen(data));
  vw_wait_tx();
  delay (500);
  Serial.println("right");
}
else if(x_final >=3){
  data="l";
  vw_send((uint8_t *)data, strlen(data));
  vw_wait_tx();
  delay (500);
  Serial.println("left");
}
else{
  data="s";
  vw_send((uint8_t *)data, strlen(data));
  vw_wait_tx();
  delay (500);
  Serial.println("stop");
}

  
}
