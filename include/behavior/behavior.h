#pragma once

#include "config.h"

#ifdef ROLL
#define STRIKER
#define GAME_SPEED 70
#endif

#ifdef ROCK
#define KEEPER
#define CARTESIAN
#define GAME_SPEED 60
#endif

#define SETUP_SPEED 35

void behavior();
