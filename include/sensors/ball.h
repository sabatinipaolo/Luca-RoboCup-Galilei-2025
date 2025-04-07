#pragma once

#define BALL_TX PB10
#define BALL_RX PB11

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
