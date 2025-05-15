#pragma once
#include <Servo.h>

class Roller {
private: 
    int microseconds{1300};
public:
    Servo servo;
    
    Roller();
    void on();
    void off();
    void setSpeed(int speed);
    void test();
};
