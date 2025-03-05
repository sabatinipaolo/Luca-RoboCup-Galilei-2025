#include "movement/motors.h"
#include <Arduino.h>

Motor::Motor(int a, int b, int pwm, int angle_){
    this->pinA = a;
    this->pinB = b;
    this->pinPwm = pwm;
    this->angle = angle_;

    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinPwm, OUTPUT);
}

Motor::Motor() {}

void Motor::drive(int speed){
    if(speed > 0) {
        digitalWrite(pinA, HIGH);
        digitalWrite(pinB, LOW);

    }else if(speed < 0) {
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, HIGH);
        speed *= -1;

    } else {
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
    }

    analogWrite(pinPwm, speed);
}

void Motor::stop(){
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, HIGH);
}

void Motor::test(){
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, HIGH);
    analogWrite(pinPwm, 255);
    delay(1500);

    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
    analogWrite(pinPwm, 0);
    delay(500);

    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, LOW);
    analogWrite(pinPwm, 255);
    delay(1500);

    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
    analogWrite(pinPwm, 0);
    delay(500);
}
