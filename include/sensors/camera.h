#pragma once

#define YELLOW_GOAL 0
#define BLUE_GOAL 1

#define GOAL_SWITCH SWITCH_2

void readMV();

class Camera {
public:
    int angle{999}, p_angle{0}, raw_angle{999};
    int area{-1}, p_area{0}, raw_area{-1};
    bool seen{false};

    Camera();
    void update();
};
