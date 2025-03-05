#include <Arduino.h>
#include "../include/movement/motors.h"

Motor motor0(PIN_A_0, PIN_B_0, PIN_VEL_0, 0); //M1 ALTO/SX
Motor motor1(PIN_A_1, PIN_B_1, PIN_VEL_1, 0); //M2 ALTO/DX
Motor motor2(PIN_A_2, PIN_B_2, PIN_VEL_2, 0); //M3 BASSO/DX
Motor motor3(PIN_A_3, PIN_B_3, PIN_VEL_3, 0); //M4 BASS/SX

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);

	digitalWrite(LED_BUILTIN, LOW);
	delay(1000);
	digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
	motor0.test();
	motor1.test();
	motor2.test();
	motor3.test();
}
