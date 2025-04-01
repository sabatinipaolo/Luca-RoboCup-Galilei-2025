#pragma once

#ifdef SENSORS
#define s_extr
#else
#define s_extr extern
#endif

#include <HardwareSerial.h>
#include "movement/movement.h"
#include "sensors/bno.h"
#include "sensors/lines.h"
#include "sensors/ball.h"

s_extr MovementController* driver;
s_extr BNO* compass;
s_extr Lines* lines;
s_extr Ball* ball;

void initSensors();
void readSensors();
