#pragma once

#include "sensors/bno.h"
#include "sensors/lines.h"
#include "sensors/ball.h"
#include "sensors/camera.h"

#ifdef SENSORS
#define s_extr
#else
#define s_extr extern
#endif

s_extr BNO* compass;
s_extr Lines* lines;
s_extr Ball* ball;
s_extr HardwareSerial* BallSerial;
s_extr Camera* attack_goal;
s_extr Camera* defence_goal;
s_extr HardwareSerial* CameraSerial;

void init_sensors();
void read_sensors();
