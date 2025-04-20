#include "sensors/sensors.h"
#include "utility/transformations.h"
#include "control/control.h"
#include "control/movement.h"

MovementController::MovementController(Motor* m0, Motor* m1, Motor* m2, Motor* m3) {
    // Motors init
    motors[0] = m0;
    motors[1] = m1;
    motors[2] = m2;
    motors[3] = m3;

    // PID init
    pid = new PID(&input, &output, &setPoint, KP, KI, KD, DIRECT);
    pid->SetSampleTime(2);
    pid->SetOutputLimits(-255, 255);
    pid->SetMode(AUTOMATIC);
    pid->SetControllerDirection(DIRECT);
}

// Keep in mind that dx indicates forward/backward movement, while dy indicates left/right movement
void MovementController::move(int dir, int dx, int dy, int speed, int orient, bool brake) {
    // Motor movement
    double r_dir = toRad(dir);
    float dirX = speed * cos(r_dir) + dx;
    float dirY = -(speed * sin(r_dir) + dy);

    float motorSpeed[4];
    motorSpeed[0] = (dirX * motors[0]->ANGLE_SIN) + (dirY * motors[0]->ANGLE_COS);
    motorSpeed[1] = (dirX * motors[1]->ANGLE_SIN) + (dirY * motors[1]->ANGLE_COS);
    motorSpeed[2] = (dirX * motors[2]->ANGLE_SIN) + (dirY * motors[2]->ANGLE_COS);
    motorSpeed[3] = (dirX * motors[3]->ANGLE_SIN) + (dirY * motors[3]->ANGLE_COS);

    // PID
    input = (compass->angle > 180) ? compass->angle - 360.0 : compass->angle;
    setPoint = (orient > 180) ? orient - 360.0 : orient;

    static double offsetPid = 0;
    if(pid->Compute()) offsetPid = -output;
    
    motorSpeed[0] += offsetPid;
    motorSpeed[1] += offsetPid;
    motorSpeed[2] += offsetPid;
    motorSpeed[3] += offsetPid;

    motorSpeed[0] = constrain(motorSpeed[0], -255, 255);
    motorSpeed[1] = constrain(motorSpeed[1], -255, 255);
    motorSpeed[2] = constrain(motorSpeed[2], -255, 255);
    motorSpeed[3] = constrain(motorSpeed[3], -255, 255);

    // Drive motors
    motors[0]->drive(motorSpeed[0]);
    motors[1]->drive(motorSpeed[1]);
    motors[2]->drive(motorSpeed[2]);
    motors[3]->drive(motorSpeed[3]);

    if (brake) stop();
}

void MovementController::move(int dir, int speed, int orient, bool brake) {
    move(dir, 0, 0, speed, orient, brake);
}

void MovementController::move() {
    move(this->dir, this->dx, this->dy, this->speed, this->orient, this->brake);
}

void MovementController::stop() {
    motors[0]->stop();
    motors[1]->stop();
    motors[2]->stop();
    motors[3]->stop();
}

void MovementController::test() {
    driver->motors[0]->test();
	driver->motors[1]->test();
	driver->motors[2]->test();
	driver->motors[3]->test();
}
