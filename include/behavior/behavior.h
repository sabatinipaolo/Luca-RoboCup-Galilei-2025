#pragma once

#include "config.h"

#ifdef ROLL
#define STRIKER
#endif

#ifdef ROCK
#define KEEPER
#endif

#define GAME_SPEED 50
#define SETUP_SPEED 35

void behavior();
