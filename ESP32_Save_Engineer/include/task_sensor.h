#ifndef TASK_SENSOR_H
#define TASK_SENSOR_H

#include<Arduino.h>
#include<ACS712.h>

extern ACS712 acs712;
void task_sensor(void *pvParameters);


#endif