#include <Arduino.h>
#include "behavior/behavior.h"
#include "behavior/striker.h"
#include "behavior/keeper.h"

void behavior() {
    #ifdef STRIKER
    striker();
    #endif

    #ifdef KEEPER
    keeper();
    #endif
}