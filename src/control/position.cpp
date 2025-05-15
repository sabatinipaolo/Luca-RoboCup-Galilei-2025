#include "sensors/sensors.h"
#include "control/position.h"

PositionController::PositionController() {}

void PositionController::update() {
    if (attack_goal->seen and defence_goal->seen) {
        int attack_goal_slope = tan(radians((450-attack_goal->angle) % 360));
        int defence_goal_slope = tan(radians((450-defence_goal->angle) % 360));

        // y = attack_goal_slope * x + 100
        // y = defence_goal_slope * x - 100
        // x = (-100 - (+100)) / (attack_goal_slope - defence_goal_slope)
        if (attack_goal_slope != defence_goal_slope) {
            coord.x = -200 / (attack_goal_slope - defence_goal_slope);
            coord.y = attack_goal_slope * coord.x + 100;
            set = true;
        } else {
            set = false;
        }
    } else {
        set = false;
    }
}
