#include <Arduino.h>
#include "sensors/sensors.h"
#include "actuators/actuators.h"
#include "control/control.h"
#include "control/movement.h"
#include "behavior/behavior.h"

// #include <Servo.h>
// Servo test;

void setup() {
	delay(1000);
	init_sensors();
	init_actuators();
	init_control();
	pinMode(LED_BUILTIN, OUTPUT); // LOW is ON, HIGH is OFF - Connected to switch2, avoid use

	// test.attach(PB5);
    // test.write(45);
}

void loop() {
	// read_sensors();
	// update_control();
	// behavior();
	// driver->move();

    // test.write(90);
	// delay(1000);
    // test.write(180);
	// delay(1000);
	
	// driver->test(); // Motors test
	// driver->move(0, 0, 0, false); // PID test
	// driver->move(0, 50, 0, false); // Polar movement test
	// driver->move(0, 50, 50, 0 , 0, false); // Cardinal movement test (should move 45°)
	// driver->move(0, 0, 50, 50, 0, false); // Mixed movement test (should move 45°)
	// driver->move(ball->absolute_angle, 70, 0, false); // Ball test
	// driver->move(0, 0, attack_goal->angle, false); // Camera test
}
