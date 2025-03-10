#pragma once
#include "movement/movement.h"
#include "sensors/bno.h"

MovementController* driver;
BNO* compass;

void initSensors();
void readSensors();
