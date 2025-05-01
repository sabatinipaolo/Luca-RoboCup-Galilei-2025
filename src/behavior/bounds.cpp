#include "control/control.h"
#include "behavior/bounds.h"
#include "utility/transformations.h"

void line_react(byte readStatus) {
    #ifdef POLAR
    driver->speed = SPEED_LINE_REACT;

    int dirX = 0;
    int dirY = 0;

    if (((readStatus & 0b10000000) >> 7) == 1) dirX -= 100;
    if (((readStatus & 0b01000000) >> 6) == 1) dirX -= 150;
    if (((readStatus & 0b00100000) >> 5) == 1) dirY -= 100;
    if (((readStatus & 0b00010000) >> 4) == 1) dirY -= 150;
    if (((readStatus & 0b00001000) >> 3) == 1) dirX += 100;
    if (((readStatus & 0b00000100) >> 2) == 1) dirX += 150;
    if (((readStatus & 0b00000010) >> 1) == 1) dirY += 100;
    if (((readStatus & 0b00000001) >> 0) == 1) dirY += 150;

    driver->dir = toGrad(atan2((double)dirY, (double)dirX));
    #endif

    #ifdef CARTESIAN
    driver->dx = 0;
    driver->dy = 0;
    if (((readStatus & 0b10000000) >> 7) == 1) driver->dx -= SPEED_LINE_REACT;
    if (((readStatus & 0b01000000) >> 6) == 1) driver->dx -= SPEED_LINE_REACT;
    if (((readStatus & 0b00100000) >> 5) == 1) driver->dy -= SPEED_LINE_REACT;
    if (((readStatus & 0b00010000) >> 4) == 1) driver->dy -= SPEED_LINE_REACT;
    if (((readStatus & 0b00001000) >> 3) == 1) driver->dx += SPEED_LINE_REACT;
    if (((readStatus & 0b00000100) >> 2) == 1) driver->dx += SPEED_LINE_REACT;
    if (((readStatus & 0b00000010) >> 1) == 1) driver->dy += SPEED_LINE_REACT;
    if (((readStatus & 0b00000001) >> 0) == 1) driver->dy += SPEED_LINE_REACT;
    #endif
}

void stay_on_line(byte readStatus) {
    driver->dx = 0;
    if (((readStatus & 0b10000000) >> 7) == 1) driver->dx += SPEED_LINE_REACT;
    if (((readStatus & 0b01000000) >> 6) == 1) driver->dx += SPEED_LINE_REACT;
    if (((readStatus & 0b00001000) >> 3) == 1) driver->dx -= SPEED_LINE_REACT;
    if (((readStatus & 0b00000100) >> 2) == 1) driver->dx -= SPEED_LINE_REACT;
}

