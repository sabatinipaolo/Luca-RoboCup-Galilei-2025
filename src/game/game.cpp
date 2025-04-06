#include <Arduino.h>
#include "game/game.h"
#include "game/striker.h"
#include "sensors/sensors.h"

void game() {
    static unsigned long t0, tf;
    static byte status = PLAY;
    static byte checkTimeout;

    t0 = millis();
    switch (status) {
        case PLAY:
            if (lines->status) { // Line is detected
                status = STOP;
                tf = t0 + STOP_TIME;
            } else {
                attack();
            }
        break;

        case STOP:
            if (tf < t0) { // Timer has passed
                status = LINE_REACT;
                tf = t0 + LINE_REACT_TIME;
                lines->react();
            } else {
                driver->stop();
            }
        break;

        case LINE_REACT:
            if (tf < t0) { // Timer has passed
                lines->status = 0;
                lines->read();
                
                if (lines->status) { // Line is detected
                    tf = t0 + LINE_CHECK_TIME;
                    status = LINE_CHECK;
                    checkTimeout = 0;
                } else {
                    status = PLAY;
                }
            } else {
                lines->react();
                driver->speed = map((millis() - t0), 0, tf, 60, MAX_SPEED_LINE_REACT);
            }
        break;

        case LINE_CHECK:
            lines->status = 0;
            if (t0 > tf) { // Timer hasn't passed
                lines->read();
                if (lines->status and checkTimeout < 3) {
                    tf = t0 + LINE_CHECK_TIME;
                    checkTimeout++;
                } else {
                    checkTimeout = 0;
                    status = PLAY;
                    lines->status = 0;
                }
            }
        break;

        default:
        break;
    }

    driver->move();
}