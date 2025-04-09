#include "sensors/lines.h"
#include "sensors/sensors.h"
#include "utility/utility.h"
#include "game/game.h"

Lines::Lines() {
    read();
}

void Lines::read() {
    values[0] = analogRead(PIN_N_INSIDE);
    values[1] = analogRead(PIN_N_OUTSIDE);
    values[2] = analogRead(PIN_E_INSIDE);
    values[3] = analogRead(PIN_E_OUTSIDE);
    values[4] = analogRead(PIN_S_INSIDE);
    values[5] = analogRead(PIN_S_OUTSIDE);
    values[6] = analogRead(PIN_W_INSIDE);
    values[7] = analogRead(PIN_W_OUTSIDE);
    
    status = 0;

    if(values[0] > LINES_THRESHOLD) status |= 0b10000000;
    if(values[1] > LINES_THRESHOLD) status |= 0b01000000; // Lower the threshold for ROCK (250-300)
    if(values[2] > LINES_THRESHOLD) status |= 0b00100000;
    if(values[3] > LINES_THRESHOLD) status |= 0b00010000;
    if(values[4] > LINES_THRESHOLD) status |= 0b00001000;
    if(values[5] > LINES_THRESHOLD) status |= 0b00000100;
    if(values[6] > LINES_THRESHOLD) status |= 0b00000010;
    if(values[7] > LINES_THRESHOLD) status |= 0b00000001;
}

void Lines::react() {
    driver->speed = SPEED_LINE_REACT;

    int dirX = 0;
    int dirY = 0;

    if (((status & 0b10000000) >> 7) == 1) dirY -= 100;
    if (((status & 0b01000000) >> 6) == 1) dirY -= 150;
    if (((status & 0b00100000) >> 5) == 1) dirX -= 100;
    if (((status & 0b00010000) >> 4) == 1) dirX -= 150;
    if (((status & 0b00001000) >> 3) == 1) dirY += 100;
    if (((status & 0b00000100) >> 2) == 1) dirY += 150;
    if (((status & 0b00000010) >> 1) == 1) dirX += 100;
    if (((status & 0b00000001) >> 0) == 1) dirX += 150;

    if (dirX >= 150 or dirX <= -150 or dirY >= 150 or dirY <= -150) driver->speed *= 1.5;

    driver->dir = toGrad(atan2(dirX, dirY));
}

void Lines::react(float* dirX, float* dirY) {
    driver->speed = SPEED_LINE_REACT;

    if (((status & 0b10000000) >> 7) == 1) dirY -= 100;
    if (((status & 0b01000000) >> 6) == 1) dirY -= 150;
    if (((status & 0b00100000) >> 5) == 1) dirX -= 100;
    if (((status & 0b00010000) >> 4) == 1) dirX -= 150;
    if (((status & 0b00001000) >> 3) == 1) dirY += 100;
    if (((status & 0b00000100) >> 2) == 1) dirY += 150;
    if (((status & 0b00000010) >> 1) == 1) dirX += 100;
    if (((status & 0b00000001) >> 0) == 1) dirX += 150;
}
