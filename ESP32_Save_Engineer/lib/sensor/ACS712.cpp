#include "ACS712.h"

ACS712::ACS712(int pin, float sensitivity, float v_ref): _pin(pin), _sensitivity(sensitivity), _v_ref(v_ref), _zeroCurrentOffset(0){};


void ACS712::calibrate(){
    long total = 0; 
    const int SAMPLES = 100;

    for(int i = 0; i < SAMPLES; i++){
        total += analogRead(_pin);
        delay(10);
    }

    _zeroCurrentOffset = total/SAMPLES;
}

float ACS712::readCurrent(){
    long total = 0;
    const int SAMPLES = 100;

    for(int i = 0; i < SAMPLES; i++){
        total += analogRead(_pin);
        delay(10);
    }
    float analogValue = total/SAMPLES;

    float voltage = (analogValue/4095)*_v_ref;
    float current = (voltage - _zeroCurrentOffset)*_sensitivity;
    return current;
}