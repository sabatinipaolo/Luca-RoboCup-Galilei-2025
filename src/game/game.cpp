#include <Arduino.h>
#include "game/game.h"
#include "game/striker.h"
#include "sensors/sensors.h"

void game() {
    static unsigned long startTime = -LINE_REACT_TIME;
    static byte gameState = PLAY;

    // INCREDIBLY SIMPLE GAME LOGIC - I HOPE YOU WON'T HAVE TO USE IT
    // if (lines->status > 0) lines->react(lines->status);
    // else attack();

    // SIMPLE GAME LOGIC - MISSING BRAKE LOGIC
    // unsigned long t0 = millis();
    // if (t0 - startTime >= LINE_REACT_TIME) {
    //     if (lines->status) {
    //         lines->savedStatus = lines->status;
    //         startTime = t0;
    //     } else {
    //         attack();
    //     }
    // } else {
    //     lines->react(lines->savedStatus);
    //     // lines->react(lines->status);
    // }

    // ADVANCED GAME LOGIC
    unsigned long t0 = millis();
    switch (gameState) {
    case PLAY:
        if (lines->status) {
            lines->savedStatus = lines->status;
            gameState = STOP;
            startTime = t0;
        } else {
            attack();
        }
        break;

    case STOP:
        if (t0 - startTime > STOP_TIME) {
            gameState = LINE_REACT;
            startTime = t0;
            driver->brake = false;
        } else {
            driver->brake = true;
        }
        break;

    case LINE_REACT:
        if (t0 - startTime > LINE_REACT_TIME) {
            if (lines->status) {
                lines->savedStatus = lines->status;
                startTime = t0;
            } else {
                gameState = PLAY;
            }
        } else {
            lines->react(lines->savedStatus);
            // lines->react(lines->status);
        }
        break;
    
    default:
        break;
    }
}