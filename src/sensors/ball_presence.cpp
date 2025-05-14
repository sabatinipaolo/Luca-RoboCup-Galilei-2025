#include <Arduino.h>
#include "sensors/ball_presence.h"
#include "utility/filters.h"
#include "config.h"

BallPresence::BallPresence() {}

void BallPresence::update() {
    value = analogRead(Pins::BALL_PRESENCE);
    value = filter(value, p_value, 0.5);
    p_value = value;
    present = value < BALL_PRESENCE_THRESHOLD;
}
