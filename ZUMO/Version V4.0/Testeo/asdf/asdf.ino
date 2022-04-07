#include <TimerOne.h>

void setup(){
  Serial.begin(9600);
  Serial.println("I'm Ready!");
  Timer1.attachInterrupt(taskTimeout, 1500*long(1000));
}

void loop(){
  if (digitalRead(2)){
    Timer1.detachInterrupt();
    Timer1.attachInterrupt(taskTimeout, 1500*long(1000));
  }  
}

void taskTimeout(void){
  Serial.println("Task Finished!");
  Timer1.detachInterrupt();
}
