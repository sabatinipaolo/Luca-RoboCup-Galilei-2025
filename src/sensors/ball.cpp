#include <Arduino.h>
#include "sensors/ball.h"
#include "sensors/sensors.h"
#include "utility/utility.h"

Ball::Ball() {
    BALL_SERIAL.begin(19200);
}

void Ball::read() {
    while (BALL_SERIAL.available()) {
        String message = BALL_SERIAL.readStringUntil('\n');
        if (message[0] == 'a') relativeAngle = message.substring(1).toInt();
        if (message[0] == 'd') distance = message.substring(1).toInt();
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

