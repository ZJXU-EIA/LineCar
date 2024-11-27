//
// Created by Nymphaea on 24-11-12.
//

#ifndef TRACING_H
#define TRACING_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stm32f1xx_hal.h>
#include <motor.hpp>
#include <servo.hpp>

class Tracer {
public:
    Tracer(Servo *servo, Motor *motorLeft, Motor *motorRight);

    void InitializeStates();

    void Execute();

private:
    Servo *servo;
    Motor *motorLeft;
    Motor *motorRight;
    char Centre;
    char Left;
    char Right;
    char LeftSlight;
    char RightSlight;
    char Cross;
    int left_speed;
    int right_speed;
    int servo_angle;
    int prev_servo_angle;
    int cross_Count;
    int last_Cross_State;
};

#endif


#ifdef __cplusplus
}
#endif
