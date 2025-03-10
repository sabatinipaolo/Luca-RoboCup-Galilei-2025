#include "sensors/sensors.h"
#include "movement/movement.h"
#include "sensors/bno.h"

void initSensors() {
    driver = new MovementController();
    compass = new BNO();
}

void readSensors() {
    compass->read();
}
