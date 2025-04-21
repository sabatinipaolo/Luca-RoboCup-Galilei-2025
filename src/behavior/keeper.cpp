#include <Arduino.h>
#include "sensors/sensors.h"
#include "control/control.h"
#include "behavior/bounds.h"
#include "behavior/striker.h"
#include "behavior/keeper.h"

void keeper() {
    static unsigned long start_time;
    unsigned long t0 = millis();
    static byte game_state = DEFEND;
    
    switch (game_state) {
    case DEFEND:
        if (ball->distance < BALL_CLOSE and t0 - start_time > REST_TIME) {
            game_state = GET_IN_ACTION;
        } else {
            defend();
        }
        break;

    case GET_IN_ACTION:
        if (!lines->status) {
            game_state = SAVE;
            start_time = t0;
        } else {
            save();
        }
        break;

    case SAVE:
        if (lines->status or ball->distance > BALL_CLOSE or t0 - start_time > SAVE_TIME) {
            game_state = DEFEND;
            start_time = t0;
        } else {
            save();
        }
        break;
    
    default:
        break;
    }
}

void defend() {
    // GO TO GOAL
    driver->orient = 0;
    driver->speed = SPEED_ATK/2;

    if (!defence_goal->seen) driver->dir = 180;
    else if (defence_goal->angle > 90 and defence_goal->angle < 145) driver->dir = 55;
    else if (defence_goal->angle > 215 and defence_goal->angle < 270) driver->dir = 315;

    // STAY AT GOAL
    else {
        if (!lines->status) driver->dir = 180;
        else driver->speed = 0;

        stay_on_line(lines->status);

        if (ball->absolute_angle < 90) driver->dy = map(ball->absolute_angle, 0, 90, SPEED_ATK/2, SPEED_ATK*2);
        if (ball->absolute_angle > 270) driver->dy = -map(ball->absolute_angle, 270, 360, SPEED_ATK*2, SPEED_ATK/2);
    }
}

void save() {
    driver->dir = ball->absolute_angle;
    driver->speed = SPEED_ATK;
    driver->orient = ball->absolute_angle;
    if (driver->orient > 90 and driver->orient <= 180) driver->orient = 90;
    if (driver->orient < 270 and driver->orient > 180) driver->orient = 270;
}
