#pragma once

#include "actuators/kicker.h"

#ifdef ACTUATORS
#define a_extr
#else
#define a_extr extern
#endif

a_extr Kicker* kicker;

void init_actuators();
