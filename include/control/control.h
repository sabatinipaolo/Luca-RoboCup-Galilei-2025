#pragma once

#include "control/movement.h"

#ifdef CONTROL
#define c_extr
#else
#define c_extr extern
#endif

c_extr MovementController* driver;

void init_control();
