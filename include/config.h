#pragma once

#include <Arduino.h>

// #define ROCK
#define ROLL

namespace Pins {
    // MOTOR DRIVERS
    constexpr int DRIVER_0_A = PB12;
    constexpr int DRIVER_0_B = PB13;
    constexpr int DRIVER_0_PWM = PB1;

    constexpr int DRIVER_1_A = PB14;
    constexpr int DRIVER_1_B = PB15;
    constexpr int DRIVER_1_PWM = PB0;

    constexpr int DRIVER_2_A = PA11;
    constexpr int DRIVER_2_B = PA12;
    constexpr int DRIVER_2_PWM = PB9;

    constexpr int DRIVER_3_A = PA15;
    constexpr int DRIVER_3_B = PB3;
    constexpr int DRIVER_3_PWM = PB8;

    // LINE SENSORS
    constexpr int LINE_N_INSIDE = PA5;
    constexpr int LINE_N_OUTSIDE = PA4;

    constexpr int LINE_E_INSIDE = PA3;
    constexpr int LINE_E_OUTSIDE = PA2;

    constexpr int LINE_S_INSIDE = PA1;
    constexpr int LINE_S_OUTSIDE = PA0;

    constexpr int LINE_W_INSIDE = PA7;
    constexpr int LINE_W_OUTSIDE = PA6;

    // SERIALS
    constexpr int ESP32_TX = PB10;
    constexpr int ESP32_RX = PB11;

    constexpr int CAMERA_TX = PA9;
    constexpr int CAMERA_RX = PA10;

    // SWITCHES
    constexpr int SWITCH_1 = PC14;
    constexpr int SWITCH_2 = PC13;
    constexpr int SWITCH_3 = PC15;
}