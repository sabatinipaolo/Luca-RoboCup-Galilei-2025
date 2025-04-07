#include <Arduino.h>
#include "movement/movement.h"
#include "sensors/sensors.h"

void setup() {
	initSensors();
	pinMode(LED_BUILTIN, OUTPUT); // LOW is ON, HIGH is OFF - Connected to switch2, avoid use
}

void loop() {
	readSensors();
	driver->move(0, 0, 0); // PID test
    // driver->move(0, 0, ball->absoluteAngle); // Ball test
	// driver->test();
}
