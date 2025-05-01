#include "sensors/sensors.h"
#include "control/control.h"
#include "behavior/striker.h"
#include "behavior/bounds.h"
#include "config.h"

void striker() {
    static unsigned long start_time;
    unsigned long t0 = millis();
    static byte game_state = PLAY, saved_status;
    
    switch (game_state) {
    case PLAY:
        if (lines->status) {
            saved_status = lines->status;
            game_state = STOP;
            start_time = t0;
        } else {
            attack();
        }
        break;

    case STOP:
        if (t0 - start_time > STOP_TIME) {
            game_state = LINE_REACT;
            start_time = t0;
            driver->brake = false;
        } else {
            driver->brake = true;
        }
        break;

    case LINE_REACT:
        if (t0 - start_time > LINE_REACT_TIME) {
            if (lines->status) {
                saved_status = lines->status;
                start_time = t0;
            } else {
                game_state = PLAY;
                driver->dx = 0;
                driver->dy = 0;
            }
        } else {
            attack();
            line_react(saved_status);
        }
        break;
    
    default:
        break;
    }
}

void attack() {
    driver->speed = SPEED_ATK;
    driver->orient = 0;

    // BALL
    #ifdef ROCK
    if      (ball->relative_angle < 30)  driver->dir = (int)(ball->relative_angle * (3) + 5);
    else if (ball->relative_angle > 330) driver->dir = (int)(360 - ((360 - ball->relative_angle) * (3)));
    else if (ball->relative_angle < 160) driver->dir = 160;
    else if (ball->relative_angle > 200) driver->dir = 200;
    else                                 driver->dir = 130;
    #else
    if      (ball->absolute_angle < 50)  driver->dir = (int)(ball->absolute_angle * (1.5) - 5);
    else if (ball->absolute_angle > 310) driver->dir = (int)(360 - ((360 - ball->absolute_angle) * (1.5)));
    else if (ball->absolute_angle < 160) driver->dir = 160;
    else if (ball->absolute_angle > 200) driver->dir = 200;
    else                                 driver->dir = 130;
    #endif

    if (!ball->seen) {
        driver->speed = SPEED_ATK;
        driver->speed = 0;
        driver->dir = 180;
    }

    // CAMERA
    if (attack_goal->seen) {
        driver->orient = attack_goal->angle;
        if (driver->orient > 45 and driver->orient < 180) driver->orient = 45;
        if (driver->orient < 315 and driver->orient > 180) driver->orient = 315;
    } else {
        driver->orient = 0;
    }
}
