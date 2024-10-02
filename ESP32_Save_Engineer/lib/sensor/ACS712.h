#ifndef ACS712_H
#define ACS712_H

#include <Arduino.h>

class ACS712 {
public:
    ACS712(int pin, float sensitivity, float v_ref);
    void calibrate();           // Hiệu chỉnh để tìm offset khi không có dòng điện
    float readCurrent();        // Đọc giá trị dòng điện hiện tại

private:
    int _pin;
    float _sensitivity;
    float _v_ref;
    float _zeroCurrentOffset;
};

#endif
