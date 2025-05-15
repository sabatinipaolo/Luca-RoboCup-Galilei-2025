#include "control/control.h"
#include "behavior/behavior.h"
#include "behavior/bounds.h"

void line_react(byte readStatus) {
    #ifdef POLAR
    driver->speed = SPEED_LINE_REACT;
    driver->absolute = true;

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

    driver->dir = degrees(atan2((double)dirY, (double)dirX));
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
    if (((readStatus & 0b10000000) >> 7) == 1) driver->dx += SETUP_SPEED;
    if (((readStatus & 0b01000000) >> 6) == 1) driver->dx += SETUP_SPEED;
    // if (((readStatus & 0b00001000) >> 3) == 1) driver->dx -= SETUP_SPEED;
    if (((readStatus & 0b00000100) >> 2) == 1) driver->dx -= SETUP_SPEED;

    if (
        ((readStatus & 0b11000000) >> 6) >= 1 and
        ((readStatus & 0b00001100) >> 2) >= 1
    ) driver->dx = SPEED_LINE_REACT;

    // if (((readStatus | 0b11011111) >> 5) == 0) driver->dy -= SPEED_LINE_REACT;
    // if (((readStatus | 0b11101111) >> 4) == 0) driver->dy -= SPEED_LINE_REACT;
    // if (((readStatus | 0b11111101) >> 1) == 0) driver->dy += SPEED_LINE_REACT;
    // if (((readStatus | 0b11111110) >> 0) == 0) driver->dy += SPEED_LINE_REACT;
}

