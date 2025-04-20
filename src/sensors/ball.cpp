#include <Arduino.h>
#include "sensors/sensors.h"
#include "sensors/ball.h"
#include "utility/filters.h"
#include "config.h"

Ball::Ball() {
    BallSerial = new HardwareSerial(Pins::ESP32_RX, Pins::ESP32_TX);
    BallSerial->begin(57600);
}

void Ball::read() {
    while (BallSerial->available()) {
        String message = BallSerial->readStringUntil('b'); 
        relative_angle = message.substring(message.lastIndexOf("B")+1, message.indexOf("-")).toInt();
        distance = message.substring(message.lastIndexOf("-")+1).toInt();
    }

    relative_angle = filter_angle(relative_angle, p_angle, 0.45);
    p_angle = relative_angle;

    absolute_angle = (int)(relative_angle + compass->angle) % 360;

    distance = filter(distance, p_distance, 0.5);
    p_distance = distance;

    seen = distance > 0;
}
