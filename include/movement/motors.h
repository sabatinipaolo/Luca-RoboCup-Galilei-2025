#pragma once
#include <Arduino.h>

// Bluepill
#define PIN_A_0 PB12
#define PIN_B_0 PB13
#define PIN_VEL_0 PB1

#define PIN_A_1 PB14
#define PIN_B_1 PB15
#define PIN_VEL_1 PB0

#define PIN_A_2 PA11
#define PIN_B_2 PA12
#define PIN_VEL_2 PB9

#define PIN_A_3 PA15
#define PIN_B_3 PB3
#define PIN_VEL_3 PB8

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
