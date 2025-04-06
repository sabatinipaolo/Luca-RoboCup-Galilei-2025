#include <Arduino.h>
#include "movement/movement.h"
#include "sensors/sensors.h"

void setup() {
	initSensors();
	pinMode(LED_BUILTIN, OUTPUT); // LOW is ON, HIGH is OFF
}

void loop() {
	readSensors();
	// driver->move(0, 0, 45);
	// driver->test();
}
