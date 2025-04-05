#include <Arduino.h>
#include "sensors/ball.h"
#include "sensors/sensors.h"
#include "utility/utility.h"

Ball::Ball() {
    BALL_SERIAL.begin(19200);
}

void Ball::read() {
    // byte prefix;
    while (BALL_SERIAL.available()) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        // prefix = BALL_SERIAL.read();
        // if (prefix != 'a' and prefix != 'd') continue;

        // String data = "";
        // data += BALL_SERIAL.readString();
        // data += BALL_SERIAL.readString();
        // data += BALL_SERIAL.readString();

        // if (prefix == 'a') relativeAngle = data.toInt();
        // if (prefix == 'd') distance = data.toInt();

        String message = BALL_SERIAL.readStringUntil('e');
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

