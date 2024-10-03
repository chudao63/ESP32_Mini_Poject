#include<Arduino.h>
#include "task_sensor_acs712.h"
#include "task_sensor_zmpt101b.h"

void setup(){
  Serial.begin(9600);

  xTaskCreatePinnedToCore(task_sensor_acs712, "Task Sensor ACS", 4096, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(task_sensor_zmpt101b, "Task Sensor ZMPT", 4096, NULL, 1, NULL, 1);
}

void loop(){
}