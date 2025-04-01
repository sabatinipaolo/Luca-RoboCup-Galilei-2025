#include <Arduino.h>
#include "sensors/ball.h"
#include "sensors/sensors.h"
#include "utility/utility.h"

Ball::Ball() {
    BALL_SERIAL.begin(57600);
}

void Ball::read() {
    while (BALL_SERIAL.available() > 0) {
        byte read = BALL_SERIAL.read();
        if (read == 'A') relativeAngle = BALL_SERIAL.parseInt();
        if (read == 'D') distance = BALL_SERIAL.parseInt();
        seen = distance < 255;
    }

    relativeAngle = filter_angle(relativeAngle, p_angle, 0.45);
    p_angle = relativeAngle;

    absoluteAngle = (int)(relativeAngle + compass->angle) % 360;

    distance = filter(distance, p_distance, 0.5);
    p_distance = distance;
}

void Ball::test() {
    driver->move(0, 0, absoluteAngle);
}

