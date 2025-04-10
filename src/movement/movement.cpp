#include "movement/movement.h"
#include "sensors/sensors.h"
#include "sensors/lines.h"
#include "utility/utility.h"

MovementController::MovementController(Motor* m0, Motor* m1, Motor* m2, Motor* m3) {
    //Motors init
    motors[0] = m0;
    motors[1] = m1;
    motors[2] = m2;
    motors[3] = m3;

    //PID init
    pid = new PID(&input, &output, &setPoint, KP, KI, KD, DIRECT);
    pid->SetSampleTime(2);
    // pid->setAngleWrap(true);
    pid->SetOutputLimits(-255, 255);
    pid->SetMode(AUTOMATIC);
    pid->SetControllerDirection(DIRECT);

    speed = 0;
    dir = 0;
    orient = 0;
    brake = false;
}

void MovementController::move(int dir, int speed, int orient) {
    //Motor movement
    double r_dir = toRad(dir);
    float vx = speed * cos(r_dir);
    float vy = -speed * sin(r_dir);

    float motorSpeed[4];
    motorSpeed[0] = (vx * motors[0]->ANGLE_SIN) + (vy * motors[0]->ANGLE_COS);
    motorSpeed[1] = (vx * motors[1]->ANGLE_SIN) + (vy * motors[1]->ANGLE_COS);
    motorSpeed[2] = (vx * motors[2]->ANGLE_SIN) + (vy * motors[2]->ANGLE_COS);
    motorSpeed[3] = (vx * motors[3]->ANGLE_SIN) + (vy * motors[3]->ANGLE_COS);

    //PID
    input = (compass->angle > 180) ? compass->angle - 360.0 : compass->angle;
    setPoint = (orient > 180) ? orient - 360.0 : orient;

    double offsetPid = (pid->Compute()) ? -output : 0;
    motorSpeed[0] += offsetPid;
    motorSpeed[1] += offsetPid;
    motorSpeed[2] += offsetPid;
    motorSpeed[3] += offsetPid;

    motorSpeed[0] = constrain(motorSpeed[0], -255, 255);
    motorSpeed[1] = constrain(motorSpeed[1], -255, 255);
    motorSpeed[2] = constrain(motorSpeed[2], -255, 255);
    motorSpeed[3] = constrain(motorSpeed[3], -255, 255);

    //Drive motors
    motors[0]->drive(motorSpeed[0]);
    motors[1]->drive(motorSpeed[1]);
    motors[2]->drive(motorSpeed[2]);
    motors[3]->drive(motorSpeed[3]);
}

void MovementController::move() {
    move(dir, speed, orient);
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