#include <Arduino.h>
#include <HardwareSerial.h>
#include "movement/movement.h"
#include "sensors/sensors.h"

#if !defined(HAVE_HWSERIAL2) && defined(USART2_ENABLED)
HardwareSerial Serial2(USART2);
#endif

// String read;

void setup() {
		// Enable USART2 clock
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	__DSB(); // Data synchronization barrier
	pinMode(LED_BUILTIN, OUTPUT); // LOW is ON, HIGH is OFF
	digitalWrite(LED_BUILTIN, LOW); // Turn on LED to indicate power

    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
	// initSensors();
	// Serial1.begin(19200);
	Serial2.begin(57600);
	while(!Serial2); // Wait for serial port to connect

	// Blink LED to indicate setup complete
	for(int i=0; i<3; i++) {
		digitalWrite(LED_BUILTIN, HIGH);
		delay(100);
		digitalWrite(LED_BUILTIN, LOW);
		delay(100);
	}
}

void loop() {
	// readSensors();
	// digitalWrite(LED_BUILTIN, HIGH);
	// delay(1000);
	// digitalWrite(LED_BUILTIN, LOW);
	// delay(1000);
	// driver->move(0, 0, 45);
	// driver->test();
	// while (Serial1.available() > 0) {
    //     read = Serial1.readString();
    // }
	if(Serial2.available()) {
		digitalWrite(LED_BUILTIN, HIGH); // Turn off LED when receiving
		char c = Serial2.read();
		// Simple echo - send back what we received
		Serial2.write(c);
		digitalWrite(LED_BUILTIN, LOW); // Turn on LED after
	}
}
