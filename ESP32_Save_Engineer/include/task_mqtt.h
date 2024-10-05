
#ifndef TASK_MQTT_H
#define TASK_MQTT_H

#include<Arduino.h>

extern QueueHandle_t electricCurrrentQueue;
extern QueueHandle_t voltageQueue;

void mqtt_task(void *pvParameters);

#endif
