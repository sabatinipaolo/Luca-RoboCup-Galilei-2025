#include "game/game.h"
#include "game/striker.h"
#include "sensors/sensors.h"

void attack() {
    driver->speed = SPEED_ATK;

    // if (attackGoal->seen) {
    //     driver->orient = attackGoal->angle + 8;
    //     if (driver->orient > 45 and driver->orient < 180) driver->orient = 45;
    //     if (driver->orient < 315 and driver->orient > 180) driver->orient = 315;
    // } else {
    //     driver->orient = 0;
    // }
    driver->orient = 0;
    // if      (ball->relativeAngle < 60)  driver->dir = (int)(ball->relativeAngle * (COEFF_ATK - 0.3));
    // else if (ball->relativeAngle > 300) driver->dir = (int)(360 - ((360 - ball->relativeAngle) * (COEFF_ATK + 1.0)));
    // else if (ball->relativeAngle < 160) driver->dir = 180; //170
    // else if (ball->relativeAngle > 200) driver->dir = 180; //190
    // else                                driver->dir = 130;
    
    #ifdef ROCK
    if      (ball->relativeAngle < 30)  driver->dir = (int)(ball->relativeAngle * (COEFF_ATK) + 5);
    else if (ball->relativeAngle > 330) driver->dir = (int)(360 - ((360 - ball->relativeAngle) * (COEFF_ATK)));
    else if (ball->relativeAngle < 160) driver->dir = 160;
    else if (ball->relativeAngle > 200) driver->dir = 200;
    else                                driver->dir = 130;
    #else
    if      (ball->absoluteAngle < 50)  driver->dir = (int)(ball->absoluteAngle * (COEFF_ATK-1.5) - 5);
    else if (ball->absoluteAngle > 310) driver->dir = (int)(360 - ((360 - ball->absoluteAngle) * (COEFF_ATK-1.5)));
    else if (ball->absoluteAngle < 160) driver->dir = 160;
    else if (ball->absoluteAngle > 200) driver->dir = 200;
    else                                driver->dir = 130;
    #endif

    if (!ball->seen) {
        driver->speed = SPEED_ATK;
        driver->dir = 180;
        driver->orient = 0;
    }
}
