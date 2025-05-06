#include <Arduino.h>
#include "sensors/sensors.h"
#include "control/control.h"
#include "behavior/bounds.h"
#include "behavior/behavior.h"
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
        } else {
            goto_goal();
        }
        break;

    case DEFEND:
        if (ball->seen and ball->distance > BALL_CLOSE) {
            game_state = PARRY;
            start_time = t0;
        } else if (t0 - start_time > IDLE_TIME) {
            game_state = RESET;
        } else {
            if (lines->status) start_time = t0;
            defend();
        }
        break;

    case PARRY:
        if (ball->distance < BALL_CLOSE or t0 - start_time > SAVE_TIME) {
            game_state = RESET;
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
    driver->speed = SETUP_SPEED;

    if (!defence_goal->seen) driver->dir = 180;
    else if (defence_goal->angle > 90 and defence_goal->angle < 160) driver->dir = 55;
    else if (defence_goal->angle > 200 and defence_goal->angle < 270) driver->dir = 315;
    else driver->dir = 180;
}

void defend() {
    // driver->orient = (defence_goal->angle + 180) % 360;
    // driver->orient = (ball->seen) ? ball->absolute_angle : 0;
    driver->orient = 0;
    driver->absolute = true;
    driver->speed = 0;

    if (!ball->seen or (ball->absolute_angle > 10 and ball->absolute_angle < 350)) stay_on_line(lines->status);

    if (ball->absolute_angle < 90) driver->dy = map(ball->absolute_angle, 0, 90, GAME_SPEED/2, GAME_SPEED*4);
    if (ball->absolute_angle > 270) driver->dy = -map(ball->absolute_angle, 270, 360, GAME_SPEED*4, GAME_SPEED/2);
    if (!ball->seen or defence_goal->angle > 220 or defence_goal->angle < 140 ) driver->dy = 0;
}

void save() {
    driver->speed = GAME_SPEED;
    driver->orient = 0;

    if      (ball->absolute_angle < 90)  driver->dir = ball->absolute_angle * 1.5;
    else if (ball->absolute_angle > 270) driver->dir = (360 - ((360 - ball->relative_angle) * 1.5));
    else driver->speed = 0;
}
