#include "sensors/bno.h"
#include "utility/utility.h"

BNO::BNO() {
    bno = Adafruit_BNO055(55, 0x28);
    bno.begin(bno.OPERATION_MODE_IMUPLUS); //Could add check to see if conncted correctly
    bno.setExtCrystalUse(true);
    delay(1000);
    
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    STARTING_ANGLE = euler.x();
}

void BNO::read() {
    int imuCurrentEuler;
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    imuCurrentEuler = euler.x() - STARTING_ANGLE;

    if (imuCurrentEuler < 0) imuCurrentEuler += 360;

    angle = filter_angle(imuCurrentEuler, p_angle, 0.5);
    p_angle = angle;
}
