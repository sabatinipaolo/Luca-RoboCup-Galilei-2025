#pragma once

#include "sensors/bno.h"
#include "sensors/lines.h"
#include "sensors/ball.h"
#include "sensors/camera.h"
#include "sensors/ball_presence.h"

extern BNO* compass;
extern Lines* lines;
extern Ball* ball;
extern HardwareSerial* BallSerial;
extern Goal* attack_goal;
extern Goal* defence_goal;
extern HardwareSerial* CameraSerial;
extern BallPresence* ball_presence;

void init_sensors();
void read_sensors();
