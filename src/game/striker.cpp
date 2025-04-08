#include "game/game.h"
#include "game/striker.h"
#include "sensors/sensors.h"

void attack() {
    driver->speed = SPEED_ATK;
    driver->orient = 0;

    if      (ball->relativeAngle < 60)  driver->dir = (int)(ball->relativeAngle * (COEFF_ATK - 0.3));
    else if (ball->relativeAngle > 300) driver->dir = (int)(360 - ((360 - ball->relativeAngle) * (COEFF_ATK + 1.0)));
    else if (ball->relativeAngle < 160) driver->dir = 180; //170
    else if (ball->relativeAngle > 200) driver->dir = 180; //190
    else                                driver->dir = 130;

    //TEST LINES
    driver->dir = ball->absoluteAngle;
}
