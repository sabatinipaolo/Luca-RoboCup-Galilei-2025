#include <Arduino.h>
#include "sensors/sensors.h"
#include "control/control.h"
#include "control/movement.h"
#include "behavior/behavior.h"

void setup() {
	delay(1000);
	init_sensors();
	init_control();
	pinMode(LED_BUILTIN, OUTPUT); // LOW is ON, HIGH is OFF - Connected to switch2, avoid use
}

void loop() {
   	read_sensors();
	behavior();
	driver->move();

	// driver->test(); // Motors test
	// driver->move(0, 0, 0, false); // PID test
	// driver->move(0, 50, 0, false); // Movement test
	// driver->move(0, 0, 50, 50, 0, false); // Mixed movement test (should move 45°)
	// driver->move(ball->absolute_angle, 70, 0, false); // Ball test
	// driver->move(0, 0, attack_goal->angle, false); // Camera test
}
