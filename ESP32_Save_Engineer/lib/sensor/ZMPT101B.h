#include<Arduino.h>

class ZMPT101B{
private:
    int _pin;
    float _zeroVoltageOffset;

public:
    ZMPT101B(int pin);
    void calibrate();
    float readVoltage();
};

