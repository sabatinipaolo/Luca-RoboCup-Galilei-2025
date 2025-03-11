#pragma once

#ifdef SENSORS
#define s_extr
#else
#define s_extr extern
#endif

#include "movement/movement.h"
#include "sensors/bno.h"
#include "sensors/lines.h"

s_extr MovementController* driver;
s_extr BNO* compass;
s_extr Lines* lines;

void initSensors();
void readSensors();
