#include "movement/movement.h"
#include "sensors/sensors.h"
#include "utility/utility.h"

MovementController::MovementController() {
    MovementController(
        new Motor(PIN_A_0, PIN_B_0, PIN_VEL_0, 54), //M1 ALTO/SX
        new Motor(PIN_A_1, PIN_B_1, PIN_VEL_1, 135), //M2 ALTO/DX
        new Motor(PIN_A_2, PIN_B_2, PIN_VEL_2, 225), //M3 BASSO/DX
        new Motor(PIN_A_3, PIN_B_3, PIN_VEL_3, 306)  //M4 BASSO/SX
    );
}

MovementController::MovementController(Motor* m0, Motor* m1, Motor* m2, Motor* m3) {
    motors[0] = m0;
    motors[1] = m1;
    motors[2] = m2;
    motors[3] = m3;

    pid = new PID(&input, &output, &setPoint, KP, KI, KD, DIRECT);

    pid->SetSampleTime(2);
    //pid->setAngleWrap(true);
    pid->SetOutputLimits(-255, 255);
    pid->SetMode(AUTOMATIC);
    pid->SetControllerDirection(DIRECT);

}

void MovementController::move(int speed, int dir, int orient) {
    //CONTROLLA DA QUA
    if (compass->angle > 180) input = (double)(compass->angle - 360.0);
    else input = (double)compass->angle;

    if (orient > 180) setPoint = (double)(orient - 360.0);
    else setPoint = (double)orient;

    static double offsetPid = 0;
    if (pid->Compute()) offsetPid = -output;
    //FINO A QUA

    double rang = toRad(dir);
    float vx = speed * cos(rang);
    float vy = -speed * sin(rang);
    
    float motorSpeed[4];
    motorSpeed[0] = (vx * motors[0]->ANGLE_SIN) + (vy * motors[0]->ANGLE_COS);
    motorSpeed[1] = (vx * motors[1]->ANGLE_SIN) + (vy * motors[1]->ANGLE_COS);
    motorSpeed[2] = (vx * motors[2]->ANGLE_SIN) + (vy * motors[2]->ANGLE_COS);
    motorSpeed[3] = (vx * motors[3]->ANGLE_SIN) + (vy * motors[3]->ANGLE_COS);

    motorSpeed[0] += offsetPid;
    motorSpeed[1] += offsetPid;
    motorSpeed[2] += offsetPid;
    motorSpeed[3] += offsetPid;

    motorSpeed[0] = constrain(motorSpeed[0], -255, 255);
    motorSpeed[1] = constrain(motorSpeed[1], -255, 255);
    motorSpeed[2] = constrain(motorSpeed[2], -255, 255);
    motorSpeed[3] = constrain(motorSpeed[3], -255, 255);

    motors[0]->drive(motorSpeed[0]);
    motors[1]->drive(motorSpeed[1]);
    motors[2]->drive(motorSpeed[2]);
    motors[3]->drive(motorSpeed[3]);
}

void MovementController::stop() {
    motors[0]->stop();
    motors[1]->stop();
    motors[2]->stop();
    motors[3]->stop();
}
