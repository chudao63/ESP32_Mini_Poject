#include<Arduino.h>
#include "ZMPT101B.h" 

ZMPT101B::ZMPT101B(int pin): _pin(pin){};

void ZMPT101B::calibrate(){
    float total = 0;
    int SAMPLES = 100;
    for(int i = 0; i < SAMPLES; i++){
        total += analogRead(_pin);
        delay(10);
    }

    _zeroVoltageOffset = (total/SAMPLES)/4095*3.3;
}

float ZMPT101B::readVoltage(){
    float total = 0;
    int SAMPLES = 100;

    for(int i = 0; i < SAMPLES; i++){
        total += analogRead(_pin);
        delay(10);
    }

    float analogValue = total/SAMPLES;
    float voltage = (analogValue/4095)*3.3;

    voltage = (voltage - _zeroVoltageOffset);
    return voltage;

}


