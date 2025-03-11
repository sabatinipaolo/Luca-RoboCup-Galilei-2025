#pragma once
#include <Adafruit_BNO055.h>

class BNO {
private:
    Adafruit_BNO055 bno;
    int STARTING_ANGLE, p_angle;

public:
    int angle;
    BNO();
    void read();
};
