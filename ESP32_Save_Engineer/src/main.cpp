#include<Arduino.h>
#include "task_sensor.h"

void setup(){
  Serial.begin(9600);

  xTaskCreatePinnedToCore(task_sensor, "Task Sensor", 4096, NULL, 1, NULL, 1);

}

void loop(){
}