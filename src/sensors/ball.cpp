#include <Arduino.h>
#include "sensors/ball.h"
#include "sensors/sensors.h"
#include "utility/utility.h"

Ball::Ball() {
    BallSerial = new HardwareSerial(BALL_RX, BALL_TX);
    BallSerial->begin(57600);

    relativeAngle = 0;
    absoluteAngle = 0;
    distance = 0;

    p_angle = 0;
    p_distance = 0;

    seen = false;
}

void Ball::read() {
    while (BallSerial->available()) {
        String message = BallSerial->readStringUntil('b'); 
        relativeAngle = message.substring(message.lastIndexOf("B")+1, message.indexOf("-")).toInt();
        distance = message.substring(message.lastIndexOf("-")+1).toInt();
    }

    relativeAngle = filter_angle(relativeAngle, p_angle, 0.45);
    p_angle = relativeAngle;

    absoluteAngle = (int)(relativeAngle + compass->angle) % 360;

    distance = filter(distance, p_distance, 0.5);
    p_distance = distance;

    seen = distance > 0;
}

void Ball::test() {
    driver->move(0, 0, absoluteAngle);
}

