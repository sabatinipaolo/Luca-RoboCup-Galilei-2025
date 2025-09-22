#pragma once

#include "control/movement.h"
#include "control/position.h"


extern MovementController* driver;
extern PositionController* position;

void init_control();
void update_control();
