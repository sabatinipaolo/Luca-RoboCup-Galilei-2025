#pragma once
#include <Arduino.h>

class Motor {
private:
    int PIN_A, PIN_B, PIN_PWM, ANGLE;

public:
    double ANGLE_COS, ANGLE_SIN;    

    Motor(int PIN_A, int PIN_B, int PIN_PWM, int ANGLE);
    Motor();
    void drive(int speed);
    void test();
    void stop();
};
