#include "../include/movement/movement.h"
#include "../include/utility/utility.h"

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

void MovementController::move(int vel, int dir, int orient, double compass) {
    //CONTROLLA DA QUA
    if (compass > 180) input = (double)(compass - 360.0);
    else input = (double)compass;

    if (orient > 180) setPoint = (double)(orient - 360.0);
    else setPoint = (double)orient;

    static double offsetPid = 0;
    if (pid->Compute()) offsetPid = -output;
    //FINO A QUA

    double rang = toRad(dir);
    float vx = vel * cos(rang);
    float vy = -vel * sin(rang);
    
    float speed[4];
    speed[0] = (vx * motors[0]->ANGLE_SIN) + (vy * motors[0]->ANGLE_COS);
    speed[1] = (vx * motors[1]->ANGLE_SIN) + (vy * motors[1]->ANGLE_COS);
    speed[2] = (vx * motors[2]->ANGLE_SIN) + (vy * motors[2]->ANGLE_COS);
    speed[3] = (vx * motors[3]->ANGLE_SIN) + (vy * motors[3]->ANGLE_COS);

    speed[0] += offsetPid;
    speed[1] += offsetPid;
    speed[2] += offsetPid;
    speed[3] += offsetPid;

    speed[0] = constrain(speed[0], -255, 255);
    speed[1] = constrain(speed[1], -255, 255);
    speed[2] = constrain(speed[2], -255, 255);
    speed[3] = constrain(speed[3], -255, 255);

    motors[0]->drive(speed[0]);
    motors[1]->drive(speed[1]);
    motors[2]->drive(speed[2]);
    motors[3]->drive(speed[3]);
}

void MovementController::stop() {
    motors[0]->stop();
    motors[1]->stop();
    motors[2]->stop();
    motors[3]->stop();
}
