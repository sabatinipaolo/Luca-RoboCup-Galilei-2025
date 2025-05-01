#include <Arduino.h>
#include "sensors/sensors.h"
#include "control/control.h"
#include "behavior/bounds.h"
#include "behavior/striker.h"
#include "behavior/keeper.h"

void keeper() {
    static unsigned long start_time;
    unsigned long t0 = millis();
    static byte game_state = RESET;
    
    switch (game_state) {
    case RESET:
        if (lines->status) {
            game_state = DEFEND;
            start_time = t0;
            driver->speed = 0;
        } else {
            goto_goal();
        }
        break;

    case DEFEND:
        if (ball->seen and ball->distance > BALL_CLOSE) {
            game_state = GET_IN_ACTION;
        } else if (t0 - start_time > IDLE_TIME) {
            game_state = RESET;
        } else {
            if (lines->status) start_time = t0;
            defend();
        }
        break;

    case GET_IN_ACTION:
        if (!lines->status) {
            game_state = PARRY;
            start_time = t0;
        } else {
            save();
        }
        break;

    case PARRY:
        if (lines->status or ball->distance > BALL_CLOSE or t0 - start_time > SAVE_TIME) {
            game_state = RESET;
            // start_time = t0;
        } else {
            save();
        }
        break;
    
    default:
        break;
    }
}

void goto_goal() {
    driver->orient = 0;
    driver->speed = SPEED_ATK;

    if (!defence_goal->seen) driver->dir = 180;
    else if (defence_goal->angle > 90 and defence_goal->angle < 160) driver->dir = 55;
    else if (defence_goal->angle > 200 and defence_goal->angle < 270) driver->dir = 315;
    else driver->dir = 180;
}

void defend() {
    // driver->orient = (defence_goal->angle + 180) % 360;
    driver->orient = 0;
    driver->speed = 0;
    stay_on_line(lines->status);

    if (ball->absolute_angle < 90) driver->dy = map(ball->absolute_angle, 0, 90, SPEED_ATK, SPEED_ATK*4);
    if (ball->absolute_angle > 270) driver->dy = -map(ball->absolute_angle, 270, 360, SPEED_ATK*4, SPEED_ATK);
    if (!ball->seen or defence_goal->angle > 220 or defence_goal->angle < 140) driver->dy = 0;
}

void save() {
    driver->dir = ball->absolute_angle;
    driver->speed = SPEED_ATK;
    driver->orient = ball->absolute_angle;
    if (driver->orient > 90 and driver->orient <= 180) driver->orient = 90;
    if (driver->orient < 270 and driver->orient > 180) driver->orient = 270;
}
