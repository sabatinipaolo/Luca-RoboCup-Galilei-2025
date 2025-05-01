#include <Arduino.h>
#include "sensors/sensors.h"
#include "sensors/camera.h"
#include "utility/filters.h"
#include "config.h"

Camera::Camera() {
    pinMode(Pins::GOAL_SWITCH, INPUT);
    CameraSerial = new HardwareSerial(Pins::CAMERA_RX, Pins::CAMERA_TX);
    CameraSerial->begin(19200);
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

            if (digitalRead(Pins::GOAL_SWITCH) == YELLOW_GOAL) {
                attack_goal->raw_angle = yellow_goal_angle;
                attack_goal->raw_area = yellow_goal_area;
            } else {
                defence_goal->raw_angle = yellow_goal_angle;
                defence_goal->raw_area = yellow_goal_area;
            }
        } else if (byteLetto == 'B') {
            blue_goal_angle = CameraSerial->parseInt();
            CameraSerial->read();
            blue_goal_area = CameraSerial->parseInt();

            if (digitalRead(Pins::GOAL_SWITCH) == BLUE_GOAL) {
                attack_goal->raw_angle = blue_goal_angle;
                attack_goal->raw_area = blue_goal_area;
            } else {
                defence_goal->raw_angle = blue_goal_angle;
                defence_goal->raw_area = blue_goal_area;
            }
        }
    }
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
}
