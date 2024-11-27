//
// Created by Nymphaea on 24-11-12.
//

#include "tracer.hpp"
#include <main.h>
#include <oled.h>

Tracer::Tracer(Servo* servo, Motor* motorLeft, Motor* motorRight)
    : servo(servo), motorLeft(motorLeft), motorRight(motorRight), left_speed(32), right_speed(32),
      servo_angle(0), prev_servo_angle(91), cross_Count(0), last_Cross_State(0) {}

void Tracer::InitializeStates() {
    Centre = (Gray_3_Value == GPIO_PIN_SET && Gray_4_Value == GPIO_PIN_SET && Gray_5_Value == GPIO_PIN_SET) ||
             (Gray_3_Value == GPIO_PIN_SET && Gray_4_Value == GPIO_PIN_SET) ||
             (Gray_4_Value == GPIO_PIN_SET && Gray_5_Value == GPIO_PIN_SET);
    LeftSlight = Gray_2_Value == GPIO_PIN_SET;
    RightSlight = Gray_6_Value == GPIO_PIN_SET;
    Left = Gray_1_Value == GPIO_PIN_SET;
    Right = Gray_7_Value == GPIO_PIN_SET;
    Cross = Gray_1_Value == GPIO_PIN_SET && Gray_2_Value == GPIO_PIN_SET && Gray_3_Value == GPIO_PIN_SET &&
            Gray_4_Value == GPIO_PIN_SET && Gray_5_Value == GPIO_PIN_SET && Gray_6_Value == GPIO_PIN_SET &&
            Gray_7_Value == GPIO_PIN_SET;
}

void Tracer::Execute() {
    InitializeStates();

    if (Cross && last_Cross_State == 0) {
        cross_Count++;
        last_Cross_State = 1;
    } else if (!Cross) {
        last_Cross_State = 0;
    }

    if (cross_Count >= 7) {
        left_speed = 0;
        right_speed = 0;
    } else {
        if (Centre) {
            left_speed = 35;
            right_speed = 35;
            if (prev_servo_angle == 55) {
                servo_angle = 90 + 1;
            } else if (prev_servo_angle == 125) {
                servo_angle = 90 - 1;
            } else {
                servo_angle = 90;
            }
        } else if (Left || LeftSlight) {
            left_speed = Left ? 20 : 25;
            right_speed = Left ? 40 : 35;
            servo_angle = Left ? 55 : 80;
        } else if (Right || RightSlight) {
            left_speed = Right ? 40 : 35;
            right_speed = Right ? 20 : 25;
            servo_angle = Right ? 125 : 100;
        }
    }

    prev_servo_angle = servo_angle;
    servo->Move(servo_angle);
    motorLeft->Run(Motor::Forward, left_speed);
    motorRight->Run(Motor::Forward, right_speed);
}