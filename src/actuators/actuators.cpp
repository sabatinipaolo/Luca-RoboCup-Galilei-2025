#define ACTUATORS

#include "actuators/actuators.h"

void init_actuators() {
    kicker = new Kicker();
    roller = new Roller();
    roller->setSpeed(100);
}
