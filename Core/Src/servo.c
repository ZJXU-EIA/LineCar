//
// Created by Nymphaea on 24-11-14.
//

#include "servo.h"
#include <main.h>
#include <oled.h>
#include <tim.h>
#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_tim.h>

/**
 * @author Nymphaea0726
 * @brief Initialize the PWM for the servo
 */
void Servo_PWM_Init() {
    // 1. Enable the clock for the timer
    // 2. Configure the timer
    // 3. Enable the timer
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
}

/**
 * @author Nymphaea0726
 * @brief Move the servo to a specific angle
 * @param angle The angle to move the servo to
 */
void Servo(int angle) {
    // 1. Calculate the pulse width
    int pulse_width = 500 + (angle * 2000 / 180);
    // 2. Set the pulse width
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, pulse_width);
    // 3. Wait for the servo to move

    // 4. Set the pulse width to 0
    // 5. Wait for the servo to stop moving
    // 6. Return
}

/**
 * @author Nymphaea0726
 * @brief Test the servo by moving it from 0 to 180 degrees in 10 degree increments
 */
void Servo_Test() {
    int angle = 0;
    for (angle = 0; angle <= 180; angle += 10) {
        Servo(angle);
        HAL_Delay(1000);
    }
    for (angle = 180; angle >= 0; angle -= 10) {
        Servo(angle);
        HAL_Delay(1000);
    }
}
