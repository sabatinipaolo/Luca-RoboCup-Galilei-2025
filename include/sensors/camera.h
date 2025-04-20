#pragma once

#define YELLOW_GOAL 0
#define BLUE_GOAL 1

void readMV();

class Camera {
public:
    int angle{999}, p_angle{0}, raw_angle{999};
    int area{999}, p_area{0}, raw_area{999};
    bool seen{false};

    Camera();
    void update();
};
