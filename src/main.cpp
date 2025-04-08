#include <Arduino.h>
#include "movement/movement.h"
#include "sensors/sensors.h"
#include "game/game.h"

void setup() {
	initSensors();
	pinMode(LED_BUILTIN, OUTPUT); // LOW is ON, HIGH is OFF - Connected to switch2, avoid use
}

void loop() {
	readSensors();
	// game();
    // driver->move();

	// driver->move(0, 50, 0);
	// driver->move(ball->absoluteAngle, 70, 0);
	driver->move(0, 0, 0); // PID test
    // driver->move(0, 0, ball->absoluteAngle); // Ball test
	// driver->test();
}
