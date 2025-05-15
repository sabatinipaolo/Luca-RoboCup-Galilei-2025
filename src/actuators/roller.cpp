#include <Servo.h>
#include "actuators/roller.h"
#include "config.h"

Roller::Roller() {
    servo.attach(Pins::ROLLER);
}

void Roller::on() {
    servo.writeMicroseconds(microseconds);
}

void Roller::off() {
    servo.writeMicroseconds(1500);
}

void Roller::setSpeed(int speed) {
    microseconds = map(speed, 0, 100, 1500, 1700);
}

void Roller::test() {
    setSpeed(100);
    on();
    delay(2000);

    setSpeed(50);
    on();
    delay(2000);

    setSpeed(25);
    on();
    delay(2000);

    setSpeed(0);
    on();
    delay(1000);
    off();
    delay(1000);
}
