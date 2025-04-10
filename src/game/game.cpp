#include <Arduino.h>
#include "game/game.h"
#include "game/striker.h"
#include "sensors/sensors.h"

void game() {
    static unsigned long t0, tf, startTime;
    static unsigned long reactTimer = -LINE_REACT_TIME, timer = 0;
    static byte savedLineStatus = 0;

    static int gameState = PLAY;
    static int checkTimeout;
    // driver->brake = false;

    if (lines->status > 0) lines->react();
    else attack();

    // t0 = millis();
    // if (t0 - reactTimer >= LINE_REACT_TIME) {
    //     if (lines->status) {
    //         savedLineStatus = lines->status;
    //         reactTimer = t0;
    //     } else {
    //         attack();
    //     }
    // } else {
    //     lines->react(savedLineStatus);
    //     // lines->react(lines->status);
    //     //driver->speed = 50;
    //     //driver->dir = 0;
    // } 
    // t0 = millis();
    // switch (gameState) {
    // case PLAY:
    //     if (lines->status > 0) {
    //         // savedLineStatus = lines->status;
    //         gameState = STOP;
    //         startTime = millis();
    //     } else {
    //         attack();
    //     }
    //     break;

    // case STOP:
    //     if (t0 - startTime > STOP_TIME) {
    //         gameState = LINE_REACT;
    //         startTime = millis();
    //     } else {
    //         // driver->brake = true;
    //     }
    //     break;

    // case LINE_REACT:
    //         // lines->react(lines->status);

    //     // if (t0 - startTime > LINE_REACT_TIME) {
    //         gameState = PLAY;
    //         // if (lines->status > 0) {
    //         //     savedLineStatus = lines->status;
    //         //     startTime = t0;
    //         // } else {
    //         //     // gameState = PLAY;
    //         // }
    //     // } else {
    //         // lines->react(savedLineStatus);
    //         // lines->react(lines->status);
    //     // }
    //     break;
    
    // default:
    //     break;
    // }
}