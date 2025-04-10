#pragma once

#define GOAL_SWITCH_PIN PC13
#define YELLOW_GOAL 0
#define BLUE_GOAL 1

#define CAMERA_TX PA9
#define CAMERA_RX PA10

void readMV();

class Camera {
public:
    int angle, p_angle, raw_angle;
    int area, p_area, raw_area;
    bool seen;

    Camera();
    void update();
};
