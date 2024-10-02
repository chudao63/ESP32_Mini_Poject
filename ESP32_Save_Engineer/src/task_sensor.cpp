#include "task_sensor.h" 
//Khai báo cảm biến ACS712

ACS712 acs712(35, 0.185, 3.3);

void task_sensor(void *pvParameters){
    acs712.calibrate();
    Serial.println("Calibration complete!!");

    while(1){
        float current = acs712.readCurrent();

        Serial.print("Current: ");
        Serial.print(current, 4);
        Serial.println(" A");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}