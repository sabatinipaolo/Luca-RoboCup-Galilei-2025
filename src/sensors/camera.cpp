#include <Arduino.h>
#include "sensors/sensors.h"
#include "sensors/camera.h"
#include "utility/utility.h"

Camera::Camera() {
    pinMode(GOAL_SWITCH_PIN, INPUT);

    CameraSerial = new HardwareSerial(CAMERA_RX, CAMERA_TX);
    CameraSerial->begin(19200);

    angle = 999;
    p_angle = 0;
    raw_angle = 999;

    area = 999;
    p_area = 0;
    raw_area = 999;

    seen = false;
}

void readMV() {
    int yellow_goal_angle, blue_goal_angle;
    int yellow_goal_area, blue_goal_area;
    char byteLetto;
    while (CameraSerial->available()) {

        byteLetto = CameraSerial->read();
        if (byteLetto == 'Y') {
            yellow_goal_angle = CameraSerial->parseInt();
            CameraSerial->read();
            yellow_goal_area = CameraSerial->parseInt();

            if (digitalRead(GOAL_SWITCH_PIN) == YELLOW_GOAL) {
                attackGoal->raw_angle = yellow_goal_angle;
                attackGoal->raw_area = yellow_goal_area;
            } else {
                defenceGoal->raw_angle = yellow_goal_angle;
                defenceGoal->raw_area = yellow_goal_area;
            }
        } else if (byteLetto == 'B') {
            blue_goal_angle = CameraSerial->parseInt();
            CameraSerial->read();
            blue_goal_area = CameraSerial->parseInt();

            if (digitalRead(GOAL_SWITCH_PIN) == BLUE_GOAL) {
                attackGoal->raw_angle = blue_goal_angle;
                attackGoal->raw_area = blue_goal_area;
            } else {
                defenceGoal->raw_angle = blue_goal_angle;
                defenceGoal->raw_area = blue_goal_area;
            }
        }
    }
    ;
}

void Camera::update() {
    unsigned long t0 = millis();
    static unsigned long t1 = t0 + 500;

    if (raw_angle <= 360) {
        angle = raw_angle;
        angle = filter_angle(angle, p_angle, 0.5);
        p_angle = angle;
        angle = (compass->angle + angle) % 360;

        area = raw_area;
        area = filter(area, p_area, 0.5);
        p_area = area;

        seen = true;
        t1 = t0 + 500;

    } else if(t1 < t0) {
        seen = false;
        angle = 999;
        area = -1;
    }

    // WHY DOES THIS EXIST, IF SOMETHING ISN'T WORKING, TRY TURNING IT ON
    // if (angoloPortaAttacco <= 360) {
    //     if (angoloPortaAttacco < 90) angoloPortaAttacco *= 1.5;

    //     angoloPortaAttacco = filtroAngolo(angoloPortaAttacco, angoloPortaAttaccoPasta, 0.1);
    //     angoloPortaAttaccoPasta = angoloPortaAttacco;
    // }

    // if (angoloPortaDifesa <= 360) {
    //     angoloPortaDifesa = filtroAngolo(angoloPortaDifesa, angoloPortaDifesaPasta, 0.1);
    //     angoloPortaDifesaPasta = angoloPortaDifesa;
    // }
}
