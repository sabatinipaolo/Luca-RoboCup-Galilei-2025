#include "sensors/sensors.h"
#include "control/position.h"
#include "utility/transformations.h"

PositionController::PositionController() {}

void PositionController::update() {
    if (attack_goal->seen and defence_goal->seen) {
        int attack_goal_slope, defence_goal_slope;
        if (attack_goal->angle <= 90)      attack_goal_slope = tan(toRad(90 - attack_goal->angle));
        else if (attack_goal->angle < 270) attack_goal_slope = tan(toRad(270 - attack_goal->angle));
        else                               attack_goal_slope = tan(toRad(450 - attack_goal->angle));
    
        if (defence_goal->angle <= 90)      defence_goal_slope = tan(toRad(90 - defence_goal->angle));
        else if (defence_goal->angle < 270) defence_goal_slope = tan(toRad(270 - defence_goal->angle));
        else                                defence_goal_slope = tan(toRad(450 - defence_goal->angle));
        
        if (attack_goal_slope != defence_goal_slope) {
            coord.x = -242 / (attack_goal_slope - defence_goal_slope);
            coord.y = attack_goal_slope * coord.x + 121;
            set = true;
        } else {
            set = false;
        }
    } else {
        set = false;
    }
}
