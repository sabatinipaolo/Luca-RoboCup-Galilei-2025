#include <Arduino.h>
#include <HardwareSerial.h>
#include "movement/movement.h"
#include "sensors/sensors.h"

// #if !defined(HAVE_HWSERIAL2) && defined(USART2_ENABLED)
// HardwareSerial Serial1(PA10, PA9);
HardwareSerial Serial2(USART2);
HardwareSerial Serial3(USART3);
// #endif

// String read;
// PA3 PA2
void setup() {
		// Enable USART2 clock
	// RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	// __DSB(); // Data synchronization barrier
	pinMode(LED_BUILTIN, OUTPUT); // LOW is ON, HIGH is OFF
	digitalWrite(LED_BUILTIN, LOW); // Turn on LED to indicate power

    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
	// initSensors();
	// Serial1.begin(19200);
	// Serial2.begin(19200);
	// Serial1.begin(9600); //TX-PA9/RX-PA10
	Serial2.begin(9600); //TX-PA2/RX-PA3
	Serial3.begin(9600); //TX-PB10/RX-PB11
	Serial.begin(9600); //USB (PA11/PA12)
	// while(!Serial2); // Wait for serial port to connect

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
	// if(Serial1.available()) {
	// 	digitalWrite(LED_BUILTIN, HIGH); // Turn off LED when receiving
	// 	char c = Serial1.read();
	// 	// Simple echo - send back what we received
	// 	Serial.print(c);
	// 	digitalWrite(LED_BUILTIN, LOW); // Turn on LED after
	// }
	// if(Serial2.available()) {
	// 	digitalWrite(LED_BUILTIN, HIGH); // Turn off LED when receiving
	// 	char c = Serial2.read();
	// 	// Simple echo - send back what we received
	// 	Serial.print(c);
	// 	digitalWrite(LED_BUILTIN, LOW); // Turn on LED after
	// }
	// if(Serial3.available()) {
	// 	digitalWrite(LED_BUILTIN, HIGH); // Turn off LED when receiving
	// 	char c = Serial3.read();
	// 	// Simple echo - send back what we received
	// 	Serial.print(c);
	// 	digitalWrite(LED_BUILTIN, LOW); // Turn on LED after
	// }
}
