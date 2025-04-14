#pragma once

#include "main.h"

#define PLAY 0
#define STOP 1
#define LINE_REACT 2
#define LINE_CHECK 3

#ifdef ROCK
    #define SPEED_ATK 35
    #define SPEED_LINE_REACT 35
    #define MAX_SPEED_LINE_REACT 200

    #define STOP_TIME 20
    #define LINE_REACT_TIME 350
    #define LINE_CHECK_TIME 0
#else
    #define SPEED_ATK 35
    #define SPEED_LINE_REACT 35
    #define MAX_SPEED_LINE_REACT 200

    #define STOP_TIME 20
    #define LINE_REACT_TIME 300
    #define LINE_CHECK_TIME 0
#endif

void game();
