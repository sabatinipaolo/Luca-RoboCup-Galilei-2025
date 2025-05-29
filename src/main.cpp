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
	pinMode(LED_BUILTIN, OUTPUT); // LOW is ON, HIGH is OFF - Connected to switch2, avoid use. might catch fire
}

#include "behavior/bounds.h"
void loop() {
 	read_sensors();
	update_control();
	behavior();

	// roller->on();
	// driver->absolute = true;
	// if (ball_presence->is_in_mouth) {
	// 	driver->speed = 0;
	// } else {
	// 	driver->orient = ball->absolute_angle;
	// 	driver->speed = 50;
	// 	driver->dir = ball->absolute_angle;
	// }

	update_actuators();
	driver->move();
}
