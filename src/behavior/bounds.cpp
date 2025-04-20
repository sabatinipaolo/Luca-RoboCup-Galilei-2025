#include "control/control.h"
#include "behavior/bounds.h"
#include "utility/transformations.h"

void line_react(byte readStatus) {
    #ifdef POLAR
    driver->speed = SPEED_LINE_REACT;

    int dirX = 0;
    int dirY = 0;

    if (((readStatus & 0b10000000) >> 7) == 1) dirY -= 100;
    if (((readStatus & 0b01000000) >> 6) == 1) dirY -= 150;
    if (((readStatus & 0b00100000) >> 5) == 1) dirX -= 100;
    if (((readStatus & 0b00010000) >> 4) == 1) dirX -= 150;
    if (((readStatus & 0b00001000) >> 3) == 1) dirY += 100;
    if (((readStatus & 0b00000100) >> 2) == 1) dirY += 150;
    if (((readStatus & 0b00000010) >> 1) == 1) dirX += 100;
    if (((readStatus & 0b00000001) >> 0) == 1) dirX += 150;

    driver->dir = toGrad(atan2((double)dirX, (double)dirY));
    #endif
}

void stay_on_line(byte readStatus) {

}

