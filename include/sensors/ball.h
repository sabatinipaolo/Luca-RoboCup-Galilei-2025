#pragma once

#define BALL_SERIAL Serial3

class Ball {
private:
    int p_angle, p_distance;

public:
    int relativeAngle, absoluteAngle, distance;
    bool seen;

    Ball();
    void read();
    void test();
};
