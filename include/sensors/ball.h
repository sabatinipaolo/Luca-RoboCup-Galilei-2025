#pragma once

#define BALL_CLOSE 350

class Ball {
private:
    int p_angle{0}, p_distance{0};

public:
    int relative_angle{0}, absolute_angle{0}, distance{0};
    bool seen{false};

    Ball();
    void read();
};
