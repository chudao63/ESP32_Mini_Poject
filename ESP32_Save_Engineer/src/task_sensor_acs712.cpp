#include "task_sensor_acs712.h" 
//Khai báo cảm biến ACS712

ACS712 acs712(35, 0.185, 3.3);

void task_sensor_acs712(void *pvParameters){
    acs712.calibrate();
    Serial.println("ACS Calibration complete!!");

    while(1){
        float current = acs712.readCurrent();

        Serial.print("Current ACS: ");
        Serial.print(current, 4);
        Serial.println(" A");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}