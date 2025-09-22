#include "actuators/actuators.h"

Kicker* kicker=nullptr;
Roller* roller=nullptr;

void init_actuators() {
    kicker = new Kicker();
    roller = new Roller();
}

void update_actuators() {
    kicker->update();
}
