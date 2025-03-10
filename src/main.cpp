#include <Arduino.h>
#include "movement/movement.h"
#include "sensors/sensors.h"

void setup() {
	initSensors();
}

void loop() {
	readSensors();
	// driver->motors[0]->test();
	// driver->motors[1]->test();
	// driver->motors[2]->test();
	// driver->motors[3]->test();
}
