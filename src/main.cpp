#include <Arduino.h>
#include "sensors/sensors.h"
#include "actuators/actuators.h"
#include "control/control.h"
#include "control/movement.h"
#include "behavior/behavior.h"

void setup() {
	delay(1000);
	init_sensors();
	init_actuators();
	init_control();
	pinMode(LED_BUILTIN, OUTPUT); // LOW is ON, HIGH is OFF - Connected to switch2, avoid use
}

void loop() {
	read_sensors();
	update_control();
	behavior();
	update_actuators();
	driver->move();
	if (ball_presence->present) kicker->kick();
	roller->on();

	// driver->test(); // Motors test
	// driver->move(0, 0, 180); // PID test
	// driver->move(0, 50, 0); // Polar movement test
	// driver->move(0, 50, 50, 0 , 0); // Cardinal movement test (should move 45°)
	// driver->move(0, 0, 50, 50, 0); // Mixed movement test (should move 45°)
	// driver->move(ball->absolute_angle, 70, 0); // Ball test
	// driver->move(0, 0, attack_goal->angle); // Camera test
	// kicker->test(); // Kicker test
	// roller->test(); // Roller test
}
