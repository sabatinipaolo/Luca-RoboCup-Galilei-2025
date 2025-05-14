#include "sensors/sensors.h"
#include "control/control.h"
#include "behavior/behavior.h"
#include "behavior/striker.h"
#include "behavior/bounds.h"
#include "config.h"

void striker() {
    static unsigned long start_time;
    static byte game_state = PLAY, saved_status;
    
    switch (game_state) {
    case PLAY:
        if (lines->status) {
            saved_status = lines->status;
            game_state = STOP;
            start_time = millis();
        } else {
            attack();
        }
        break;

    case STOP:
        if (millis() - start_time >= STOP_TIME) {
            game_state = LINE_REACT;
            start_time = millis();
        } else {
            driver->brake = true;
        }
        break;

    case LINE_REACT:
        if (millis() - start_time >= LINE_REACT_TIME) {
            if (lines->status) {
                saved_status = lines->status;
                start_time = millis();
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
    driver->speed = GAME_SPEED;
    driver->orient = 0;

    // BALL
    if (ball->distance < BALL_CLOSE) driver->dir = ball->relative_angle;

    else if (ball->relative_angle < 30)  driver->dir = ball->relative_angle * 2;
    else if (ball->relative_angle > 330) driver->dir = 360 - ((360 - ball->relative_angle) * 2);

    else if (ball->relative_angle < 90)  driver->dir = ball->relative_angle * 2.2;
    else if (ball->relative_angle > 180) driver->dir = 360 - ((360 - ball->relative_angle) * 2.5);

    else if (ball->relative_angle < 160) driver->dir = 160;
    else if (ball->relative_angle > 200) driver->dir = 200;

    else {
        if (!attack_goal->seen) driver->dir = 130;
        else driver->dir = (attack_goal->angle < 180) ? 130 : 230;
    }

    if (!ball->seen) {
        driver->speed = 0;
        driver->dir = 180;
    }

    // CAMERA
    if (attack_goal->seen) {
        driver->orient = attack_goal->angle;
        if (driver->orient < 180) driver->orient = driver->orient * 1.25;
        else driver->orient = 360 - ((360 - driver->orient) * 1.25);

        if (driver->orient > 45 and driver->orient < 180) driver->orient = 45;
        if (driver->orient < 315 and driver->orient > 180) driver->orient = 315;
    } else {
        driver->orient = 0;
    }
}
