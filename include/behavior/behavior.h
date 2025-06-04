#pragma once

#include "config.h"

#ifdef ROLL
#define STRIKER
#define POLAR
#define GAME_SPEED 35
#endif

#ifdef ROCK
#define KEEPER
#define CARTESIAN
#define GAME_SPEED 35
#endif

#define SETUP_SPEED 30

void behavior();
