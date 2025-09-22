#pragma once

#include "actuators/kicker.h"
#include "actuators/roller.h"

extern Kicker* kicker;
extern Roller* roller;

void init_actuators();
void update_actuators();
