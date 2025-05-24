#include "sensors/sensors.h"
#include "actuators/actuators.h"
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
    if (!ball_presence->is_in_mouth) {
        driver->dir = ball->absolute_angle;
        driver->speed = GAME_SPEED;
        driver->orient = ball->absolute_angle;
        driver->absolute = true;
        if (is_ball_close(ball->distance)) roller->on();
    } else {
        driver->dir = attack_goal->angle;
        driver->speed = GAME_SPEED;
        driver->orient = attack_goal->angle;
        driver->absolute = true;
        driver->pid_limit = 100;

        if (is_goal_visible(attack_goal->area)) {
            roller->off();
            kicker->kick();
            driver->dir = 180;
        }
    }
}
