#pragma once

#ifdef SENSORS
#define s_extr
#else
#define s_extr extern
#endif

#include "movement/movement.h"
#include "sensors/bno.h"
#include "sensors/lines.h"
#include "sensors/ball.h"
#include "sensors/camera.h"

s_extr MovementController* driver;
s_extr BNO* compass;
s_extr Lines* lines;
s_extr Ball* ball;
s_extr HardwareSerial* BallSerial;
s_extr Camera* attackGoal;
s_extr Camera* defenceGoal;
s_extr HardwareSerial* CameraSerial;

void initSensors();
void readSensors();
