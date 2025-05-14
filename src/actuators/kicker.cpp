#include <Arduino.h>
#include "sensors/sensors.h"
#include "actuators/kicker.h"
#include "config.h"

Kicker::Kicker() {}

void Kicker::kick() {
    static long long int t_charge = 0, t_atk = 0;
    
    if (ball_presence->present) {
        if (millis() - t_charge >= KICKER_CHARGE_TIME and attack_goal->seen and attack_goal->area > KICKER_AREA_THRESHOLD) {
            digitalWrite(Pins::KICKER, HIGH);
            t_atk = millis();
        } 
    } else {
        if (millis() - t_atk >= KICKER_ATK_TIME) {
            digitalWrite(Pins::KICKER, LOW); 
        } 
        t_charge = millis();
    }
}

void Kicker::test() {
    digitalWrite(Pins::KICKER, HIGH);
    delay(1000);
    digitalWrite(Pins::KICKER, LOW);
    delay(1000);
}
