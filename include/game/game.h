#pragma once

#include "main.h"

#define PLAY 0
#define STOP 1
#define LINE_REACT 2
#define LINE_CHECK 3

#ifdef ROCK
    #define SPEED_ATK 50
    #define SPEED_LINE_REACT 50
    #define MAX_SPEED_LINE_REACT 200

    #define STOP_TIME 1000
    #define LINE_REACT_TIME 1500
    #define LINE_CHECK_TIME 0
#else
    #define SPEED_ATK 70
    #define SPEED_LINE_REACT 70
    #define MAX_SPEED_LINE_REACT 200

    #define STOP_TIME 0
    #define LINE_REACT_TIME 100
    #define LINE_CHECK_TIME 0
#endif

void game();
