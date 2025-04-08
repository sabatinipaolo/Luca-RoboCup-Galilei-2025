#pragma once
#include <Arduino.h>

#define PIN_N_INSIDE PA5
#define PIN_N_OUTSIDE PA4

#define PIN_E_INSIDE PA3
#define PIN_E_OUTSIDE PA2

#define PIN_S_INSIDE PA1
#define PIN_S_OUTSIDE PA0

#define PIN_W_INSIDE PA7
#define PIN_W_OUTSIDE PA6

// #define LINES_THRESHOLD 350
#define LINES_THRESHOLD 100

class Lines {
public:
    // | N-IN | N-OUT || E-IN | E-OUT || S-IN | S-OUT || W-IN | W-OUT |
    int values[8];
    byte status;

    Lines();
    void read();
    void react();
    void react(float* dirX, float* dirY);
};
