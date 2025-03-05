#include "Arduino.h"

#define PIN_A_0 PB12
#define PIN_B_0 PB13
#define PIN_VEL_0 PB1

#define PIN_A_1 PB14
#define PIN_B_1 PB15
#define PIN_VEL_1 PB0

#define PIN_A_2 PB11
#define PIN_B_2 PB12
#define PIN_VEL_2 PB9

#define PIN_A_3 PB15
#define PIN_B_3 PB3
#define PIN_VEL_3 PB8

class Motor {
private:
    int pinA, pinB, pinPwm;

public:
    int angle;
    Motor(int a, int b, int pwm, int angle);
    Motor();
    void drive(int speed);
    void test();
    void stop();
};
