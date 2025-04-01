#include <Arduino.h>
#include "movement/movement.h"
#include "sensors/sensors.h"

void setup() {
	initSensors();
}

void loop() {
	readSensors();
	driver->move(0, 0, 45);
	// driver->test();
}
