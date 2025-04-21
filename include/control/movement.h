#pragma once
#include <PID_v1.h>
#include <Arduino.h>
#include "actuators/motors.h"

#define KP 1.2
#define KI 0.0 
#define KD 0.05

class MovementController {
private:
    double input{0}, output{0}, setPoint{0};
    PID* pid; 

public:
    //motors[0]: M1 ALTO-SX
    //motors[1]: M2 ALTO-DX
    //motors[2]: M3 BASSO-DX
    //motors[3]: M4 BASSO-SX
    Motor* motors[4];

    int dir{0}, speed{0}, orient{0};
    int dx{0}, dy{0}; // Keep in mind that dx indicates forward/backward movement, while dy indicates left/right movement
    bool brake{false};

    MovementController(Motor* m0, Motor* m1, Motor* m2, Motor* m3);
    void move(int dir, int dx, int dy, int speed, int orient, bool brake);
    void move(int dir, int speed, int orient, bool brake);
    void move();
    void stop();
    void test();
};
