#pragma once
#include <PID_v1.h>
#include "./motors.h"

#define KP 1.25 
#define KI 0.0 
#define KD 0.1

class MovementController {
private:
    //STUDIA CHE CAZZO SONO QUESTI :)
    double input;
    double output;
    double setPoint;

    PID* pid;

public:
    //motors[0]: M1 ALTO-SX
    //motors[1]: M1 ALTO-DX
    //motors[2]: M1 BASSO-DX
    //motors[3]: M1 BASSO-SX
    Motor* motors[4];

    MovementController(Motor* m0, Motor* m1, Motor* m2, Motor* m3);
    MovementController();
    void move(int vel, int dir, int orient);
    void stop();
};
