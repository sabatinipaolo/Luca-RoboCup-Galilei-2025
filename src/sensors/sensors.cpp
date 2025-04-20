#define SENSORS

#include "sensors/sensors.h"

void init_sensors() {
    compass = new BNO();
    lines = new Lines();
    ball = new Ball();
    attack_goal = new Camera();
    defence_goal = new Camera();
}

void read_sensors() {
    compass->read();
    lines->read();
    ball->read();
    readMV();
    attack_goal->update();
    defence_goal->update();
}
