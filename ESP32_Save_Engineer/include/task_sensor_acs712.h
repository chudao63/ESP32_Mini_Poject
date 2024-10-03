#ifndef TASK_SENSOR_ACS712_H
#define TASK_SENSOR_ACS712_H

#include<Arduino.h>
#include<ACS712.h>

extern ACS712 acs712;
void task_sensor_acs712(void *pvParameters);


#endif