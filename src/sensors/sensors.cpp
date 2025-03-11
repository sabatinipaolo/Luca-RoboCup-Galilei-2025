#define SENSORS

#include "sensors/sensors.h"
#include "movement/movement.h"
#include "sensors/bno.h"
#include "sensors/lines.h"

void initSensors() {
    driver = new MovementController(
        new Motor(PIN_A_0, PIN_B_0, PIN_VEL_0, 306), //M1 ALTO/SX
        new Motor(PIN_A_1, PIN_B_1, PIN_VEL_1, 54), //M2 ALTO/DX
        new Motor(PIN_A_2, PIN_B_2, PIN_VEL_2, 135), //M3 BASSO/DX
        new Motor(PIN_A_3, PIN_B_3, PIN_VEL_3, 225) //M4 BASSO/SX
    );
    compass = new BNO();
    lines = new Lines();
}

void readSensors() {
    compass->read();
    lines->read();
}
