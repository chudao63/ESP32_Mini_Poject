#include<Arduino.h>
#include "task_sensor_zmpt101b.h"



ZMPT101B zmpt(35);

void task_sensor_zmpt101b(void *pvParameters){
    Serial.println("ZMPT starting...");
    zmpt.calibrate();
    Serial.println("ZMPT calibrate done!!");

    while(1){
        float current = zmpt.readVoltage();
        Serial.print("Zmpt value: ");

        Serial.print(current, 4);
        Serial.println(" V");
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }



}