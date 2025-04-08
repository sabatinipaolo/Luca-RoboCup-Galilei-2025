#include <Arduino.h>
#include "game/game.h"
#include "game/striker.h"
#include "sensors/sensors.h"

void game() {
    static unsigned long t0, tf, startTime;
    static unsigned long reactTimer = 0;

    static byte status = PLAY;
    static byte checkTimeout;

    if (millis() - reactTimer > LINE_REACT_TIME) {
        lines->read();
        if (lines->status) reactTimer = millis();
        else attack();
    } else {
        lines->react();
    }

    // t0 = millis();
    // switch (status) {
    //     case PLAY:
    //         if (lines->status) { // Line is detected
    //             // status = STOP;
    //             // tf = t0 + STOP_TIME;
    //             startTime = millis();
    //             lines->react();
    //         } else {
    //             attack();
    //         }
    //     break;

    //     case STOP:
    //         if (tf < t0) { // Timer has passed
    //             status = LINE_REACT;
    //             tf = t0 + LINE_REACT_TIME;

    //             startTime = millis();
    //             lines->react();
    //         } else {
    //             driver->stop();
    //         }
    //     break;

    //     case LINE_REACT:
    //         if (millis() - startTime > LINE_REACT_TIME) { // Timer has passed
    //             if (lines->status) { // Line is detected
    //                 // tf = t0 + LINE_CHECK_TIME;
    //                 // status = LINE_CHECK;
    //                 // checkTimeout = 0;


    //                 // tf = t0 + LINE_REACT_TIME;
    //                 // status = LINE_REACT;

    //                 startTime = millis();
    //                 lines->react();
    //             } else {
    //                 status = PLAY;
    //             }
    //         } else {
    //             lines->react();
    //             // driver->speed = SPEED_LINE_REACT;
    //             // driver->speed = map((millis() - t0), 0, tf, 60, MAX_SPEED_LINE_REACT);
    //         }
    //     break;

    //     case LINE_CHECK:
    //         lines->status = 0;
    //         if (t0 > tf) { // Timer hasn't passed
    //             lines->read();
    //             if (lines->status and checkTimeout < 3) {
    //                 tf = t0 + LINE_CHECK_TIME;
    //                 checkTimeout++;
    //             } else {
    //                 checkTimeout = 0;
    //                 status = PLAY;
    //                 lines->status = 0;
    //             }
    //         }
    //     break;

    //     default:
    //     break;
    // }
}