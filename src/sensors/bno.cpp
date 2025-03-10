#include "sensors/bno.h"
#include "utility/utility.h"

BNO::BNO() {
    //Controlla se è presente la bussola
    // if (!bno.begin(bno.OPERATION_MODE_IMUPLUS))  {
    //     Serial.print("No BNO055 detected");
    //     while (1);
    // }

    bno.setExtCrystalUse(true);
    delay(1000);
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    STARTING_ANGLE = euler.x();
}

void BNO::read() {
    //static unsigned long t0_bussola = millis(), tf_bussola = t0_bussola + 15;
    int imuCurrentEuler;
    //t0_bussola = millis();

    //if (t0_bussola > tf_bussola)
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER); //Magia Oscura
    imuCurrentEuler = euler.x() - STARTING_ANGLE;

    if (imuCurrentEuler < 0) imuCurrentEuler += 360;

    //tf_bussola = t0_bussola + 15;

    angle = filter_angle(imuCurrentEuler, p_angle, 0.5);
    p_angle = angle;
}
